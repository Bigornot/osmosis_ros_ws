#include <osmosis_control/RecoveryModules/RM2_ControlledStop.hpp>

RM2_ControlledStop::RM2_ControlledStop(int id, vector<int> successors) : RecoveryModule(id, successors) 
{
	pub_=nh_.advertise<std_msgs::Bool>("/do_RM2_ControlledStop", 1);
}

void RM2_ControlledStop::doRecovery()
{
	std_msgs::Bool data;
	data.data=true;
	pub_.publish(data);
}

void RM2_ControlledStop::stopRecovery()
{
}
