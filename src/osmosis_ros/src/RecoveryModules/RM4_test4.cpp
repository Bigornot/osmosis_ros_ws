#include <osmosis_control/RecoveryModules/RM4_test4.hpp>

RM4_test4::RM4_test4(int id, int predecessor, vector<int> successors) : RecoveryModule(id, predecessor, successors) 
{
	pub_=nh_.advertise<std_msgs::Bool>("/do_RM4_test4", 1);
}

void RM4_test4::doRecovery()
{
	std_msgs::Bool data;
	data.data=true;
	pub_.publish(data);
}
