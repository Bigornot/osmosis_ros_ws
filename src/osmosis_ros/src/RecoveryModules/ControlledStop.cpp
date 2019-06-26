#include <osmosis_control/ControlledStop.hpp>
#include <osmosis_control/Recov.hpp>

//compute detection wrong command


//constructeur
//! ROS node topics publishing and subscribing initialization
ControlledStop::ControlledStop()
	  {
	    //set up the suscriber for the cmd_vel topic
	    Recov1_sub_  = nh_.subscribe("Call_ControlStop", 1, &ControlledStop::ControlledstopCallbackFTMrules, this);
			//set up the publisher for the Detect1 topic
			ControlledStop_pub_ = nh_.advertise<std_msgs::Bool>("/ControlStop", 1);
	  }


//Topic callback
void ControlledStop::ControlledstopCallbackFTMrules(const std_msgs::Bool & rec1)
	{
	this->recovery_action_ = rec1.data;
	}


void ControlledStop::pub_topic_recov(std_msgs::Bool donnee)
	{
	ControlledStop_pub_.publish(donnee);
	}


int main(int argc, char** argv)
{
  //init the ROS node
  ros::init(argc, argv, "ControlledStop_node");

  Recov* myControlledStop =new ControlledStop();
  myControlledStop->run();
}
