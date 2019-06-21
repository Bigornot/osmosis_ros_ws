#ifndef OSMOSIS_DetectionModule_HPP
#define OSMOSIS_DetectionModule_HPP

#include <iostream>
#include <std_msgs/Bool.h>
#include <ros/ros.h>

using namespace std;

class DetectionModule
{
private :
	std_msgs::Bool state_;
	ros::NodeHandle nh_;
public :
	DetectionModule();
	void run(); //method to lauch the detection node
	virtual bool detect()=0; //method for the condition of the detection
	virtual void pub_to_FTM(std_msgs::Bool)=0; //method to publish on the designated topics
};

#endif
