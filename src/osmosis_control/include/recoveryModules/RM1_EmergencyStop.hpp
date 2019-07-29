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

#ifndef RM1_EMERGENCYSTOP_HPP
#define RM1_EMERGENCYSTOP_HPP

#include <iostream>
#include <ros/ros.h>
#include <string>
#include <geometry_msgs/Twist.h>
#include <recoveryModules/RecoveryModule.hpp>

class RM1_EmergencyStop : public RecoveryModule
{
private:
	///////// Attributes ////////
	ros::Publisher pub_cmd_;

	///////// Methods ////////
	void startingAction();
	void doRecovery();
	void stoppingAction();

public:
	RM1_EmergencyStop(int id, vector<int> successors);
};

#endif
