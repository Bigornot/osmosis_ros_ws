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
	std::vector<osmosis_control::State_and_PointMsg> orders;
};

class MissionManager
{
private:
	ros::NodeHandle nh_;
	ros::Publisher goal_pub_;
	ros::Subscriber goal_reached_sub_;
	//geometry_msgs::Point goal_;
	osmosis_control::State_and_PointMsg state_and_point_cmd_;
	enum StateDriveMission{IDLE,TARGETPOINT,MISSION};
	StateDriveMission state_;
	enum StateMission {WAITMISSION,EXECUTEMISSION};
	StateMission missionState_;
	Mission mission_;
	bool goal_reached_;
	bool pub_on_;
	bool missionOver_;
	bool missionAborted_;
	ros::Time timeStartMission_;
	ros::Duration timeout_;

public:
	MissionManager();
	void goalKeyboard();
	void run();
        bool initMission(std::string name);
	void parse(std::string line);

	void doMission();
	bool isMissionOver();
	void sendNextOrder();
	char askMode();
	bool askMission();

	void driveMissionManager();
	void MissionManagerCallbackGoalReached(const std_msgs::Bool &goal_reached);
  void MissionManagerCallbackEmergencyHit(const std_msgs::Bool &emergency_hit);
	bool is_goal_reached();
}; // end of class

#endif
