#include <osmosis_control/RecoveryModules/Recov.hpp>

Recov::Recov (){}

bool Recov::is_recovery_on()
{
  return recovery_;
}

void Recov::run()
{
	ros::Rate loop_rate(10);
	while (nh_.ok())
  {
		recov_msg_.data=this->is_recovery_on();
		this->pub_topic_recov(recov_msg_);
		ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
		loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate
	}
}
