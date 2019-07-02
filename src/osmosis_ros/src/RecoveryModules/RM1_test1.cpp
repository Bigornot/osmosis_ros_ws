#include <osmosis_control/RecoveryModules/RM1_test1.hpp>

RM1_test1::RM1_test1(int id, int antecedent, vector<int> successors) : RecoveryModule(id, antecedent, successors) 
{
	pub_=nh_.advertise<std_msgs::Bool>("/do_RM1_test1", 1);
}

void RM1_test1::doRecovery()
{
	std_msgs::Bool data;
	data.data=true;
	pub_.publish(data);
}
