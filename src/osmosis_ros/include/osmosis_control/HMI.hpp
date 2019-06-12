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

class HMI
{
private:
	ros::NodeHandle nh_;
	ros::Publisher orders_pub_;
	ros::Subscriber done_sub_;
	enum StateDriveHMI{IDLE,POINT,MISSION};
	StateDriveHMI state_;
	enum StateMission {WAITMISSION,EXECUTEMISSION};
	StateMission missionState_;
	enum StatePoint {TARGETPOINT,WAITPOINT};
	StatePoint pointState_;
	ros::Time timeStartMission_;
	ros::Duration timeout_;
	Mission mission_;
	osmosis_control::State_and_PointMsg state_and_point_cmd_;
	osmosis_control::Hmi_OrderMsg orders_cmd_;

public:
	HMI();

	bool goal_reached_;
	bool pub_on_;
	bool missionOver_;
	bool missionAborted_;
	bool done_mission_;
	bool done_point_;

	void goalKeyboard();
	void run();
  bool initMission(std::string name);
	void parse(std::string line);

	void doMission();
	char askMode();
	bool askMission();
  void HMICallbackHmiOrder(const std_msgs::DoneMsg &done);
	void driveHMI();


}; // end of class

#endif
