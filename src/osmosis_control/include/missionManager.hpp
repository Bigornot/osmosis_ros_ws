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

#ifndef OSMOSIS_MISSION_MANAGER_HPP
#define OSMOSIS_MISSION_MANAGER_HPP

#include <iostream>
#include <ros/ros.h>
#include <fstream>
#include <vector>
#include <string>
#include <ros/package.h>
#include "std_msgs/Bool.h"
#include "osmosis_control/MissionMsg.h"

using namespace std;

struct Mission
{
	string name;
	int step;
	vector<osmosis_control::GoalMsg> mission_steps;
};

class MissionManager
{
private:
	///////// Attributes ////////
	ros::NodeHandle nh_;
	ros::Publisher goal_pub_;
	ros::Publisher hmi_done_pub_;
	ros::Subscriber goal_reached_sub_;
	ros::Subscriber hmi_mission_sub_;

	enum StateDriveMission{IDLE,REACH_POINT_MISSION,RUNWAY_MISSION};
	StateDriveMission state_;
	enum StateMission {INIT_MISSION,EXECUTE_MISSION};
	StateMission mission_state_;

	Mission mission_;
	osmosis_control::MissionMsg mission_msg_;
	bool mission_received_=true;

	osmosis_control::GoalMsg goal_cmd_;

	bool goal_reached_;
	bool mission_over_;

	std_msgs::Bool done_;

	/////////  Methods   ////////
	void MissionManagerFSM();

	bool isGoalReached();

	void goalKeyboard();
	void endPoint();

	void initMission(string name);
	void parse(string line);
	bool checkNextStep();
	bool isMissionOver();
	void nextStep();
	void endMission();

	void publishMissionGoal();
	void publishDone();

public:
	MissionManager();
	void run();

	void callbackGoalReached(const std_msgs::Bool &goal_reached);
	void callbackMission(const osmosis_control::MissionMsg &mission);

}; // end of class

#endif
