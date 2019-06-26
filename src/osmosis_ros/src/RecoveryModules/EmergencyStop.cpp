#include <osmosis_control/EmergencyStop.hpp>
#include <osmosis_control/Recov.hpp>

//compute detection wrong command


//constructeur
//! ROS node topics publishing and subscribing initialization
EmergencyStop::EmergencyStop()
	  {
	    //set up the suscriber for the topic recov2
	    Recov2_sub_  = nh_.subscribe("Call_EmergencyStop", 1, &EmergencyStop::EmergencystopCallbackFTMrules, this);
			//set up the publisher for the topic
			EmergencyStop_pub_ = nh_.advertise<std_msgs::Bool>("/EmergencyStop", 1);
	  }


//Topic callback
void EmergencyStop::EmergencystopCallbackFTMrules(const std_msgs::Bool & rec2)
	{
	this->recovery_action_ = rec2.data;
	}


void EmergencyStop::pub_topic_recov(std_msgs::Bool donnee)
		{
		EmergencyStop_pub_.publish(donnee);

		if (donnee.data)
		{
			sleep(5);
			ros::shutdown();
		}

		}


int main(int argc, char** argv)
{
  //init the ROS node
  ros::init(argc, argv, "EmergencyStop_node");

  Recov* myEmergencyStop =new EmergencyStop();
  myEmergencyStop->run();
}
