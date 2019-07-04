#ifndef DEF_FTM_RULE
#define DEF_FTM_RULE

#include <iostream>
#include "ros/ros.h"
#include <string>
#include "std_msgs/Bool.h"
#include <vector>

#include <osmosis_control/DetectionModules/DetectionModule.hpp>
#include <osmosis_control/RecoveryModules/RecoveryModule.hpp>

class FTM_Rule
{
private:
	ros::NodeHandle nh_;

	DetectionModule* DM_;
	RecoveryModule* RM_;
	
	int id_;

	int predecessor_;
	vector<int> successors_;
	
public:
	FTM_Rule(int id, int predecessor, vector<int> successor, DetectionModule* DM, RecoveryModule* RM);

	int getId();
	int getPredecessor();
	vector<int> getSuc();

	void runDM();
	bool getStateDM();
	void runRM();
	bool getStateRM();

	void startRM();
	void stopRM();

	int getRMId();
	vector<int> getRMSuc();
};

#endif
