#include <osmosis_control/RecoveryModules/RM5_test5.hpp>

RM5_test5::RM5_test5(int id, int antecedent, vector<int> successors) : RecoveryModule(id, antecedent, successors) 
{
	pub_=nh_.advertise<std_msgs::Bool>("/do_RM5_test5", 1);
}

void RM5_test5::doRecovery()
{
	std_msgs::Bool data;
	data.data=true;
	pub_.publish(data);
}
