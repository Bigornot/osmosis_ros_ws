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
	enum driveState{IDLE, ACTIVATED};
	driveState drive_state_;

	int id_;
	vector<int> successors_;

protected:
	ros::NodeHandle nh_;
	bool state_;

public:
	RecoveryModule(int id, vector<int> successors);
	int getState();
	void run();
	void start();
	void stop();
	void recoveryModuleFSM();
	int getId();
	vector<int> getSuccessorsId();
	virtual void doRecovery()=0;
	virtual void startRecovery()=0;
	virtual void stopRecovery()=0;
};

#endif
