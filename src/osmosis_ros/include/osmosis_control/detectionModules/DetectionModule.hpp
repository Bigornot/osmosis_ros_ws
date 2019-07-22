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
	enum driveState{IDLE, ACTIVE};
	driveState driveState_;

protected:
	ros::NodeHandle nh_;
	bool state_;

public :
	DetectionModule();
	void detectionModuleFSM();
	virtual void init()=0; // Executed when the FTM starts (after startDelay)
	void run(); 
	virtual void detect()=0; //method for the condition of the detection
	int getState();
};

#endif
