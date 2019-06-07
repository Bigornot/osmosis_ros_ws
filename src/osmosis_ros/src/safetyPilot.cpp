#include <osmosis_control/safetyPilot.hpp>


// from MAUVE safetyPilot update operation
geometry_msgs::Twist SafetyPilot::updateCmdWithLaserScan(geometry_msgs::Twist cmd,sensor_msgs::LaserScan s)
{

	//auto s = shell().scan.read();
	double obs_dist = std::numeric_limits<double>::max();
	double obs_lat = std::numeric_limits<double>::max();

	for (int i = 0; i < s.ranges.size(); i++) 
	{
		double r = s.ranges[i];
		if (r > s.range_min)
		{
			double a = s.angle_min + (s.angle_max - s.angle_min) * i / s.ranges.size();
			double dy = fabs( r * sin(a) );
			if (dy <= stop_lateral_distance)
			{
				obs_dist = std::min(obs_dist, r);
				obs_lat = std::min(obs_lat, dy);
			}
		}
	}
	// logger().debug("Obstacle at {} (lateral: {})", obs_dist, obs_lat);

	//auto i = shell().input.read().value;

	if (obs_dist < stop_distance)
	{
		// logger().warn("Obstacle too close: robot is not allowed to go forward");
		ROS_INFO("Obstacle too close: robot is not allowed to go forward\n");
		{
		cmd.linear.x = std::min(0.0, cmd.linear.x);
		cmd.linear.y = std::min(0.0, cmd.linear.y);

		}
	}
	else {/*
		cmd.linear.x = fmin(cmd.linear.x, + max_linear);
		cmd.linear.y = fmin(cmd.linear.y, + max_linear);
		cmd.linear.x = fmax(cmd.linear.x, - max_linear);
		cmd.linear.y = fmax(cmd.linear.y, - max_linear);
		cmd.angular.x = fmin(cmd.angular.x, + max_angular);
		cmd.angular.y = fmin(cmd.angular.y, + max_angular);
		cmd.angular.x = fmax(cmd.angular.x, - max_angular);
		cmd.angular.y = fmax(cmd.angular.y, - max_angular);*/
	}

	// logger().debug("Sending safe command {}", i);
	// shell().output.write(i);
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

void SafetyPilot::safetyPilotCallbackCmdVelCtrl(const geometry_msgs::Twist & cmd_msg)
{
	base_cmd_ctrl_ = cmd_msg;
}


void SafetyPilot::safetyPilotCallbackScan(const sensor_msgs::LaserScan & scan_msg)
{
	scan_=scan_msg;
}

void SafetyPilot::safetyPilotCallbackTeleop(const osmosis_control::TeleopMsg & teleop_msg)
{
	base_cmd_teleop_=teleop_msg;
}


//! ROS node topics publishing and subscribing initialization
SafetyPilot::SafetyPilot()
{
	//set up the publisher for the cmd_vel topic
	cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/summit_xl_a/robotnik_base_control/cmd_vel", 1);
	cmd_vel_sub_  = nh_.subscribe("cmd_vel_control", 1, &SafetyPilot::safetyPilotCallbackCmdVelCtrl, this);
	scan_sub_  = nh_.subscribe("/summit_xl_a/front_laser/scan", 1, &SafetyPilot::safetyPilotCallbackScan, this);
	cmd_vel_teleop_sub_= nh_.subscribe("cmd_vel_teleop", 1, &SafetyPilot::safetyPilotCallbackTeleop, this);
}


bool SafetyPilot::run()
{
	ros::Rate loop_rate(20);
	while (nh_.ok())
	{
		this->computeCommandCtrlTeleop();
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
