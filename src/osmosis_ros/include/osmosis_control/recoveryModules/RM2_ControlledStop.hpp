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

#ifndef RM2_CONTROLLEDSTOPHPP
#define RM2_CONTROLLEDSTOPHPP

#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <geometry_msgs/Twist.h>
#include <osmosis_control/recoveryModules/RecoveryModule.hpp>

class RM2_ControlledStop : public RecoveryModule
{
private:
	ros::Publisher pub_order_;
	ros::Publisher pub_cmd_;
	double pollRate_;
	double delaySend_;
	ros::Time start_;

public:
	RM2_ControlledStop(int id, vector<int> successors);
	void startRecovery();
	void doRecovery();
	void stopRecovery();
};

#endif 
