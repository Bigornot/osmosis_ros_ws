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

#ifndef OSMOSIS_DM3_WrongCommand_HPP
#define OSMOSIS_DM3_WrongCommand_HPP

#include <iostream>
#include <cmath>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Bool.h>
#include <osmosis_control/DetectionModules/DetectionModule.hpp>

class DM3_WrongCommand : public DetectionModule
{
private:
  ros::Publisher DM3_pub_;
  ros::Subscriber cmd_sub_;
  geometry_msgs::Twist cmd_;
  float cmd_linear_x_max_;
  float cmd_angular_z_max_;

public:
  bool detect();
  void pub_to_FTM(std_msgs::Bool donnee);
  void DM3_WrongCommandCallback(const geometry_msgs::Twist & cmd_msg);
  DM3_WrongCommand();

}; // end of class

#endif //OSMOSIS_DM3_WrongCommand_HPP
