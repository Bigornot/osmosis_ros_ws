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

#ifndef OSMOSIS_DM5_NodeCrash_HPP
#define OSMOSIS_DM5_NodeCrash_HPP

#include <iostream>
#include <ros/ros.h>
#include <ros/master.h>
#include <std_msgs/Bool.h>
#include <osmosis_control/DetectionModules/DetectionModule.hpp>

class DM5_NodeCrash : public DetectionModule
{
private:
	ros::Publisher DM5_pub_;
	ros::V_string aliveNodes_;
	ros::V_string nodesToCheck_;

public:
	bool detect();
	void pub_to_FTM(std_msgs::Bool donnee);
	DM5_NodeCrash();
};

#endif //OSMOSIS_DM5_NodeCrash_HPP
