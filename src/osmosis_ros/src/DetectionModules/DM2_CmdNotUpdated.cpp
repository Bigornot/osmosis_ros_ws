#include <osmosis_control/DetectionModules/DM2_CmdNotUpdated.hpp>

//! ROS node topics publishing and subscribing initialization
DM2_CmdNotUpdated::DM2_CmdNotUpdated() : DetectionModule()
{
	cmd_vel_sub_  = nh_.subscribe("summit_xl_a/robotnik_base_control/cmd_vel", 1, &DM2_CmdNotUpdated::DM2_CmdNotUpdatedCallback, this);
	DM2_pub_ = nh_.advertise<std_msgs::Bool>("DM2_CmdNotUpdated", 10);

	lastUpdate_=ros::Time::now();
	timeOut_ = ros::Duration(1);
}

bool DM2_CmdNotUpdated::detect()
{
	if(ros::Time::now()-lastUpdate_>timeOut_)
		return true;
	else
		return false;
}

void DM2_CmdNotUpdated::DM2_CmdNotUpdatedCallback(const geometry_msgs::Twist &cmd_vel)
{
	lastUpdate_ = ros::Time::now();
}

void DM2_CmdNotUpdated::pub_to_FTM(std_msgs::Bool donnee)
{
	bool b = donnee.data;
	DM2_pub_.publish(donnee);
	std::cout << "Publication of DM2 : CmdNotUpdated : ";
	std::cout << debug_msg <<" ";
	std::cout << std::boolalpha << b << std::endl;
}

int main(int argc, char** argv)
{
	//init the ROS node
	ros::init(argc, argv, "DM2_CmdNotUpdated_node");

	DM2_CmdNotUpdated myDM2_CmdNotUpdated;
	myDM2_CmdNotUpdated.run();
}
