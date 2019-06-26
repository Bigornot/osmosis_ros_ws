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

#ifndef OSMOSIS_EMERGENCYSTOP_HPP
#define OSMOSIS_EMERGENCYSTOP_HPP


#include <iostream>
#include <cmath>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Bool.h>

#include <osmosis_control/Recov.hpp>


class EmergencyStop : public Recov
{
private:
 ros::NodeHandle nh_;
 ros::Publisher EmergencyStop_pub_;
 ros::Subscriber Recov2_sub_;

 bool rec2;
 std_msgs::Bool donnee;


public:
//constructeur
//! ROS node topics publishing and subscribing initialization
EmergencyStop();

//definition methode virtuelle
void pub_topic_recov(std_msgs::Bool donnee);

//methode propre
 void EmergencystopCallbackFTMrules(const std_msgs::Bool & rec2);


}; // end of class

#endif //OSMOSIS_EMERGENCYSTOP_HPP
