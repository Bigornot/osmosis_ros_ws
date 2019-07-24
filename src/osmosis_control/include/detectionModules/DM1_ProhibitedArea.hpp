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
#include <std_msgs/Bool.h>
#include <detectionModules/DetectionModule.hpp>

class DM1_ProhibitedArea : public DetectionModule
{
private:
	///////// Attributes ////////
	ros::Subscriber state_sub_;

	///////// Methods ////////
	void detect();

public:
	DM1_ProhibitedArea();
	void init();
	void DM1_ProhibitedAreaCallback(const std_msgs::Bool & state);
};

#endif //OSMOSIS_DM1_ProhibitedArea_HPP
