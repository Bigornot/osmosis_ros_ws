//juil2018 J.Guiochet @ LAAS
#include <osmosis_control/emergency_shutdown.hpp>

void EmergencyShutdown::driveEmergencyShutdown()
{
	std::string emergency_hit;
	switch (state_)
	{
		case NOMINAL:
			std::cin >> emergency_hit;
			state_=EMERGENCY;
		break;

		case EMERGENCYHIT:
			emergency_.data=true;
			emergency_pub_.publish(emergency_);
			state_=EMERGENCY;
		break;

		case EMERGENCY:
			std::cin >> emergency_hit;
			state_=NOMINAL;
		break;
  }
}
//! ROS node initialization
EmergencyShutdown::EmergencyShutdown()
{
	//set up the publisher for the goal topic
	emergency_.data=false;
	emergency_pub_ = nh_.advertise<std_msgs::Bool>("emergency_shutdown", 1);
	state_=NOMINAL;
}

void EmergencyShutdown::run()
{
	ros::Rate loop_rate(10); //using 10 makes the robot oscillating trajectories, TBD check with the PF algo ?
	while (nh_.ok())
	    {
				this->driveEmergencyShutdown();
			 	ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
				loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate
	    }
}

int main(int argc, char** argv)
{
  //init the ROS node
  ros::init(argc, argv, "emergency_shutdown_node");

  EmergencyShutdown myEmergencyShutdown;
  myEmergencyShutdown.run();
}
