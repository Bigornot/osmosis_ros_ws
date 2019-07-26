/*
 * Copyright 2019 LAAS-CNRS
 * MESSIOUX Antonin / FAVIER Anthony
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

#ifndef OSMOSIS_JOY_TELEOP_HPP
#define OSMOSIS_JOY_TELEOP_HPP

#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include "osmosis_control/TeleopMsg.h"
#include <sensor_msgs/Joy.h>
#include <vector>

using namespace std;

class JoyTeleop
{
private:
	///////// Attributes ////////
	ros::NodeHandle nh_;
	double freq_;

	ros::Publisher cmd_joy_teleop_pub_;
	ros::Subscriber cmd_joystick_sub_;

	osmosis_control::TeleopMsg joy_teleop_cmd_;
	sensor_msgs::Joy joy_msg_;
	enum StateTeleop {DESACTIVATED, ACTIVATED};
	StateTeleop state_;
	bool button_pressed_;
	bool pub_on_;

	///////// Methods ////////
	void JoyFSM();
	void joy_on();
	void joy_off();

public:
	JoyTeleop();

	void run();

	void teleopCallbackJoy(const sensor_msgs::Joy & joy_msg);

}; // end of class

#endif
