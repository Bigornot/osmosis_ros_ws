/* Copyright 2018 LAAS-CNRS
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

#ifndef OSMOSIS_DM1_ProhibitedArea_HPP
#define OSMOSIS_DM1_ProhibitedArea_HPP

#include <iostream>
#include <cmath>
#include <ros/ros.h>
#include <geometry_msgs/Pose2D.h>
#include <std_msgs/Bool.h>
#include <osmosis_control/DetectionModule.hpp>

class DM1_ProhibitedArea : public DetectionModule
{
private:
	ros::NodeHandle nh_;
	ros::Publisher DM1_pub_;
	ros::Subscriber position_sub_;
	geometry_msgs::Pose2D robot_pose_;
	float x_min;
	float x_max;
	float y_min;
	float y_max;

public:
	bool detect();
	void pub_to_FTM(std_msgs::Bool donnee);
	void DM1_ProhibitedAreaCallback(const geometry_msgs::Pose2D & position_msg);
	DM1_ProhibitedArea();

};

#endif //OSMOSIS_DM1_ProhibitedArea_HPP
