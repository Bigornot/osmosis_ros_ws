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

#ifndef OSMOSIS_TELEOP_HPP
#define OSMOSIS_TELEOP_HPP

#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include "osmosis_control/TeleopMsg.h"

class Teleop
{
private:
	ros::NodeHandle nh_;
	ros::Publisher cmd_teleop_pub_;
	osmosis_control::TeleopMsg teleop_cmd_;
	//ros::Subscriber cmd_joystick_sub_;
	//teleop_msgs base_cmd_teleop_;
	enum StateTeleop {DESACTIVATED, ACTIVATED};
	StateTeleop state_;


public:

	void driveKeyboard();
	Teleop();
	void run();

}; // end of class

#endif
