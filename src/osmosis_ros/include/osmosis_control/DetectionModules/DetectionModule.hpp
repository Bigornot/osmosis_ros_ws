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
	std_msgs::Bool state_;
	enum driveState{DETECTION_MODE,START_RECOVERY,ERROR_DETECTED};
	driveState driveState_;

protected:
	string debug_msg;
	ros::NodeHandle nh_;

public :
	DetectionModule();
	void driveDetectionModule();
	void run(); //method to lauch the detection node
	virtual bool detect()=0; //method for the condition of the detection
};

#endif
