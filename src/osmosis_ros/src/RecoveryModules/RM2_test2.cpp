#include <osmosis_control/RecoveryModules/RM2_test2.hpp>

using namespace std;

RM2_test2::RM2_test2(int id, int antecedent, vector<int> successors) : RecoveryModule(id, antecedent, successors) 
{
	pub_=nh_.advertise<std_msgs::Bool>("/do_RM2_test2", 1);
}

void RM2_test2::doRecovery()
{
	cout << "AHAZIOFHAZOFHAZDHAHAHAHAZDHAZOHAHA" << endl;
	std_msgs::Bool data;
	data.data=true;
	pub_.publish(data);
}
