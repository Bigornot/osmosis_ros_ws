#include <osmosis_control/detectionModules/DM6_LocNotUpdated.hpp>

//! ROS node topics publishing and subscribing initialization
DM6_LocNotUpdated::DM6_LocNotUpdated() : DetectionModule()
{
	pose_sub_  = nh_.subscribe("/pose", 1, &DM6_LocNotUpdated::DM6_LocNotUpdatedCallback, this);

	//ros::Duration(1).sleep();

	lastUpdate_=ros::Time::now();
	timeOut_ = ros::Duration(1);
}

void DM6_LocNotUpdated::init()
{
	lastUpdate_=ros::Time::now();
}

void DM6_LocNotUpdated::detect()
{
	ros::Duration delay = ros::Time::now()-lastUpdate_;
	if(delay>timeOut_)
		state_=true;
	else
		state_ = false;
}

void DM6_LocNotUpdated::DM6_LocNotUpdatedCallback(const geometry_msgs::Pose2D &pose)
{
	lastUpdate_ = ros::Time::now();
}

