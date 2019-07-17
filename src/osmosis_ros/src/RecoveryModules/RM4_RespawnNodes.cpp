#include <osmosis_control/RecoveryModules/RM4_RespawnNodes.hpp>

RM4_RespawnNodes::RM4_RespawnNodes(int id, vector<int> successors, bool managerCanStop) : RecoveryModule(id, successors, managerCanStop) 
{
	nodesToCheck_.push_back("/teleop_node");
	nodesToCheck_.push_back("/safety_pilot_node");
	nodesToCheck_.push_back("/localization_node");
	nodesToCheck_.push_back("/joy_teleop_node");
	nodesToCheck_.push_back("/joy_node");
	//nodesToCheck_.push_back("/checkProhibitedArea_node");
	nodesToCheck_.push_back("/emergency_shutdown_node");
}

void RM4_RespawnNodes::startRecovery()
{
	cout << "START RM4" << endl;
	
	bool found=false;
	string command;

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
		if(nodesToRespawn_[i]=="joy_node")
			command="xterm -e \"rosrun joy " + nodesToRespawn_[i] + "\" &";
		else
			command="xterm -e \"rosrun osmosis_control " + nodesToRespawn_[i] + "\" &";
		system(command.c_str());
	}
}

void RM4_RespawnNodes::doRecovery()
{
	bool respawnDone=true;
	bool found=false;
	ros::V_string aliveNodes;
	ros::master::getNodes(aliveNodes);

	for(int i=0; i<aliveNodes.size(); i++)
		aliveNodes[i].erase(aliveNodes[i].begin());

	for(int i=0; i<nodesToRespawn_.size(); i++)
	{
		cout << "to respawn " << i << " " << nodesToRespawn_[i] << endl;
		for(int j=0; j<aliveNodes.size(); j++)
		{
			cout << aliveNodes[j] << endl;
			if(nodesToRespawn_[i]==aliveNodes[j])
				found=true;
		}
		if(!found)
			respawnDone=false;
	}

	if(respawnDone)
		stop();
}

void RM4_RespawnNodes::stopRecovery()
{
}

