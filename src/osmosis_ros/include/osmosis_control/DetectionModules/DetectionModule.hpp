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
	enum driveState{DETECTION_MODE,START_RECOVERY,ERROR_DETECTED};
	driveState driveState_;

protected:
	ros::NodeHandle nh_;
	bool state_;

public :
	DetectionModule();
	void driveDetectionModule();
	void run(); //method to lauch the detection node
	virtual bool detect()=0; //method for the condition of the detection
	bool getState();
};

#endif
