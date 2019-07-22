#include <osmosis_control/detectionModules/DM1_ProhibitedArea.hpp>


////////////////////// PRIVATE //////////////////////

void DM1_ProhibitedArea::detect()
{
	// Done in another node
	// Cf ProhibitedAreaCallback
}


////////////////////// PUBLIC //////////////////////

DM1_ProhibitedArea::DM1_ProhibitedArea() : DetectionModule()
{
	state_sub_  = nh_.subscribe("inProhibitedArea", 1, &DM1_ProhibitedArea::DM1_ProhibitedAreaCallback, this);
 	state_=false;
}

void DM1_ProhibitedArea::init()
{
	
}

void DM1_ProhibitedArea::DM1_ProhibitedAreaCallback(const std_msgs::Bool & state)
{
	state_ = state.data;
}

