#include <osmosis_control/RecoveryModules/RM3_test3.hpp>

RM3_test3::RM3_test3(int id, int antecedent, vector<int> successors) : RecoveryModule(id, antecedent, successors) 
{
	pub_=nh_.advertise<std_msgs::Bool>("/do_RM3_test3", 1);
}

void RM3_test3::doRecovery()
{
	std_msgs::Bool data;
	data.data=true;
	pub_.publish(data);
}
