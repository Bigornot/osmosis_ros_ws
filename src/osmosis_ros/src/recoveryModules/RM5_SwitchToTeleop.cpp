#include <osmosis_control/recoveryModules/RM5_SwitchToTeleop.hpp>


////////////////////// PUBLIC //////////////////////

RM5_SwitchToTeleop::RM5_SwitchToTeleop(int id, vector<int> successors) : RecoveryModule(id, successors) 
{
	pub_=nh_.advertise<std_msgs::Bool>("/do_RM5_SwitchToTeleop", 100);
	pollRate_=100;
	delaySend_=0.1;
	start_=ros::Time::now();
}

void RM5_SwitchToTeleop::startRecovery()
{
	std_msgs::Bool data;
	data.data=true;

	ros::Rate poll_rate(pollRate_);
	start_=ros::Time::now();
	while(pub_.getNumSubscribers() == 0 && ros::Time::now()-start_<ros::Duration(delaySend_))
		poll_rate.sleep();

	pub_.publish(data);
}

void RM5_SwitchToTeleop::doRecovery()
{
}

void RM5_SwitchToTeleop::stopRecovery()
{
}

