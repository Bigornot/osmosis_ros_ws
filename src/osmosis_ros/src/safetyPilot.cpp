#include <osmosis_control/safetyPilot.hpp>

void SafetyPilot::driveSafetyPilot()
{
	if(emergency_stop_)
		state_=EMERGENCY_STOP;
	else if(controlled_stop_)
		state_=CONTROLLED_STOP;
	else if(switch_to_teleop_)
		state_=SWITCH_TO_TELEOP;

	switch(state_)
	{
		case COMPUTE_CMD:
			ROS_INFO("COMPUTE_CMD\n");
			this->computeCommandCtrlTeleop();
			break;
		case  EMERGENCY_STOP:
			ROS_INFO("EMERGENCY_STOP\n");
			this->stop();
			if(!emergency_stop_)
				state_=COMPUTE_CMD;
			break;
		case CONTROLLED_STOP:
			ROS_INFO("CONTROLLED_STOP\n");
			this->stop();
			if(!controlled_stop_)
				state_=COMPUTE_CMD;
			break;
		case SWITCH_TO_TELEOP:
			ROS_INFO("SWITCH_TO_TELEOP\n");
			base_cmd_=updateCmdWithLaserScan(base_cmd_teleop_.cmd_vel,scan_);

			if(!switch_to_teleop_)
				state_=COMPUTE_CMD;
			break;
		default:
			break;
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
	else 
	{
		cmd.linear.x = fmin(cmd.linear.x, + max_linear);
		cmd.linear.y = fmin(cmd.linear.y, + max_linear);
		cmd.linear.x = fmax(cmd.linear.x, - max_linear);
		cmd.linear.y = fmax(cmd.linear.y, - max_linear);
		cmd.angular.x = fmin(cmd.angular.x, + max_angular);
		cmd.angular.y = fmin(cmd.angular.y, + max_angular);
		cmd.angular.x = fmax(cmd.angular.x, - max_angular);
		cmd.angular.y = fmax(cmd.angular.y, - max_angular);
	}

	return cmd;
}

// from MAUVE priority ressource: choose between teleop or control
void SafetyPilot::computeCommandCtrlTeleop()
{
	geometry_msgs::Twist cmd;

	// if user activate teleop
	if (base_cmd_teleop_.is_active)
	{
		cmd=base_cmd_teleop_.cmd_vel;
	}

	// else read the command from the control loop (from OsmosisControl)
	else cmd=base_cmd_ctrl_;

	//check if we need to override the command due to safe stop from laserScan
	cmd=updateCmdWithLaserScan(cmd,scan_);

	base_cmd_=cmd; // command to publish
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

void SafetyPilot::callbackEmergencyStop(const std_msgs::Bool &stop)
{
	emergency_stop_=stop.data;
}

void SafetyPilot::callbackControlledStop(const std_msgs::Bool &stop)
{
	controlled_stop_=stop.data;
}

void SafetyPilot::callbackSwitchToTeleop(const std_msgs::Bool &switchToTeleop)
{
	switch_to_teleop_=switchToTeleop.data;
}

//! ROS node topics publishing and subscribing initialization
SafetyPilot::SafetyPilot()
{
	freq_=10;
	//set up the publisher for the cmd_vel topic
	cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/summit_xl_a/robotnik_base_control/cmd_vel", 1);
	cmd_vel_sub_  = nh_.subscribe("cmd_vel_control", 1, &SafetyPilot::callbackCmdVelCtrl, this);
	scan_sub_  = nh_.subscribe("/summit_xl_a/front_laser/scan", 1, &SafetyPilot::callbackScan, this);
	cmd_vel_teleop_sub_= nh_.subscribe("cmd_vel_teleop", 1, &SafetyPilot::callbackTeleop, this);
	emergency_stop_sub_ = nh_.subscribe("/do_RM1_EmergencyStop", 1, &SafetyPilot::callbackEmergencyStop, this);
	controlled_stop_sub_ = nh_.subscribe("/do_RM2_ControlledStop", 1, &SafetyPilot::callbackControlledStop, this);
	switch_to_teleop_sub_ = nh_.subscribe("/do_RM5_SwitchToTeleop", 1, &SafetyPilot::callbackSwitchToTeleop, this);

	emergency_stop_=false;
	controlled_stop_=false;
	switch_to_teleop_=false;
}

bool SafetyPilot::run()
{
	ros::Rate loop_rate(freq_);
	while (nh_.ok())
	{
		//this->computeCommandCtrlTeleop();
		this->driveSafetyPilot();
		cmd_vel_pub_.publish(base_cmd_);
		ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
		loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate
	}

	return true;
}

int main(int argc, char** argv)
{
	//init the ROS node
	ros::init(argc, argv, "safety_pilot_node");

	SafetyPilot mySafePilot;
	mySafePilot.run();
}
