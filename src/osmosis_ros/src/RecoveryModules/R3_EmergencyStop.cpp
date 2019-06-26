#include <osmosis_control/RecoveryModules/R3_EmergencyStop.hpp>
#include <osmosis_control/RecoveryModules/Recov.hpp>

R3_EmergencyStop::R3_EmergencyStop() : Recov()
{
	Call_sub_=nh_.subscribe("call_R3_EmergencyStop", 1, &R3_EmergencyStop::R3_EmergencyStopCallback, this);
	R3_EmergencyStop_pub_=nh_.advertise<std_msgs::Bool>("/do_R3_EmergencyStop", 1);
}

//Topic callback
void R3_EmergencyStop::R3_EmergencyStopCallback(const std_msgs::Bool & r3)
{
	this->recovery_= r3.data;
}

void R3_EmergencyStop::pub_topic_recov(std_msgs::Bool donnee)
{
		R3_EmergencyStop_pub_.publish(donnee);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "R3_EmergencyStop_node");
  Recov* myR3_EmergencyStop =new R3_EmergencyStop();
  myR3_EmergencyStop->run();
}
