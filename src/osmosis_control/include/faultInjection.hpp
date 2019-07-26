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

#ifndef OSMOSIS_FAULT_INJECTION_HPP
#define OSMOSIS_FAULT_INJECTION_HPP

#include <iostream>
#include <cstdlib>
#include <ros/ros.h>
#include <vector>
#include <string>
#include <ros/package.h>
#include "std_msgs/Bool.h"

using namespace std;

class FaultInjection
{
private:
	///////// Attributes ////////
	ros::NodeHandle nh_;

	ros::Publisher FI1_pub_;
	ros::Publisher FI2_pub_;
	ros::Publisher FI3_pub_;
	ros::Publisher FI6_pub_;

	enum StateFSM{IDLE,FAULT_INJECTION};
	StateFSM state_;

	double freq_;
	
	vector<int> list_FI_;

	/////////  Methods   ////////
	void FaultInjectionFSM();
	bool askFI();
	bool parse(string select);
	void doFI();

public:
	FaultInjection();
	void run();

}; // end of class

#endif
