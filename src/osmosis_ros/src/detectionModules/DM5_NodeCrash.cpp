#include <osmosis_control/detectionModules/DM5_NodeCrash.hpp>

////////////////////// PRIVATE //////////////////////

void DM5_NodeCrash::detect()
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


////////////////////// PUBLIC //////////////////////

DM5_NodeCrash::DM5_NodeCrash() : DetectionModule()
{
	nodesToCheck_.push_back("/teleop_node");
	nodesToCheck_.push_back("/joy_node");
	nodesToCheck_.push_back("/joy_teleop_node");
	nodesToCheck_.push_back("/localization_node");
	nodesToCheck_.push_back("/safety_pilot_node");
	nodesToCheck_.push_back("/teleop_node");
	nodesToCheck_.push_back("/checkProhibitedArea_node");
}

void DM5_NodeCrash::init()
{
}


