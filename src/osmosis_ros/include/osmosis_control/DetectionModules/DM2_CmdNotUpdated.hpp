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

#ifndef OSMOSIS_DM2_CmdNotUpdated_HPP
#define OSMOSIS_DM2_CmdNotUpdated_HPP

#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <osmosis_control/DetectionModules/DetectionModule.hpp>

class DM2_CmdNotUpdated : public DetectionModule
{
private:
	ros::Subscriber cmd_vel_sub_;
	ros::Time lastUpdate_;
	ros::Duration timeOut_;

public:
	DM2_CmdNotUpdated();
	void detect();
	void DM2_CmdNotUpdatedCallback(const geometry_msgs::Twist &cmd_vel);
};

#endif //OSMOSIS_DM2_CmdNotUpdated_HPP
