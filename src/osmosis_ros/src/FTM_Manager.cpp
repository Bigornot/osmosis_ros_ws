#include <osmosis_control/FTM_Manager.hpp>

FTM_Manager::FTM_Manager()
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
	// RMx_ = new RM_type(id, predecessor, {successors})
	RM1_emergency_stop_ = new RM1_EmergencyStop(1, {2,5}, false);
	RM2_controlled_stop_ = new RM2_ControlledStop(2, {3,4}, false);
	RM3_respawn_control_nodes_ = new RM3_RespawnControlNodes(3, {}, true);
	RM4_respawn_nodes_ = new RM4_RespawnNodes(4, {}, true);
	RM5_switch_to_teleop_ = new RM5_SwitchToTeleop(5, {3,4}, false);

	// Declarations of the rules (linking of detection modules and recovery modules)
	// The FMT tree the built here
	// FTM_rules_.push_back(new FTM_Rule(id, predecessor, {successors}, DMx_, RMx_))
	FTM_rules_.push_back(new FTM_Rule(1, 0, {2, 3, 6}, DM1_prohibited_area_, RM1_emergency_stop_));
	FTM_rules_.push_back(new FTM_Rule(2, 1, {4,5}, DM2_cmd_not_updated_, RM2_controlled_stop_));
	FTM_rules_.push_back(new FTM_Rule(3, 1, {}, DM3_wrong_command_, RM2_controlled_stop_));
	FTM_rules_.push_back(new FTM_Rule(4, 5, {}, DM4_node_crash_, RM4_respawn_nodes_));
	FTM_rules_.push_back(new FTM_Rule(5, 2, {4}, DM5_node_crash_control_, RM3_respawn_control_nodes_));
	FTM_rules_.push_back(new FTM_Rule(6, 1, {}, DM6_loc_not_updated_, RM5_switch_to_teleop_));

	strategy_=new FTM_SafetyFirst();

	timeStart_ = ros::Time::now();
	delayBeforeStart_ = 2;
	freq_=20;
}

void FTM_Manager::setDMs()
{
	for(int i=0; i<FTM_rules_.size(); i++)
		FTM_rules_[i]->setDM();
}

void FTM_Manager::runDMs()
{
	for(int i=0; i<FTM_rules_.size(); i++)
		FTM_rules_[i]->runDM();
}

void FTM_Manager::runRMs()
{
	vector<FTM_Rule*> RMs = checkSameRM(FTM_rules_);

	for(int i=0; i<RMs.size(); i++)
		RMs[i]->runRM();
}

vector<FTM_Rule*> FTM_Manager::findDominant(vector<FTM_Rule*> Rules)
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
		if(!findRule(dominated, Rules[i]) && !findRule(dominant, Rules[i]))
			dominant.push_back(Rules[i]);
	}
	return dominant;
}

vector<FTM_Rule*> FTM_Manager::findDominated(FTM_Rule* Dominant_rule, vector<FTM_Rule*>* dominated)
{
	vector<int> successorsId = Dominant_rule->getSuccessorsId();
	for (int i=0; i<successorsId.size(); i++)
	{
		for(int j=0; j<FTM_rules_.size(); j++)
		{
			if(successorsId[i]==FTM_rules_[j]->getId() && !findRule(*dominated, FTM_rules_[j]))
			{
				dominated->push_back(FTM_rules_[j]);
				findDominated(FTM_rules_[j], dominated);
			}
		}
	}
	return *dominated;
}

vector<FTM_Rule*> FTM_Manager::findDominantRecovery(vector<FTM_Rule*> Rules)
{
	vector<FTM_Rule*> dominated;
	vector<FTM_Rule*> dominant;
	vector<FTM_Rule*> checked;

	checked=checkSameRM(Rules);

	for (int i=0; i<Rules.size(); i++)//for each rules
	{
		dominated=findDominatedRecovery(Rules[i],&dominated);
	}

	cout << "Dominated RM :";
	for(int i=0; i<dominated.size(); i++)
		cout << " " << dominated[i]->getRMId();
	cout << endl;

	for (int i=0; i<Rules.size(); i++)//for each rules
	{
		if(!findRule(dominated, Rules[i]) && !findRM(dominant, Rules[i]))
			dominant.push_back(Rules[i]);
	}
	return dominant;
}

