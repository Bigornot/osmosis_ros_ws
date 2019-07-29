#include <iostream>
#include <ros/ros.h>
#include "osmosis_control/MissionMsg.h"
#include <std_msgs/Bool.h>

using namespace std;

ros::Time time_begin;
ros::Time time_end;


void callbackBegin(const osmosis_control::MissionMsg & msg)
{
	time_begin = ros::Time::now();
	ROS_INFO("Mission beginning !");
}

void callbackEnd(const std_msgs::Bool & msg)
{
	time_end = ros::Time::now();
	ros::Duration duration = time_end - time_begin;

	ROS_INFO("The mission took %f s to finish.\n", duration.toSec());

	ROS_INFO("Waiting for a mission to start.");
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "chrono_node");

	ros::NodeHandle nh;

	ros::Subscriber sub_begin = nh.subscribe("/mission", 1, &callbackBegin);
	ros::Subscriber sub_end = nh.subscribe("/hmi_done", 1, &callbackEnd);

	ROS_INFO("Waiting for a mission to start.");
	
	ros::spin();

	return 0;
}

