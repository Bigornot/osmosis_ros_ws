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
#include "osmosis_control/State_and_PointMsg.h"
#include <ros/package.h>


#include <osmosis_control/graph.hpp>
#include <osmosis_control/graphIO.hpp>

const double TH=0.5;

class GraphPlanner {

    public:
      GraphPlanner();
      void read_ports();
      void compute_plan();
      void execute_plan();
      bool new_goal();
      bool no_goal();
      bool plan_computed();
      bool is_arrived();
      bool plan_done();
      void done();
      void send_target();
      void graphPlannerFSM();

      void callbackGoal(const osmosis_control::State_and_PointMsg & thegoal);
      void callbackPose(const geometry_msgs::Pose2D & msg);
      void callbackTargetReached(const std_msgs::Bool & target_reached);

      void initGraph(const std::string& filename);
      void run();


    private:
      ros::NodeHandle nh_;
      ros::Publisher target_pub_;
      ros::Publisher goal_reached_pub_;
    //  ros::Subscriber goal_id_sub_;
      ros::Subscriber goal_sub_;
      ros::Subscriber target_reached_sub_;
      //geometry_msgs::Pose2D robot_pose;
      ros::Subscriber odom_sub_;
      geometry_msgs::Point target_;
      geometry_msgs::Point current;

      osmosis_control::State_and_PointMsg state_and_target_;	
      osmosis_control::State_and_PointMsg state_and_goal_;	
      Graph graph;
      std::vector<geometry_msgs::Point> plan;
      int target_index;
      bool _new_goal;
      bool target_reached_;
    //  std::string goal_id

      enum State {wait_goal,wait_compute_plan,send,follow,goal_done};
      State state_;

    }; // end of class


#endif
