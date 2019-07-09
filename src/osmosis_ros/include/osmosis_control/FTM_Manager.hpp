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
#include <osmosis_control/FTM_Tree.hpp>

using namespace std;

class FTM_Manager
{
private:
	ros::NodeHandle nh_;
	double freq_;

	enum Strategies{SAFETY_FIRST};
	Strategies strategy_;

	vector<FTM_Rule*> triggered_rules_;
	vector<FTM_Rule*> dominant_;
	vector<FTM_Rule*> dominant_recov_;
	FTM_Rule* common_dominant_;

	FTM_Tree FTM_tree_;

public:
	FTM_Manager();
	bool run();
};

#endif
