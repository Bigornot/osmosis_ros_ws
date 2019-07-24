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
#include "osmosis_control/GoalMsg.h"
#include "osmosis_control/MissionMsg.h"

using namespace std;

class HMI
{
private:
	///////// Attributes /////////
	ros::NodeHandle nh_;
	double freq_;
	ros::Publisher mission_pub_;
	ros::Subscriber done_sub_;

	enum StateDriveHMI{IDLE,REACH_POINT_MISSION,RUNWAY_MISSION};
	StateDriveHMI state_;
	enum StateMission {ASK_MISSION,WAIT_END_MISSION};
	StateMission mission_state_;

	osmosis_control::MissionMsg mission_cmd_;

	bool goal_reached_;
	bool mission_done_;

	/////////  Methods   ////////
	void HMI_FSM();

	void missionDone();
	char askMode();
	void goalKeyboard();
	bool askMission();
	bool checkMission(std::string name);

	void publishMission();

public:
	HMI();
	void run();

	void callbackMissionDone(const std_msgs::Bool &done);
};

#endif
