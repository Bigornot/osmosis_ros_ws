#include <osmosis_control/RecoveryModules/RM3_RespawnControlNodes.hpp>

RM3_RespawnControlNodes::RM3_RespawnControlNodes(int id, int predecessor, vector<int> successors) : RecoveryModule(id, predecessor, successors) 
{

	nodesToCheck_.push_back("/HMI_node");
	nodesToCheck_.push_back("/graph_planner_node");
	nodesToCheck_.push_back("/osmosis_control_node");
	nodesToCheck_.push_back("/mission_manager_node");
}

void RM3_RespawnControlNodes::doRecovery()
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
