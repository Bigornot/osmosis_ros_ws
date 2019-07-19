#include <osmosis_control/RecoveryModules/RM3_RespawnControlNodes.hpp>

RM3_RespawnControlNodes::RM3_RespawnControlNodes(int id, vector<int> successors, bool managerCanStop) : RecoveryModule(id, successors, managerCanStop) 
{
	nodesToCheck_.push_back("/HMI_node");
	nodesToCheck_.push_back("/graph_planner_node");
	nodesToCheck_.push_back("/osmosis_control_node");
	nodesToCheck_.push_back("/mission_manager_node");

	n_max_wait_=10;
	n_=0;
}

void RM3_RespawnControlNodes::startRecovery()
{
	cout << "START RM3" << endl;

	bool found=false;
	string command;
	n_=0;

	nodesToRespawn_.clear();
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
			nodesToRespawn_.push_back(nodesToCheck_[i]);
	}


	for(int i=0; i<nodesToRespawn_.size(); i++)
	{
		nodesToRespawn_[i].erase(nodesToRespawn_[i].begin());
		command="xterm -e \"rosrun osmosis_control " + nodesToRespawn_[i] + "\" &";
		system(command.c_str());
	}
}

void RM3_RespawnControlNodes::doRecovery()
{
	if(n_>n_max_wait_)
	{
		startRecovery();
		n_=0;
	}

	bool respawnDone=true;
	bool found=false;
	ros::V_string aliveNodes;
	ros::master::getNodes(aliveNodes);

	for(int i=0; i<nodesToRespawn_.size(); i++)
	{
		for(int j=0; j<aliveNodes.size(); j++)
		{
			aliveNodes[j].erase(aliveNodes[j].begin());
			if(nodesToRespawn_[i]==aliveNodes[j])
				found=true;
		}
		if(!found)
			respawnDone=false;
	}

	if(respawnDone)
		stop();

	n_++;
}

void RM3_RespawnControlNodes::stopRecovery()
{
}
