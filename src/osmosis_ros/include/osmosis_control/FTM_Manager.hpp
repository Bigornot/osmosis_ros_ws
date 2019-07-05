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

#ifndef DEF_FTM_MANAGER
#define DEF_FTM_MANAGER

#include <iostream>
#include <ros/ros.h>
#include <vector>
#include <osmosis_control/Tree.hpp>

using namespace std;

class FTM_Manager
{
private:
	ros::NodeHandle nh_;

	enum Strategies{SAFETY_FIRST};
	Strategies strategy_;

	vector<FTM_Rule*> Triggered_FTM;
	vector<FTM_Rule*> dominant;
	vector<FTM_Rule*> dominant_recov;

	FTM_Rule* commonDominant;


	Tree FTM_Tree_;
public:
	FTM_Manager();
	bool run();
};

#endif
