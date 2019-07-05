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

#ifndef OSMOSIS_EMERGENCY_SHUTDOWN_HPP
#define OSMOSIS_EMERGENCY_SHUTDOWN_HPP

#include <iostream>
#include <ros/ros.h>
#include <string>
#include <ros/package.h>
#include "std_msgs/Bool.h"

class EmergencyShutdown
{
private:
	ros::NodeHandle nh_;
	ros::Publisher emergency_pub_;
	enum StateDriveEmergency{NOMINAL,EMERGENCYHIT,EMERGENCY};
	StateDriveEmergency state_;
  std_msgs::Bool emergency_;

public:
	EmergencyShutdown();
	void run();
	void driveEmergencyShutdown();
}; // end of class

#endif
