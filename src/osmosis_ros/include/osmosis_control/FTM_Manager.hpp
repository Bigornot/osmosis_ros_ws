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

	enum Strategies{SAFETY_FIRST};
	Strategies strategy_;

	vector<FTM_Rule*> Triggered_FTM;
	vector<FTM_Rule*> dominant;
	vector<FTM_Rule*> dominant_recov;

	FTM_Rule* commonDominant;


	Tree FTM_Tree_;
public:
	FTM_Manager();
	bool run();
};

#endif
