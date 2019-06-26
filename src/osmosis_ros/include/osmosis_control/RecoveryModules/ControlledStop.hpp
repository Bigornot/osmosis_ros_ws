/* Copyright 2018 LAAS-CNRS
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

#ifndef OSMOSIS_CONTROLLEDSTOP_HPP
#define OSMOSIS_CONTROLLEDSTOP_HPP


#include <iostream>
#include <cmath>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Bool.h>

#include <osmosis_control/Recov.hpp>


class ControlledStop : public Recov
{
private:
 ros::NodeHandle nh_;
 ros::Publisher ControlledStop_pub_;
 ros::Subscriber Recov1_sub_;

 bool rec1;
 std_msgs::Bool rok;


public:
//constructeur
//! ROS node topics publishing and subscribing initialization
ControlledStop();

//definition methode virtuelle
void pub_topic_recov(std_msgs::Bool donnee);

//methode propre
 void ControlledstopCallbackFTMrules(const std_msgs::Bool & rec1);


}; // end of class

#endif //OSMOSIS_CONTROLSTOP_HPP
