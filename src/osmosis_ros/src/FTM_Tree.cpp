#include <osmosis_control/FTM_Tree.hpp>

FTM_Tree::FTM_Tree()
{
	// Declarations of the detection modules 
	// DMx_ = new DM_type()
	DM1_prohibited_area_ = new DM1_ProhibitedArea();	
	DM2_cmd_not_updated_ = new DM2_CmdNotUpdated();
	DM3_wrong_command_ = new DM3_WrongCommand();
	DM4_node_crash_ = new DM4_NodeCrash();
	DM5_node_crash_control_ = new DM5_NodeCrashControl();
	DM6_loc_not_updated_ = new DM6_LocNotUpdated();

	// Declarations of the recovery modules 
	// The recovery tree is built here
	// RMx_ = new RM_type(id, predecessor, {successors}, next_activation_delay)
	RM1_emergency_stop_ = new RM1_EmergencyStop(1, {2}, ros::Duration(1));
	RM2_controlled_stop_ = new RM2_ControlledStop(2, {3,4,5}, ros::Duration(1));
	RM3_respawn_control_nodes_ = new RM3_RespawnControlNodes(3, {}, ros::Duration(1));
	RM4_respawn_nodes_ = new RM4_RespawnNodes(4, {}, ros::Duration(1));
	RM5_switch_to_teleop_ = new RM5_SwitchToTeleop(5, {}, ros::Duration(1));
	
	// Declarations of the rules (linking of detection modules and recovery modules)
	// The FMT tree the built here
	// FTM_rules_.push_back(new FTM_Rule(id, predecessor, {successors}, DMx_, RMx_))
	FTM_rules_.push_back(new FTM_Rule(1, 0, {2, 3, 6}, DM1_prohibited_area_, RM1_emergency_stop_));
	FTM_rules_.push_back(new FTM_Rule(2, 1, {5}, DM2_cmd_not_updated_, RM2_controlled_stop_));
	FTM_rules_.push_back(new FTM_Rule(3, 1, {4}, DM3_wrong_command_, RM2_controlled_stop_));
	FTM_rules_.push_back(new FTM_Rule(4, 3, {}, DM4_node_crash_, RM4_respawn_nodes_));
	FTM_rules_.push_back(new FTM_Rule(5, 2, {}, DM5_node_crash_control_, RM3_respawn_control_nodes_));
	FTM_rules_.push_back(new FTM_Rule(6, 1, {}, DM6_loc_not_updated_, RM5_switch_to_teleop_));

}

void FTM_Tree::runDMs()
{
	for(int i=0; i<FTM_rules_.size(); i++)
		FTM_rules_[i]->runDM();
}

void FTM_Tree::runRMs()
{
	for(int i=0; i<FTM_rules_.size(); i++)
		FTM_rules_[i]->runRM();
}

vector<FTM_Rule*> FTM_Tree::findDominant(vector<FTM_Rule*> Rules)
{
	vector<FTM_Rule*> dominated;
	vector<FTM_Rule*> dominant;

	for (int i=0; i<Rules.size(); i++)//for each rules
	{
		dominated=findDominated(Rules[i],&dominated);
	}

	cout << "Dominated FTM :";
	for(int i=0; i<dominated.size(); i++)
		cout << " " << dominated[i]->getId();
	cout << endl;

	for (int i=0; i<Rules.size(); i++)//for each rules
	{
		if(!this->findRule(dominated, Rules[i]) && !this->findRule(dominant, Rules[i]))
			dominant.push_back(Rules[i]);
	}
	return dominant;
}

vector<FTM_Rule*> FTM_Tree::findDominated(FTM_Rule* Dominant_rule, vector<FTM_Rule*>* dominated)
{
	vector<int> successorsId = Dominant_rule->getSuccessorsId();
	for (int i=0; i<successorsId.size(); i++)
	{
		for(int j=0; j<FTM_rules_.size(); j++)
		{
			if(successorsId[i]==FTM_rules_[j]->getId() && !this->findRule(*dominated, FTM_rules_[j]))
			{
				dominated->push_back(FTM_rules_[j]);
				findDominated(FTM_rules_[j], dominated);
			}
		}
	}
	return *dominated;
}

vector<FTM_Rule*> FTM_Tree::findDominantRecovery(vector<FTM_Rule*> Rules)
{	
	vector<FTM_Rule*> dominated;
	vector<FTM_Rule*> dominant;

	for (int i=0; i<Rules.size(); i++)//for each rules
	{
		dominated=findDominatedRecovery(Rules[i],&dominated);
	}

	cout << "Dominated RM :";
	for(int i=0; i<dominated.size(); i++)
		cout << " " << dominated[i]->getId();
	cout << endl;

	for (int i=0; i<Rules.size(); i++)//for each rules
	{
		if(!this->findRule(dominated, Rules[i]) && !this->findRule(dominant, Rules[i]))
			dominant.push_back(Rules[i]);
	}
	return dominant;
}

