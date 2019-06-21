#ifndef OSMOSIS_DetectionModule_HPP
#define OSMOSIS_DetectionModule_HPP

#include <iostream>
#include <math.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Bool.h>
#include <ros/ros.h>
using namespace std;

class DetectionModule
{
private :
	bool detection_;
	std_msgs::Bool state_;
	ros::NodeHandle nh_;
public :
	DetectionModule();
	bool DetectMod();
	void run(); //method to lauch the detection node
	virtual bool detect()=0; //method for the condition of the detection
	virtual void pub_to_FTM(std_msgs::Bool)=0; //method to publish on the designated topics
};

#endif
