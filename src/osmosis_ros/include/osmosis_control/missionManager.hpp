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

 
#ifndef OSMOSIS_MISSION_MANAGER_HPP
#define OSMOSIS_MISSION_MANAGER_HPP

#include <iostream>
#include <ros/ros.h>
#include <fstream>
#include <vector>
#include <string>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <ros/package.h>
#include "std_msgs/Bool.h"
#include "osmosis_control/State_and_PointMsg.h"

struct Mission
{
	std::string name;
	int step;
	std::vector<geometry_msgs::Point> orders;
};

class MissionManager
{
private:
	ros::NodeHandle nh_;
	ros::Publisher goal_pub_;
	ros::Subscriber goal_reached_sub_;
	//geometry_msgs::Point goal_;
	osmosis_control::State_and_PointMsg state_and_point_cmd_;
	enum StateDriveMission{CHOICE,KEYBOARD,MISSION};
	StateDriveMission state_;
	enum StateMission {WAITMISSION,WAITORDERDONE};
	StateMission missionState_;
	Mission mission_;
	bool goal_reached_;
	bool pub_on_;
	
public:
	MissionManager();
	void goalKeyboard();
	void run();
        bool initMission(std::string name);
	void parse(std::string line);

	bool doMission();
	bool isMissionOver();
	void sendNextOrder();
	char askMode();
	bool askMission();

	void driveMissionManager();
	void MissionManagerCallbackGoalReached(const std_msgs::Bool &goal_reached);
	bool is_goal_reached();
}; // end of class

#endif
