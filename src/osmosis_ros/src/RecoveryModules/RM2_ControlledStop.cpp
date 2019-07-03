#include <osmosis_control/RecoveryModules/RM2_ControlledStop.hpp>

RM2_ControlledStop::RM2_ControlledStop(int id, int antecedent, vector<int> successors) : RecoveryModule(id, antecedent, successors) 
{
	pub_=nh_.advertise<std_msgs::Bool>("/do_RM2_ControlledStop", 1);
}

void RM2_ControlledStop::doRecovery()
{
	std_msgs::Bool data;
	data.data=true;
	pub_.publish(data);
}
