#include <osmosis_control/DetectionModules/DM6_LocNotUpdated.hpp>

//! ROS node topics publishing and subscribing initialization
DM6_LocNotUpdated::DM6_LocNotUpdated() : DetectionModule()
{
	pose_sub_  = nh_.subscribe("/pose", 1, &DM6_LocNotUpdated::DM6_LocNotUpdatedCallback, this);

	//ros::Duration(1).sleep();

	lastUpdate_=ros::Time::now();
	timeOut_ = ros::Duration(1);
}

bool DM6_LocNotUpdated::detect()
{
	if(ros::Time::now()-lastUpdate_>timeOut_)
		return true;
	else
		return false;
}

void DM6_LocNotUpdated::DM6_LocNotUpdatedCallback(const geometry_msgs::Pose2D &pose)
{
	lastUpdate_ = ros::Time::now();
}

