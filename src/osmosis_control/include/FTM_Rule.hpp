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

#ifndef DEF_FTM_RULE
#define DEF_FTM_RULE

#include <iostream>
#include "ros/ros.h"
#include <string>
#include "std_msgs/Bool.h"
#include <vector>

#include <detectionModules/DetectionModule.hpp>
#include <recoveryModules/RecoveryModule.hpp>

class FTM_Rule
{
private:
	///////// Attributes ////////
	ros::NodeHandle nh_;

	DetectionModule* DM_;
	RecoveryModule* RM_;

	enum RunState{IDLE, ACTIVE, RECOVERY};
	RunState state_;

	int id_;
	int predecessor_;
	vector<int> successors_;


public:
	void runFSM();

	FTM_Rule(int id, int predecessor, vector<int> successor, DetectionModule* DM, RecoveryModule* RM);

	int getState();
	int getPredecessorId();
	vector<int> getSuccessorsId();
	int getId();

	void initDM();
	void runDM();
	int getStateDM();

	void runRM();
	int getStateRM();
	void startRM();
	void stopRM();
	int getRMId();
	vector<int> getRMSuc();
};

#endif
