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

#ifndef OSMOSIS_GRAPHPLANNER_HPP
#define OSMOSIS_GRAPHPLANNER_HPP


#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Pose2D.h>
#include <std_msgs/Bool.h>
#include "osmosis_control/GoalMsg.h"
#include <ros/package.h>

#include <graph.hpp>
#include <graphIO.hpp>

using namespace std;

class GraphPlanner
{
private:
	///////// Attributes ////////
	ros::NodeHandle nh_;

	double freq_;

	ros::Publisher target_pub_;
	ros::Publisher goal_reached_pub_;
	ros::Subscriber goal_sub_;
	ros::Subscriber target_reached_sub_;
	ros::Subscriber odom_sub_;
	ros::Subscriber emergency_stop_sub_;
	geometry_msgs::Point current;

	osmosis_control::GoalMsg target_;
	osmosis_control::GoalMsg mission_goal_;
	Graph graph;
	std::vector<geometry_msgs::Point> plan;
	int target_index;
	bool _new_goal;
	bool target_reached_;
	bool emergency_stop_;

	enum State {WAIT_GOAL,WAIT_COMPUTE_PLAN,SEND,FOLLOW,GOAL_DONE,EMERGENCY_STOP};
	State state_;

	///////// Methods ////////
	void graphPlannerFSM();

	bool new_goal();
	void compute_plan();
	bool plan_computed();
	bool plan_done();
	bool is_arrived();
	void execute_plan();

	void publishDone();
	void publishSendTarget();

	//void read_ports();
	//bool no_goal();

public:
	GraphPlanner();

	void initGraph(const std::string& filename);
	void run();

	void callbackGoal(const osmosis_control::GoalMsg & thegoal);
	void callbackPose(const geometry_msgs::Pose2D & msg);
	void callbackTargetReached(const std_msgs::Bool & target_reached);
	void callbackEmergencyStop(const std_msgs::Bool &emergency_stop);

	//void GraphPlanner::callbackGoalId(const string & thegoal_id)

}; // end of class

#endif
