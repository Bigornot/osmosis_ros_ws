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
#include <ros/package.h>
#include "std_msgs/Bool.h"
#include "osmosis_control/Hmi_OrderMsg.h"
#include "osmosis_control/Hmi_DoneMsg.h"

struct Mission
{
	std::string name;
	int step;
	std::vector<osmosis_control::State_and_PointMsg> mission_steps;
};

class MissionManager
{
private:
	///////// Attributes ////////
	ros::NodeHandle nh_;
	ros::Publisher goal_pub_;
	ros::Publisher hmi_done_pub_;
	ros::Subscriber goal_reached_sub_;
	ros::Subscriber emergency_sub_;
	ros::Subscriber hmi_order_sub_;

	enum StateDriveMission{IDLE,POINT,MISSION, EMERGENCY_STOP};
	StateDriveMission state_;
	enum StateMission {INITMISSION,EXECUTEMISSION};
	StateMission missionState_;
	enum StatePoint {TARGETPOINT,WAITPOINT};
	StatePoint pointState_;

	osmosis_control::State_and_PointMsg state_and_point_cmd_;
	Mission mission_;
	std::string mission_name_;
	bool emergencyStop_;

	bool goal_reached_;
	bool missionOver_;
	bool missionAborted_;
	bool hmi_point_;
	bool hmi_mission_;

	ros::Time timeStartMission_;
	ros::Duration timeout_;

	/////////  Methods   ////////
	void driveMissionManager();

	void resetIdle();
	bool isGoalReached();

	void goalKeyboard();
	void endPoint();

        void initMission(std::string name);
	void parse(std::string line);
	void doMission();
	bool isMissionOver();
	void sendNextOrder();
	void abortMission();
	void endMission();

public:
	MissionManager();
	void run();

	void CallbackGoalReached(const std_msgs::Bool &goal_reached);
	void CallbackEmergencyStop(const std_msgs::Bool &stop);
	void CallbackOrder(const osmosis_control::Hmi_OrderMsg &order);

}; // end of class

#endif
