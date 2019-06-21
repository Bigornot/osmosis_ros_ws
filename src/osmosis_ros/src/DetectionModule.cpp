#include <osmosis_control/DetectionModule.hpp>

DetectionModule::DetectionModule ()
{
}

void DetectionModule::run()
{
	ros::Rate loop_rate(10);
	while (nh_.ok())
	{
		state_.data=this->detect();
		this->pub_to_FTM(state_);
		ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
		loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate
	}
}
