#include <osmosis_control/detectionModules/DM2_CmdNotUpdated.hpp>


////////////////////// PRIVATE //////////////////////

void DM2_CmdNotUpdated::detect()
{
	ros::Duration delay = ros::Time::now()-lastUpdate_;
	if(delay>timeOut_)
		state_=true;
	else
		state_=false;
}


////////////////////// PUBLIC //////////////////////

DM2_CmdNotUpdated::DM2_CmdNotUpdated() : DetectionModule()
{
	cmd_vel_sub_  = nh_.subscribe("summit_xl_a/robotnik_base_control/cmd_vel", 1, &DM2_CmdNotUpdated::DM2_CmdNotUpdatedCallback, this);

	lastUpdate_=ros::Time::now();
	timeOut_ = ros::Duration(1);
}

void DM2_CmdNotUpdated::init()
{
	lastUpdate_=ros::Time::now();
}

void DM2_CmdNotUpdated::DM2_CmdNotUpdatedCallback(const geometry_msgs::Twist &cmd_vel)
{
	lastUpdate_ = ros::Time::now();
}

