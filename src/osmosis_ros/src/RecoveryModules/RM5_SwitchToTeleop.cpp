#include <osmosis_control/RecoveryModules/RM5_SwitchToTeleop.hpp>

RM5_SwitchToTeleop::RM5_SwitchToTeleop(int id, int antecedent, vector<int> successors) : RecoveryModule(id, antecedent, successors) 
{
	pub_=nh_.advertise<std_msgs::Bool>("/do_RM5_SwitchToTeleop", 1);
}

void RM5_SwitchToTeleop::doRecovery()
{
	std_msgs::Bool data;
	data.data=true;
	pub_.publish(data);
}
