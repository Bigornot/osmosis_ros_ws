#include <osmosis_control/RecoveryModules/RM3_EmergencyStop.hpp>

RM3_EmergencyStop::RM3_EmergencyStop() : RecoveryModule() //constructeur
{
	Call_sub_=nh_.subscribe("call_RM3_EmergencyStop", 1, &RM3_EmergencyStop::RM3_EmergencyStopCallback, this);
	RM3_EmergencyStop_pub_=nh_.advertise<std_msgs::Bool>("/do_RM3_EmergencyStop", 1);
}

//Topic callback
void RM3_EmergencyStop::RM3_EmergencyStopCallback(const std_msgs::Bool & r3)
{
	this->recovery_= r3.data;
}

void RM3_EmergencyStop::pub_topic_recov(std_msgs::Bool donnee)
{
	RM3_EmergencyStop_pub_.publish(donnee);
}

