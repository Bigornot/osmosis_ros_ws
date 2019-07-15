#include <osmosis_control/DetectionModules/DM5_NodeCrashControl.hpp>

//! ROS node topics publishing and subscribing initialization
DM5_NodeCrashControl::DM5_NodeCrashControl() : DetectionModule()
{
	nodesToCheck_.push_back("/HMI_node");
	nodesToCheck_.push_back("/graph_planner_node");
	nodesToCheck_.push_back("/mission_manager_node");
	nodesToCheck_.push_back("/osmosis_control_node");
}

void DM5_NodeCrashControl::detect()
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

