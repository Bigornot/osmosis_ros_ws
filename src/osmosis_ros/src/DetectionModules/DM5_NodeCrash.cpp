#include <osmosis_control/DetectionModules/DM5_NodeCrash.hpp>

//! ROS node topics publishing and subscribing initialization
DM5_NodeCrash::DM5_NodeCrash() : DetectionModule()
{
	nodesToCheck_.push_back("/DM1_ProhibitedArea_node");
	nodesToCheck_.push_back("/DM2_CmdNotUpdated_node");
	nodesToCheck_.push_back("/DM3_WrongCommand_node");
	nodesToCheck_.push_back("/HMI_node");
	nodesToCheck_.push_back("/teleop_node");
	nodesToCheck_.push_back("/emergency_shutdown_node");
	nodesToCheck_.push_back("/graph_planner_node");
	nodesToCheck_.push_back("/joy_node");
	nodesToCheck_.push_back("/joy_teleop_node");
	nodesToCheck_.push_back("/localization_node");
	nodesToCheck_.push_back("/mission_manager_node");
	nodesToCheck_.push_back("/osmosis_control_node");
	nodesToCheck_.push_back("/safety_pilot_node");
	nodesToCheck_.push_back("/teleop_node");
}

bool DM5_NodeCrash::detect()
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
	{
		return true;
	}
	else
		return false;
}

