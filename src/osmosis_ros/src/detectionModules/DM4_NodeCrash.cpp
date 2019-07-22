#include <osmosis_control/detectionModules/DM4_NodeCrash.hpp>

//! ROS node topics publishing and subscribing initialization
DM4_NodeCrash::DM4_NodeCrash() : DetectionModule()
{
	nodesToCheck_.push_back("/teleop_node");
	nodesToCheck_.push_back("/emergency_shutdown_node");
	nodesToCheck_.push_back("/joy_node");
	nodesToCheck_.push_back("/joy_teleop_node");
	nodesToCheck_.push_back("/localization_node");
	nodesToCheck_.push_back("/safety_pilot_node");
	nodesToCheck_.push_back("/teleop_node");
	nodesToCheck_.push_back("/checkProhibitedArea_node");
}

void DM4_NodeCrash::init()
{
}

void DM4_NodeCrash::detect()
{
	int i,j;
	bool found=true;

	ros::master::getNodes(aliveNodes_);	
	for(i=0; i<nodesToCheck_.size() && found; i++)
	{
		found = false;
		for(j=0; j<aliveNodes_.size() && !found; j++)
		{
			if(aliveNodes_[j]==nodesToCheck_[i])
				found = true;
		}
	}
	aliveNodes_.clear();

	if(!found)
		state_=true;
	else
		state_=false;
}

