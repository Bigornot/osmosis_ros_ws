#include <recoveryModules/RM1_EmergencyStop.hpp>


////////////////////// PUBLIC //////////////////////

RM1_EmergencyStop::RM1_EmergencyStop(int id, vector<int> successors) : RecoveryModule(id, successors)
{
	pub_=nh_.advertise<std_msgs::Bool>("/do_emergency_stop", 100);
	pub_cmd_=nh_.advertise<geometry_msgs::Twist>("/summit_xl_a/robotnik_base_control/cmd_vel", 100);
	pollRate_=100;
	delaySend_=0.1;
	start_=ros::Time::now();
}

void RM1_EmergencyStop::startRecovery()
{
	std_msgs::Bool data;
	data.data=true;

	ros::Rate poll_rate(pollRate_);
	start_=ros::Time::now();
	while(pub_.getNumSubscribers() == 0 && ros::Time::now()-start_<ros::Duration(delaySend_))
		poll_rate.sleep();

	pub_.publish(data);

	doRecovery();
}

void RM1_EmergencyStop::doRecovery()
{
	geometry_msgs::Twist cmd;
	cmd.linear.x=0;
	cmd.linear.y=0;
	cmd.linear.z=0;
	cmd.angular.x=0;
	cmd.angular.y=0;
	cmd.angular.z=0;

	ros::Rate poll_rate(pollRate_);
	start_=ros::Time::now();
	while(pub_cmd_.getNumSubscribers() == 0 && ros::Time::now()-start_<ros::Duration(delaySend_))
		poll_rate.sleep();

	pub_cmd_.publish(cmd);
}

void RM1_EmergencyStop::stopRecovery()
{
}
