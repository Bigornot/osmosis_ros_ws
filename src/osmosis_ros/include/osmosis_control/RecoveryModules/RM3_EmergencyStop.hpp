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

#ifndef RM3_EMERGENCYSTOP_HPP
#define RM3_EMERGENCYSTOP_HPP

#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <osmosis_control/RecoveryModules/RecoveryModule.hpp>

class RM3_EmergencyStop : public RecoveryModule
{
  private:
    ros::Publisher RM3_EmergencyStop_pub_;
    bool r3;
    std_msgs::Bool donnee;

  public:
    RM3_EmergencyStop();
    void pub_topic_recov(std_msgs::Bool donnee);
    void RM3_EmergencyStopCallback(const std_msgs::Bool & r3);
};

#endif 
