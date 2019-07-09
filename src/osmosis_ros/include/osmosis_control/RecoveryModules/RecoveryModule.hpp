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
	enum driveState{IDLE, RECOVERY, WAIT_STOP, STOP};
	driveState driveState_;

	int id_;
	int predecessor_;
	vector<int> successors_;
	
	ros::Time activation_time_;
	ros::Duration next_activation_delay_;

protected:
	ros::NodeHandle nh_;
	bool state_;

public:
	RecoveryModule(int id, int predecessor, vector<int> successors, ros::Duration delay);
	bool getState();
	void run();
	void start();
	void stop();
	void driveRecoveryModule();
	int getId();
	vector<int> getSuccessorsId();
	virtual void doRecovery()=0;
};

#endif
