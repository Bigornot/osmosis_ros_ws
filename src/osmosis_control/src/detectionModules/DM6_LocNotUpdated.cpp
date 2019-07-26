#include <detectionModules/DM6_LocNotUpdated.hpp>


////////////////////// PRIVATE //////////////////////

void DM6_LocNotUpdated::detect()
{
	ros::Duration delay = ros::Time::now()-lastUpdate_;
	if(delay>timeOut_)
		state_=true;
	else
		state_ = false;
}


////////////////////// PUBLIC //////////////////////

DM6_LocNotUpdated::DM6_LocNotUpdated() : DetectionModule()
{
	pose_sub_  = nh_.subscribe("/pose", 1, &DM6_LocNotUpdated::DM6_LocNotUpdatedCallback, this);

	lastUpdate_=ros::Time::now();
	timeOut_ = ros::Duration(1);
}

void DM6_LocNotUpdated::init()
{
	lastUpdate_=ros::Time::now();
}

void DM6_LocNotUpdated::DM6_LocNotUpdatedCallback(const geometry_msgs::Pose2D &pose)
{
	lastUpdate_ = ros::Time::now();
}
