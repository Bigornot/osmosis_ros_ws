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

#ifndef OSMOSIS_HMI_HPP
#define OSMOSIS_HMI_HPP

#include <iostream>
#include <ros/ros.h>
#include <fstream>
#include <string>
#include <ros/package.h>
#include "std_msgs/Bool.h"
#include "osmosis_control/State_and_PointMsg.h"
#include "osmosis_control/Hmi_OrderMsg.h"
#include "osmosis_control/Hmi_DoneMsg.h"

class HMI
{
private:
	///////// Attributes /////////
	ros::NodeHandle nh_;
	ros::Publisher orders_pub_;
	ros::Subscriber emergency_stop_sub_;
	ros::Subscriber done_sub_;

	enum StateDriveHMI{IDLE,POINT,MISSION, EMERGENCY_STOP};
	StateDriveHMI state_;
	enum StateMission {ASKMISSION,WAITMISSION};
	StateMission missionState_;
	enum StatePoint {TARGETPOINT,WAITPOINT};
	StatePoint pointState_;

	bool goal_reached_;
	bool done_mission_;
	bool done_point_;

	bool emergency_stop_;

	/////////  Methods   ////////
	void driveHMI();

	void ordersDone();
	char askMode();

	void goalKeyboard();

	bool askMission();
	bool checkMission(std::string name);

public:
	HMI();
	void run();

	void CallbackOrderDone(const osmosis_control::Hmi_DoneMsg &done);
	void CallbackEmergencyStop(const std_msgs::Bool &stop);

}; // end of class

#endif
