#include <osmosis_control/DetectionModules/DM1_ProhibitedArea.hpp>

//! ROS node topics publishing and subscribing initialization
DM1_ProhibitedArea::DM1_ProhibitedArea() : DetectionModule()
{
	state_sub_  = nh_.subscribe("inProhibitedArea", 1, &DM1_ProhibitedArea::DM1_ProhibitedAreaCallback, this);
	DM1_pub_ = nh_.advertise<std_msgs::Bool>("DM1_ProhibitedArea", 10);
}

//compute detection out of zone
bool DM1_ProhibitedArea::detect()
{
	if (state_)
	{
		std::cout << "The robot is in a prohibited area." << endl;
		return true;
	}
	else
		return false;
}

//Topic callback
void DM1_ProhibitedArea::DM1_ProhibitedAreaCallback(const std_msgs::Bool & state)
{
	state_ = state.data;
}

void DM1_ProhibitedArea::pub_to_FTM(std_msgs::Bool donnee)
{
	bool b = donnee.data;
	DM1_pub_.publish(donnee);
	std::cout << "Publication de DM1 : ProhibitedArea : ";
	std::cout << debug_msg <<" ";
	std::cout << std::boolalpha << b << std::endl;
}

int main(int argc, char** argv)
{
	//init the ROS node
	ros::init(argc, argv, "DM1_ProhibitedArea_node");

	DM1_ProhibitedArea myDM1_ProhibitedArea;
	myDM1_ProhibitedArea.run();
}
