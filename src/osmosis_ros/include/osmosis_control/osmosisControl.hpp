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

#ifndef OSMOSIS_CONTROL_HPP
#define OSMOSIS_CONTROL_HPP

#include <iostream>

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Pose.h>
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose2D.h>
#include <tf/transform_broadcaster.h>
#include <std_msgs/Bool.h>
#include "osmosis_control/State_and_PointMsg.h"
#include <osmosis_control/common.hpp>

const double obstacle_distance=0.9;
const double safety_distance=0.9;
const double nu=0.1;
const double psi=0.1;

class OsmosisControl
{
private:
	ros::NodeHandle nh_;
	double freq_;
	ros::Publisher cmd_vel_pub_;
	ros::Publisher goal_reach_pub_;

	ros::Subscriber emergency_stop_sub_;
	ros::Subscriber odom_sub_;
	ros::Subscriber scan_sub_;
	ros::Subscriber goal_sub_;

	geometry_msgs::Pose2D robot_pose;
	geometry_msgs::Point obstacle;
	osmosis_control::State_and_PointMsg state_and_target_;
	double obstacle_lw, obstacle_radius;
	geometry_msgs::Point old_goal_;
	geometry_msgs::Twist cmd_;

	sensor_msgs::LaserScan scan_;
	nav_msgs::Odometry odom_;

	enum State {WAIT_GOAL, MOVE_TO_GOAL, ARRIVED_GOAL, EMERGENCY_STOP};
	State state_;

	bool emergency_stop_;

public:

	void callbackGoal(const osmosis_control::State_and_PointMsg & thegoal);
	void callbackScan(const sensor_msgs::LaserScan & thescan);
	void callbackPose(const geometry_msgs::Pose2D & msg);
	void callbackEmergencyStop(const std_msgs::Bool &stop);
	void publish_is_arrived();

	//! ROS node initialization
	OsmosisControl();

	bool new_goal();
	bool is_arrived();

	void stop();

	void updateMove();

	bool obstacleFromScan(const sensor_msgs::LaserScan& scan);

	geometry_msgs::Twist PF(double x_p, double y_p,
	double theta_p, double obs_dx, double obs_dy);

	bool run();

	void osmosisControlFSM();


}; // end of class

#endif //OSMOSIS_CONTROL_HPP
