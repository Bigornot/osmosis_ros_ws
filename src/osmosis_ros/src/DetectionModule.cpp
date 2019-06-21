#include <list>
#include <functional>
#include <limits>
#include <cmath>
#include <algorithm>

#include <osmosis_control/DetectionModule.hpp>

DetectionModule::DetectionModule ()
{
}

bool DetectionModule::DetectMod()
{
	detection_=detect();
	return(detection_);
}

void DetectionModule::run()
{
	ros::Rate loop_rate(10);
	while (nh_.ok())
	{
		state_.data=this->DetectMod();
		this->pub_to_FTM(state_);
		ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
		loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate
	}
}
