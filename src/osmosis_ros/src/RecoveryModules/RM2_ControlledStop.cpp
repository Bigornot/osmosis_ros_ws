#include <osmosis_control/RecoveryModules/RM2_ControlledStop.hpp>

RM2_ControlledStop::RM2_ControlledStop(int id, vector<int> successors) : RecoveryModule(id, successors) 
{
	pub_order_=nh_.advertise<std_msgs::Bool>("/do_RM2_ControlledStop", 100);
	pub_cmd_=nh_.advertise<geometry_msgs::Twist>("/summit_xl_a/robotnik_base_control/cmd_vel", 100);
	
	pollRate_ = 100;
}

void RM2_ControlledStop::startRecovery()
{

	std_msgs::Bool data;
	data.data=true;

	ros::Rate poll_rate(pollRate_);
	while(pub_order_.getNumSubscribers() == 0)
		poll_rate.sleep();

	pub_order_.publish(data);

	this->doRecovery();

	cout << "order sent" << endl;
}

void RM2_ControlledStop::doRecovery()
{
	geometry_msgs::Twist cmd;
	cmd.linear.x=0;
	cmd.linear.y=0;
	cmd.linear.z=0;
	cmd.angular.x=0;
	cmd.angular.y=0;
	cmd.angular.z=0;

	ros::Rate poll_rate(pollRate_);
	while(pub_cmd_.getNumSubscribers() == 0)
		poll_rate.sleep();

	pub_cmd_.publish(cmd);

	cout << "Cmd sent" << endl;
}

void RM2_ControlledStop::stopRecovery()
{
	std_msgs::Bool data;
	data.data=false;

	pub_order_.publish(data);
}
