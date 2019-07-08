#include <osmosis_control/DetectionModules/DM2_CmdNotUpdated.hpp>

//! ROS node topics publishing and subscribing initialization
DM2_CmdNotUpdated::DM2_CmdNotUpdated() : DetectionModule()
{
	cmd_vel_sub_  = nh_.subscribe("summit_xl_a/robotnik_base_control/cmd_vel", 1, &DM2_CmdNotUpdated::DM2_CmdNotUpdatedCallback, this);

	//ros::Duration(1).sleep();

	lastUpdate_=ros::Time::now();
	timeOut_ = ros::Duration(1);
}

bool DM2_CmdNotUpdated::detect()
{
	if(ros::Time::now()-lastUpdate_>timeOut_)
		return true;
	else
		return false;
}

void DM2_CmdNotUpdated::DM2_CmdNotUpdatedCallback(const geometry_msgs::Twist &cmd_vel)
{
	lastUpdate_ = ros::Time::now();
}

