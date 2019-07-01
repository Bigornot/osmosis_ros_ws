#ifndef DEF_FTM_MANAGER
#define DEF_FTM_MANAGER

#include <iostream>
#include <ros/ros.h>
#include <vector>
#include <osmosis_control/Tree_Vector.hpp>

using namespace std;

class FTM_Manager
{
private:
	ros::NodeHandle nh_;

	Tree_Vector* FTM_Tree;
public:
	FTM_Manager();
	bool run();
};

#endif
