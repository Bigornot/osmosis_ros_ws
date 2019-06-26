#include <list>
#include <functional>
#include <limits>
#include <cmath>
#include <algorithm>

#include <osmosis_control/Recov.hpp>

Recov :: Recov ()
{}

bool Recov::makeRecovery()
{
	if (recovery_action_)
	{
		recovery=true;
	}
	else
	{
		recovery=false;
	}
	return(recovery);
}


void Recov::run()
{
	ros::Rate loop_rate(10);
	while (nh_.ok())
        {
		rok.data=this->makeRecovery();
		this->pub_topic_recov(rok);
		ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
		loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate
	}

}
