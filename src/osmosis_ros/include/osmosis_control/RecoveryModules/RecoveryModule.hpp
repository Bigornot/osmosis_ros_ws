#ifndef OSMOSIS_RECOV_HPP
#define OSMOSIS_RECOV_HPP

#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <vector>

using namespace std;

class RecoveryModule
{
private:
	enum driveState{IDLE, RECOVERY};
	driveState driveState_;

	int id_;
	int antecedent_;
	vector<int> successors_;

protected:
	ros::NodeHandle nh_;
	bool state_;

public:
	RecoveryModule(int id, int antecedent, vector<int> successors);
	bool getState();
	void run();
	void start();
	void stop();
	void driveRecoveryModule();
	int getId();
	vector<int> getSuc();
	virtual void doRecovery()=0;
};

#endif
