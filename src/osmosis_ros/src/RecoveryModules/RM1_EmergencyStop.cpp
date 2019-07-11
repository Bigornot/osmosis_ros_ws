#include <osmosis_control/RecoveryModules/RM1_EmergencyStop.hpp>

RM1_EmergencyStop::RM1_EmergencyStop(int id, vector<int> successors) : RecoveryModule(id, successors) 
{
	pub_=nh_.advertise<std_msgs::Bool>("/do_RM1_EmergencyStop", 1);
}

void RM1_EmergencyStop::doRecovery()
{
	std_msgs::Bool data;
	data.data=true;
	pub_.publish(data);
}

void RM1_EmergencyStop::stopRecovery()
{
}
