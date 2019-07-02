#include <osmosis_control/RecoveryModules/RM3_EmergencyStop.hpp>

RM3_EmergencyStop::RM3_EmergencyStop(int id, int antecedent, vector<int> successors) : RecoveryModule(id, antecedent, successors) 
{
	pub_=nh_.advertise<std_msgs::Bool>("/do_RM3_EmergencyStop", 1);
}

void RM3_EmergencyStop::doRecovery()
{
	std_msgs::Bool data;
	data.data=true;
	pub_.publish(data);
}