vector<FTM_Rule*>  FTM_Tree::findDominatedRecovery(FTM_Rule* Dominant_rule, vector<FTM_Rule*>* dominated)
{
	vector<int> successorsId = Dominant_rule->getRMSuc();
	for (int i=0; i<successorsId.size(); i++)
	{
		for(int j=0; j<FTM_rules_.size(); j++)
		{
			if(successorsId[i]==FTM_rules_[j]->getRMId() && !this->findRM(*dominated, FTM_rules_[j]))
			{
				dominated->push_back(FTM_rules_[j]);
				findDominatedRecovery(FTM_rules_[j], dominated);
			}
		}
	}
	return *dominated;
}

FTM_Rule* FTM_Tree::findLowestCommonDominant(vector<FTM_Rule*> dominant)
{
	vector<FTM_Rule*> checked=checkSameRM(dominant);
	cout << "Checked RM :";
	for(int i=0; i<checked.size(); i++)
		cout << " " << checked[i]->getId();
	cout << endl;
	return recursiveLowestCommonDominant(checkSameRM(dominant))[0];
}

vector<FTM_Rule*> FTM_Tree::recursiveLowestCommonDominant(vector<FTM_Rule*> recursiveDominant)
{
	vector<FTM_Rule*> tempRecursiveDominant;

	for (int i=0; i<recursiveDominant.size(); i++)
	{
		for (int j=0; j<FTM_rules_.size(); j++)
		{
			if (recursiveDominant[i]->getPredecessorId()==FTM_rules_[j]->getId() && !findRule(tempRecursiveDominant, FTM_rules_[j]))
			{
				tempRecursiveDominant.push_back(FTM_rules_[j]);
			}
		}
	}
	recursiveDominant=findDominant(tempRecursiveDominant);

	if (recursiveDominant.size()!=1)
		recursiveLowestCommonDominant(recursiveDominant);

	return recursiveDominant;
}

bool FTM_Tree::findRM(vector<FTM_Rule*> rules, FTM_Rule* rule)
{
	bool found=false;

	for(int i=0; i<rules.size(); i++)
	{
		if(rules[i]->getRMId() == rule->getRMId())
			found=true;
	}

	return found;
}

bool FTM_Tree::findRule(vector<FTM_Rule*> rules, FTM_Rule* rule)
{
	bool found=false;

	for(int i=0; i<rules.size(); i++)
	{
		if(rules[i]->getId() == rule->getId())
			found=true;
	}

	return found;
}

void FTM_Tree::doRecovery(vector<FTM_Rule*> activated_rules)
{
	this->stopFinishedRMs(activated_rules);

	for(int i=0; i<activated_rules.size(); i++)
		activated_rules[i]->startRM();

	this->runRMs();
}

void FTM_Tree::stopFinishedRMs(vector<FTM_Rule*> activated_rules)
{
	static vector<FTM_Rule*> last_activated_rules;

	for(int i=0; i<last_activated_rules.size(); i++)
	{
		if(!this->findRule(activated_rules, last_activated_rules[i]))
			last_activated_rules[i]->stopRM();
	}

	last_activated_rules=activated_rules;
}

vector<FTM_Rule*> FTM_Tree::checkSameRM(vector<FTM_Rule*> Rules)
{
	vector<FTM_Rule*> back_Rules=Rules;
	Rules.clear();

	for(int i=0; i<back_Rules.size(); i++)
	{
		if(!findRM(Rules, back_Rules[i]))
			Rules.push_back(back_Rules[i]);
	}
	return Rules;
}

vector<FTM_Rule*> FTM_Tree::getTriggeredFTM()
{
	Triggered_rules_.clear();

	this->runDMs();

	for(int i=0; i<FTM_rules_.size(); i++)
	{
		if(FTM_rules_[i]->getStateDM())
			Triggered_rules_.push_back(FTM_rules_[i]);
	}

	return Triggered_rules_;
}

void FTM_Tree::debugDisplayFTMid(vector<FTM_Rule*> vector)
{
	for (int i=0; i<vector.size();i++)
	{
		cout<<vector[i]->getId()<<" ";
	}
	cout<<endl;
	cout<<endl;
}

void FTM_Tree::debugDisplayRMid(vector<FTM_Rule*> vector)
{
	for (int i=0; i<vector.size();i++)
	{
		cout<<vector[i]->getRMId()<<" ";
	}
	cout<<endl;
	cout<<endl;
}
