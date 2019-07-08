/*
* Copyright 2018 LAAS-CNRS
*
* This file is part of the OSMOSIS project.
*
* Osmosis is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 3 as
* published by the Free Software Foundation.
*
* Osmosis is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
*/

#ifndef OSMOSIS_LOCALIZATION_HPP
#define OSMOSIS_LOCALIZATION_HPP

#include <iostream>

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Pose.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose2D.h>
#include <tf/transform_broadcaster.h>
#include <osmosis_control/common.hpp>

class Localization
{
private:
	ros::NodeHandle nh_;
	double freq_;
	ros::Publisher pose_pub_;
	ros::Subscriber odom_sub_;
	nav_msgs::Odometry odom_;
	geometry_msgs::Pose2D robot_pose;
public:
	void localizationCallbackOdom(const nav_msgs::Odometry::ConstPtr& msg);
	bool run();
	Localization();

};

#endif //OSMOSIS_LOCALIZATION_HPP
