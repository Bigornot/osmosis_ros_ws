#ifndef DEF_FTM_MANAGER
#define DEF_FTM_MANAGER

#include <iostream>
#include <ros/ros.h>
#include <vector>
#include <osmosis_control/Tree.hpp>

using namespace std;

class FTM_Manager
{
private:
	ros::NodeHandle nh_;

	int nbTriggeredFTM_;
	Tree FTM_Tree;
public:
	FTM_Manager();
	bool run();
};

#endif
