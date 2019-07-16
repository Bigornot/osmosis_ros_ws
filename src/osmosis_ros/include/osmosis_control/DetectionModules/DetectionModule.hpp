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
	void driveDetectionModule();
	virtual void set()=0; // Executed when the FTM starts (after startDelay)
	void run(); //method to lauch the detection node
	virtual void detect()=0; //method for the condition of the detection
	bool getState();
};

#endif
