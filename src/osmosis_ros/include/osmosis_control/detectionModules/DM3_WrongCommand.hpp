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

#ifndef OSMOSIS_DM3_WrongCommand_HPP
#define OSMOSIS_DM3_WrongCommand_HPP

#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <osmosis_control/detectionModules/DetectionModule.hpp>

class DM3_WrongCommand : public DetectionModule
{
private:
	///////// Attributes ////////
	ros::Subscriber cmd_sub_;
	geometry_msgs::Twist cmd_;
	float cmd_linear_x_max_;
	float cmd_linear_x_min_;
	float cmd_angular_z_max_;
	float cmd_angular_z_min_;

	///////// Methods ////////
	void detect();

public:
	DM3_WrongCommand();
	void init();
	void DM3_WrongCommandCallback(const geometry_msgs::Twist & cmd_msg);

}; // end of class

#endif //OSMOSIS_DM3_WrongCommand_HPP
