#include <safetyPilot.hpp>

////////////////////// PRIVATE //////////////////////

void SafetyPilot::SafetyPilotFSM()
{
	switch(state_)
	{
		case COMPUTE_CMD:
			ROS_INFO("COMPUTE_CMD\n");
			computeCommandCtrlTeleop(false);
			if(controlled_stop_)
			{
				stop();
				state_=CONTROLLED_STOP;
			}
			else if(switch_to_teleop_)
			{
				stop();
				state_=SWITCH_TO_TELEOP;
			}
			break;

		case CONTROLLED_STOP:
			ROS_INFO("CONTROLLED_STOP\n");
			if(!controlled_stop_)
				state_=COMPUTE_CMD;
			break;

		case SWITCH_TO_TELEOP:
			ROS_INFO("SWITCH_TO_TELEOP\n");
			if(controlled_stop_)
			{
				stop();
				state_=CONTROLLED_STOP;
			}
			else
			{
				computeCommandCtrlTeleop(true);
				if(!switch_to_teleop_)
					state_=COMPUTE_CMD;
			}
			break;

		default: break;
	}
}

void SafetyPilot::stop()
{
	base_cmd_.linear.x=0;
	base_cmd_.angular.z=0;
}

// from MAUVE safetyPilot update operation
geometry_msgs::Twist SafetyPilot::updateCmdWithLaserScan(geometry_msgs::Twist cmd,sensor_msgs::LaserScan s)
{
	double obs_dist = numeric_limits<double>::max();
	double obs_lat = numeric_limits<double>::max();

	for (int i = 0; i < s.ranges.size(); i++)
	{
		double r = s.ranges[i];
		if (r > s.range_min)
		{
			double a = s.angle_min + (s.angle_max - s.angle_min) * i / s.ranges.size();
			double dy = fabs( r * sin(a) );
			if (dy <= stop_lateral_distance)
			{
				obs_dist = min(obs_dist, r);
				obs_lat = min(obs_lat, dy);
			}
		}
	}

	if (obs_dist < stop_distance)
	{
		ROS_INFO("Obstacle too close: robot is not allowed to go forward\n");
		{
			cmd.linear.x = min(0.0, cmd.linear.x);
			cmd.linear.y = min(0.0, cmd.linear.y);
		}
	}

	cmd.linear.x = fmin(cmd.linear.x, + max_linear);
	cmd.linear.x = fmax(cmd.linear.x, - max_linear);
	cmd.angular.z = fmin(cmd.angular.z, + max_angular);
	cmd.angular.z = fmax(cmd.angular.z, - max_angular);

	return cmd;
}

// from MAUVE priority ressource: choose between teleop or control
void SafetyPilot::computeCommandCtrlTeleop(bool only_teleop)
{
	geometry_msgs::Twist cmd;

	// if user activate teleop
	if (only_teleop || base_cmd_teleop_.is_active)
	{
		cmd=base_cmd_teleop_.cmd_vel;
	}

	// else read the command from the control loop (from OsmosisControl)
	else cmd=base_cmd_ctrl_;

	//check if we need to override the command due to safe stop from laserScan
	cmd=updateCmdWithLaserScan(cmd,scan_);

	if(fault_injection_wrong_value_cmd_)
	{
		cmd.linear.x = 1.1*max_linear;
		cmd.angular.z = 1.1*max_angular;
		fault_injection_wrong_value_cmd_=false;
	}

	base_cmd_=cmd; // command to publish
}


////////////////////// PUBLIC //////////////////////

SafetyPilot::SafetyPilot()
{
	freq_=10;
	state_=COMPUTE_CMD;

	//set up the publisher for the cmd_vel topic
	cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/summit_xl_a/robotnik_base_control/cmd_vel", 1);
	cmd_vel_sub_  = nh_.subscribe("/cmd_vel_control", 1, &SafetyPilot::callbackCmdVelCtrl, this);
	scan_sub_  = nh_.subscribe("/summit_xl_a/front_laser/scan", 1, &SafetyPilot::callbackScan, this);
	cmd_vel_teleop_sub_ = nh_.subscribe("/cmd_vel_teleop", 1, &SafetyPilot::callbackTeleop, this);
	controlled_stop_sub_ = nh_.subscribe("/do_controlled_stop", 1, &SafetyPilot::callbackControlledStop, this);
	switch_to_teleop_sub_ = nh_.subscribe("/do_switch_to_teleop", 1, &SafetyPilot::callbackSwitchToTeleop, this);
	fault_injection_cmd_not_updated_sub_ = nh_.subscribe("/fault_injection_cmd_not_updated", 1, &SafetyPilot::callbackFaultInjectionCmdNotUpdated, this);
	fault_injection_wrong_value_cmd_sub_ = nh_.subscribe("/fault_injection_wrong_value_cmd", 1, &SafetyPilot::callbackFaultInjectionWrongValueCmd, this);
	controlled_stop_ = false;
	switch_to_teleop_ = false;

	fault_injection_cmd_not_updated_=false;
	fault_injection_wrong_value_cmd_=false;
}

bool SafetyPilot::run()
{
	ros::Rate loop_rate(freq_);
	while (nh_.ok())
	{
		//computeCommandCtrlTeleop();
		SafetyPilotFSM();
		if(!fault_injection_cmd_not_updated_)
		{
			cmd_vel_pub_.publish(base_cmd_);
		}
		ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
		loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate
	}

	return true;
}

void SafetyPilot::callbackCmdVelCtrl(const geometry_msgs::Twist & cmd_msg)
{
	base_cmd_ctrl_ = cmd_msg;
}

void SafetyPilot::callbackScan(const sensor_msgs::LaserScan & scan_msg)
{
	scan_=scan_msg;
}

void SafetyPilot::callbackTeleop(const osmosis_control::TeleopMsg & teleop_msg)
{
	base_cmd_teleop_=teleop_msg;
}

void SafetyPilot::callbackControlledStop(const std_msgs::Bool & controlled_stop)
{
	controlled_stop_=controlled_stop.data;
}

void SafetyPilot::callbackSwitchToTeleop(const std_msgs::Bool & switch_to_teleop)
{
	switch_to_teleop_=switch_to_teleop.data;
}

void SafetyPilot::callbackFaultInjectionCmdNotUpdated(const std_msgs::Bool & fault_injection)
{
	fault_injection_cmd_not_updated_=fault_injection.data;
}

void SafetyPilot::callbackFaultInjectionWrongValueCmd(const std_msgs::Bool & fault_injection)
{
	fault_injection_wrong_value_cmd_=fault_injection.data;
}


////////////////////// MAIN //////////////////////

int main(int argc, char** argv)
{
	//init the ROS node
	ros::init(argc, argv, "safety_pilot_node");

	SafetyPilot mySafePilot;
	mySafePilot.run();
}
