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

#ifndef OSMOSIS_DM4_NodeCrashControl_HPP
#define OSMOSIS_DM4_NodeCrashControl_HPP

#include <iostream>
#include <ros/ros.h>
#include <ros/master.h>
#include <detectionModules/DetectionModule.hpp>

class DM4_NodeCrashControl : public DetectionModule
{
private:
	///////// Attributes ////////
	ros::V_string aliveNodes_;
	ros::V_string nodesToCheck_;

	///////// Methods ////////
	void detect();

public:
	DM4_NodeCrashControl();
	void init();
};

#endif //OSMOSIS_DM4_NodeCrashControl_HPP
