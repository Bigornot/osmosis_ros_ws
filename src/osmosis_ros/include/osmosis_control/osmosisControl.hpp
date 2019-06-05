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
#include <osmosis_control/common.hpp>


const double obstacle_distance=0.9;
const double safety_distance=0.9;
const double nu=0.1;
const double psi=0.1;




class OsmosisControl
{
private:


  ros::NodeHandle nh_;
  ros::Publisher cmd_vel_pub_;
  ros::Publisher goal_reach_pub_;

	geometry_msgs::Pose2D robot_pose;
	geometry_msgs::Point goal,obstacle;
	double obstacle_lw, obstacle_radius;
	//bool new_goal_, is_arrived_;
	geometry_msgs::Point old_goal_;
	geometry_msgs::Twist cmd_;

	ros::Subscriber scan_sub_;
	sensor_msgs::LaserScan scan_;
	ros::Subscriber odom_sub_;
	nav_msgs::Odometry odom_;
	ros::Subscriber goal_sub_;

	enum State {wait_goal,move_to_goal,arrived_goal};
	State state_;

public:

	void osmosisControlCallbackGoal(const geometry_msgs::Point & thegoal);

	void osmosisControlCallbackScan(const sensor_msgs::LaserScan & thescan);

	void osmosisControlCallbackPose(const geometry_msgs::Pose2D & msg);
  void publish_is_arrived();

	//! ROS node initialization
	OsmosisControl();

	bool new_goal();
	bool is_arrived();

	void stop();

	void updateMove();

	void obstacleFromScan(const sensor_msgs::LaserScan& scan);

	geometry_msgs::Twist PF(double x_p, double y_p,
	    double theta_p, double obs_dx, double obs_dy);



	bool run();

	void osmosisControlFSM();


}; // end of class

#endif //OSMOSIS_CONTROL_HPP