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

#ifndef RM3_HPP
#define RM3_HPP

#include <iostream>
#include <cstdlib>
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <ros/master.h>
#include <osmosis_control/RecoveryModules/RecoveryModule.hpp>

class RM3_RespawnControlNodes : public RecoveryModule
{
private:
	ros::V_string nodesToCheck_;

public:
	RM3_RespawnControlNodes(int id, int predecessor, vector<int> successors, ros::Duration delay);
	void doRecovery();
};

#endif 
