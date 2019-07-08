#include <osmosis_control/RecoveryModules/RM4_RespawnNodes.hpp>

RM4_RespawnNodes::RM4_RespawnNodes(int id, int predecessor, vector<int> successors, ros::Duration delay) : RecoveryModule(id, predecessor, successors, delay) 
{

	nodesToCheck_.push_back("/teleop_node");
	nodesToCheck_.push_back("/safety_pilot_node");
	nodesToCheck_.push_back("/localization_node");
	nodesToCheck_.push_back("/joy_teleop_node");
	nodesToCheck_.push_back("/emergency_shutdown_node");
	nodesToCheck_.push_back("/checkProhibitedArea_node");
}

void RM4_RespawnNodes::doRecovery()
{
	bool found=false;
	string command;

	ros::V_string nodesToRespawn;
	ros::V_string aliveNodes;
	ros::master::getNodes(aliveNodes);

	for(int i=0; i<nodesToCheck_.size(); i++)
	{
		found = false;
		for(int j=0; j<aliveNodes.size() && !found; j++)
		{
			if(aliveNodes[j]==nodesToCheck_[i])
				found =true;
		}

		if(!found)
			nodesToRespawn.push_back(nodesToCheck_[i]);
	}


	for(int i=0; i<nodesToRespawn.size(); i++)
	{
		nodesToRespawn[i].erase(nodesToRespawn[i].begin());
		command="xterm -e \"rosrun osmosis_control " + nodesToRespawn[i] + "\" &";
		system(command.c_str());
	}
}
