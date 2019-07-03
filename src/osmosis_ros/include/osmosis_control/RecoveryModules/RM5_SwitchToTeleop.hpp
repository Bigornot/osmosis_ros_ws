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
#include <osmosis_control/RecoveryModules/RecoveryModule.hpp>

class RM5_SwitchToTeleop : public RecoveryModule
{
private:
	ros::Publisher pub_;

public:
	RM5_SwitchToTeleop(int id, int antecedent, vector<int> successors);
	void doRecovery();
};

#endif 
