#include <recoveryModules/RM4_RespawnNodes.hpp>


////////////////////// PUBLIC //////////////////////

RM4_RespawnNodes::RM4_RespawnNodes(int id, vector<int> successors) : RecoveryModule(id, successors)
{
	nodesToCheck_.push_back("/teleop_node");
	nodesToCheck_.push_back("/safety_pilot_node");
	nodesToCheck_.push_back("/localization_node");
	nodesToCheck_.push_back("/joy_teleop_node");
	nodesToCheck_.push_back("/joy_node");
	nodesToCheck_.push_back("/checkProhibitedArea_node");

	n_=0;
	n_max_wait_=10;
}

void RM4_RespawnNodes::startRecovery()
{
	cout << "START RM4" << endl;

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
		if(nodesToRespawn_[i]=="joy_node")
			command="xterm -e \"rosrun joy joy_node\" &";
		else if(nodesToRespawn_[i]=="checkProhibitedArea_node")
			command="xterm -e \"rosrun osmosis_control checkProhibitedArea.py\" &";
		else
			command="xterm -e \"rosrun osmosis_control " + nodesToRespawn_[i] + "\" &";
		system(command.c_str());
	}
}

void RM4_RespawnNodes::doRecovery()
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

	n_++;
}

void RM4_RespawnNodes::stopRecovery()
{
}