vector<FTM_Rule*>  FTM_Manager::findDominatedRecovery(FTM_Rule* Dominant_rule, vector<FTM_Rule*>* dominated)
{
	vector<int> successorsId = Dominant_rule->getRMSuc();
	for (int i=0; i<successorsId.size(); i++)
	{
		for(int j=0; j<FTM_rules_.size(); j++)
		{
			if(successorsId[i]==FTM_rules_[j]->getRMId() && !findRM(*dominated, FTM_rules_[j]))
			{
				dominated->push_back(FTM_rules_[j]);
				findDominatedRecovery(FTM_rules_[j], dominated);
			}
		}
	}
	return *dominated;
}

FTM_Rule* FTM_Manager::findLowestCommonDominant(vector<FTM_Rule*> dominant)
{
	return recursiveLowestCommonDominant(dominant)[0];
}

vector<FTM_Rule*> FTM_Manager::recursiveLowestCommonDominant(vector<FTM_Rule*> recursiveDominant)
{
	if (recursiveDominant.size()==1)
		return recursiveDominant;

	else
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
		return recursiveLowestCommonDominant(recursiveDominant);
	}
}

bool FTM_Manager::findRM(vector<FTM_Rule*> rules, FTM_Rule* rule)
{
	bool found=false;

	for(int i=0; i<rules.size(); i++)
	{
		if(rules[i]->getRMId() == rule->getRMId())
			found=true;
	}

	return found;
}

bool FTM_Manager::findRule(vector<FTM_Rule*> rules, FTM_Rule* rule)
{
	bool found=false;

	for(int i=0; i<rules.size(); i++)
	{
		if(rules[i]->getId() == rule->getId())
			found=true;
	}

	return found;
}

void FTM_Manager::doRecovery(vector<FTM_Rule*> activated_rules)
{
	for(int i=0; i<activated_rules.size(); i++)
	{
		if(!activated_rules[i]->getStateRM())
			activated_rules[i]->startRM();
	}
}

vector<FTM_Rule*> FTM_Manager::checkSameRM(vector<FTM_Rule*> Rules)
{
	vector<FTM_Rule*> back_Rules=Rules;
	Rules.clear();

	for(int i=0; i<back_Rules.size(); i++)
	{
		if(!findRM(Rules, back_Rules[i]) && !findRule(Rules,back_Rules[i]))
			Rules.push_back(back_Rules[i]);
	}
	return Rules;
}

vector<FTM_Rule*> FTM_Manager::getTriggeredFTM()
{
	Triggered_rules_.clear();

	for(int i=0; i<FTM_rules_.size(); i++)
	{
		// If the rule is ACTIVE or in RECOVERY
		if(FTM_rules_[i]->getState())
		{
			Triggered_rules_.push_back(FTM_rules_[i]);
		}
	}
	cout << endl;

	return Triggered_rules_;
}

void FTM_Manager::debugDisplayFTMid(vector<FTM_Rule*> vector)
{
	for (int i=0; i<vector.size();i++)
	{
		cout<<vector[i]->getId()<<" ";
	}
	cout<<endl;
	cout<<endl;
}

void FTM_Manager::debugDisplayRMid(vector<FTM_Rule*> vector)
{
	for (int i=0; i<vector.size();i++)
	{
		cout<<vector[i]->getRMId()<<" ";
	}
	cout<<endl;
	cout<<endl;
}

void FTM_Manager::runRules()
{
	for(int i=0; i<FTM_rules_.size(); i++)
		FTM_rules_[i]->runState();
}

void FTM_Manager::run()
{
	ros::Rate loop_rate(freq_);

	ros::Duration(delayBeforeStart_).sleep();

	setDMs();

	while(nh_.ok())
	{
		runDMs();
		runRules();
		strategy_->execute(this);
		runRMs();

		ros::spinOnce();
		loop_rate.sleep();
	}
}

////////////////////// MAIN //////////////////////

int main(int argc, char** argv)
{
	//init the ROS node
	ros::init(argc, argv, "FTM_Manager_node");

	FTM_Manager myManager;
	myManager.run();
}
