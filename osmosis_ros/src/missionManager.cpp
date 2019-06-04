//juil2018 J.Guiochet @ LAAS
#include <osmosis_control/missionManager.hpp>


//! ROS node initialization
MissionManager::MissionManager()
  {
	//set up the publisher for the goal topic
	goal_pub_ = nh_.advertise<geometry_msgs::Point>("goal", 1);

  }


void MissionManager::goalKeyboard()
{
	geometry_msgs::Point thegoal;
  std::cout << "This mission manager is a simple goto position mission... "<<std::endl
            <<"It is better to choose an x and an y from the nodes defined in test.graph ";
	std::cout << "Enter a new goal (x,y) \nx= ";
	std::cin >> thegoal.x;

	std::cout << "y= ";
	std::cin >> thegoal.y;

	this->goal_=thegoal;
}


void MissionManager::run()
{
	ros::Rate loop_rate(10); //using 10 makes the robot oscillating trajectories, TBD check with the PF algo ?
	while (nh_.ok())
	    {
		//std::cout <<"HEY";
		this->goalKeyboard();
		goal_pub_.publish(goal_);
	 	//ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
		loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate
	    }

}




int main(int argc, char** argv)
{
  //init the ROS node
  ros::init(argc, argv, "navigation_node");

  MissionManager myMManager;
  myMManager.run();
}
