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

#ifndef RM5_SWITCHTOTELEOPHPP
#define RM5_SWITCHTOTELEOPHPP

#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <recoveryModules/RecoveryModule.hpp>

class RM5_SwitchToTeleop : public RecoveryModule
{
private:
	///////// Attributes ////////
	ros::Publisher pub_;
	double pollRate_;
	double delaySend_;
	ros::Time start_;

	///////// Methods ////////
	void startingAction();
	void doRecovery();
	void stoppingAction();

public:
	RM5_SwitchToTeleop(int id, vector<int> successors);
};

#endif
