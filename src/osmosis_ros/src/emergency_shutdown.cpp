//juil2018 J.Guiochet @ LAAS
#include <osmosis_control/emergency_shutdown.hpp>

void EmergencyShutdown::driveEmergencyShutdown()
{
	string emergency_hit;
	switch (state_)
	{
		case IDLE://nominal case
			cout << "Press any caracter for emergency stop :";
			cin >> emergency_hit;
			state_=EMERGENCYHIT;
		break;

		case EMERGENCYHIT:
			emergency_.data=true;
			emergency_pub_.publish(emergency_);
			state_=EMERGENCY;
		break;

		case EMERGENCY:
			ROS_ERROR("\nEMERGENCY STOP !\n");
<<<<<<< HEAD
			cin.get();
=======
			cin >> emergency_hit;
>>>>>>> a73e49499c84d6b388fb5febb598793e4c5f2158
			emergency_.data=false;
			emergency_pub_.publish(emergency_);
			state_=IDLE;
		break;
  }
}

EmergencyShutdown::EmergencyShutdown()
{
	emergency_.data=false;
	emergency_pub_ = nh_.advertise<std_msgs::Bool>("/do_RM1_EmergencyStop", 1);
	state_=IDLE;
}

void EmergencyShutdown::run()
{
	ros::Rate loop_rate(10); //using 10 makes the robot oscillating trajectories, TBD check with the PF algo ?
	while (nh_.ok())
	{
		driveEmergencyShutdown();//state machine
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
