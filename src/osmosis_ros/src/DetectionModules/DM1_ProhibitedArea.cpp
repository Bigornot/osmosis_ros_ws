#include <osmosis_control/DetectionModules/DM1_ProhibitedArea.hpp>

//! ROS node topics publishing and subscribing initialization
DM1_ProhibitedArea::DM1_ProhibitedArea() : DetectionModule()
{
	state_sub_  = nh_.subscribe("inProhibitedArea", 1, &DM1_ProhibitedArea::DM1_ProhibitedAreaCallback, this);
 	state_=false;
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
	std::cout << "SALLUT je suis DM1" << endl;
}

