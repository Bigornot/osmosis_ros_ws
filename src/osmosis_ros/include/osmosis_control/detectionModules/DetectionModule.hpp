#ifndef OSMOSIS_DetectionModule_HPP
#define OSMOSIS_DetectionModule_HPP

#include <iostream>
#include <std_msgs/Bool.h>
#include <ros/ros.h>
#include <string>

using namespace std;

class DetectionModule
{
private :
	///////// Attributes ////////
	enum driveState{IDLE, ACTIVE};
	driveState drive_state_;

	///////// Methods ////////
	virtual void detect()=0; //method for the condition of the detection
	void detectionModuleFSM();

protected:
	ros::NodeHandle nh_;
	bool state_;

public :
	DetectionModule();

	virtual void init()=0; // Executed when the FTM starts (after startDelay)
	int getState();

	void run();
};

#endif
