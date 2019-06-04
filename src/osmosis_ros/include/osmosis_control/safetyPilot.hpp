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

#ifndef OSMOSIS_SAFETYPILOT_HPP
#define OSMOSIS_SAFETYPILOT_HPP


#include <iostream>
#include <cmath>

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>
#include "osmosis_control/TeleopMsg.h"


const double stop_distance = 0.8;
const double stop_lateral_distance = 0.3;
const double  max_linear = 1.0;
const double max_angular = 0.4;



class SafetyPilot
{
private:
	ros::NodeHandle nh_;
	ros::Publisher cmd_vel_pub_;
	ros::Subscriber cmd_vel_sub_;
	ros::Subscriber scan_sub_;
	ros::Subscriber cmd_vel_teleop_sub_;
	geometry_msgs::Twist base_cmd_ctrl_;
	geometry_msgs::Twist base_cmd_;
	osmosis_control::TeleopMsg base_cmd_teleop_;
	sensor_msgs::LaserScan scan_;

public:

	// from MAUVE safetyPilot update operation
	geometry_msgs::Twist updateCmdWithLaserScan(geometry_msgs::Twist cmd,sensor_msgs::LaserScan s);

	// from MAUVE "priority" ressource: choose between teleop or control
	void computeCommandCtrlTeleop();

	void safetyPilotCallbackCmdVelCtrl(const geometry_msgs::Twist & cmd_msg);


	void safetyPilotCallbackScan(const sensor_msgs::LaserScan & scan_msg);


	void safetyPilotCallbackTeleop(const osmosis_control::TeleopMsg & teleop_msg);


	//! ROS node topics publishing and subscribing initialization
	SafetyPilot();

	bool run();


}; // end of class

#endif //OSMOSIS_SAFETYPILOT_HPP
