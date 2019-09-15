#include <FTM_Manager.hpp>


////////////////////// PRIVATE //////////////////////

void FTM_Manager::initDMs()
{
	for(int i=0; i<FTM_rules_.size(); i++)
		FTM_rules_[i]->initDM();
}

void FTM_Manager::runDMs()
{
	for(int i=0; i<FTM_rules_.size(); i++)
		FTM_rules_[i]->runDM();
}

void FTM_Manager::runRules()
{
	for(int i=0; i<FTM_rules_.size(); i++)
		FTM_rules_[i]->runFSM();
}

void FTM_Manager::runRMs()
{
	vector<FTM_Rule*> RMs = checkSameRM(FTM_rules_);

	cout << "Run RM, RM state :" << endl;
	for(int i=0; i<RMs.size(); i++)
		RMs[i]->runRM();
}

vector<FTM_Rule*> FTM_Manager::findDominated(FTM_Rule* dominant_rule, vector<FTM_Rule*>* dominated)
{
	vector<int> successorsId = dominant_rule->getSuccessorsId();
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

vector<FTM_Rule*>  FTM_Manager::findDominatedRecovery(FTM_Rule* dominant_rule, vector<FTM_Rule*>* dominated)
{
	vector<int> successorsId = dominant_rule->getRMSuc();
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

vector<FTM_Rule*> FTM_Manager::recursiveLowestCommonDominant(vector<FTM_Rule*> recursive_dominant)
{
	if (recursive_dominant.size()==1)
		return recursive_dominant;

	else
	{
		vector<FTM_Rule*> temprecursive_dominant;
		for (int i=0; i<recursive_dominant.size(); i++)
		{
			for (int j=0; j<FTM_rules_.size(); j++)
			{
				if (recursive_dominant[i]->getPredecessorId()==FTM_rules_[j]->getId() && !findRule(temprecursive_dominant, FTM_rules_[j]))
				{
					temprecursive_dominant.push_back(FTM_rules_[j]);
				}
			}
		}
		recursive_dominant=findDominant(temprecursive_dominant);
		return recursiveLowestCommonDominant(recursive_dominant);
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

vector<FTM_Rule*> FTM_Manager::checkSameRM(vector<FTM_Rule*> rules)
{
	vector<FTM_Rule*> back_rules=rules;
	rules.clear();

	for(int i=0; i<back_rules.size(); i++)
	{
		if(!findRM(rules, back_rules[i]) && !findRule(rules,back_rules[i]))
			rules.push_back(back_rules[i]);
	}
	return rules;
}

void FTM_Manager::stoppingActionDominatedRules(vector<FTM_Rule*> rules)
{
	vector<FTM_Rule*> dominated;

	for(int i=0; i<rules.size(); i++)
		dominated=findDominated(rules[i], &dominated);

	for(int i=0; i<dominated.size(); i++)
		dominated[i]->stopRM();
}


////////////////////// PUBLIC //////////////////////

FTM_Manager::FTM_Manager()
{
	// Declarations of the detection modules
	// DMx_ = new DM_type()
	DM1_prohibited_area_ = new DM1_ProhibitedArea();
	DM2_cmd_not_updated_ = new DM2_CmdNotUpdated();
	DM3_wrong_value_command_ = new DM3_WrongValueCommand();
	DM4_node_crash_control_ = new DM4_NodeCrashControl();
	DM5_node_crash_ = new DM5_NodeCrash();
	DM6_loc_not_updated_ = new DM6_LocNotUpdated();
	DM7_node_localization_crash_ = new DM7_NodeLocalizationCrash();

	// Declarations of the recovery modules
	// The recovery tree is built here
	// RMx_ = new RM_type(id, predecessor, {successors})
	RM1_emergency_stop_ = new RM1_EmergencyStop(1, {2,5});
	RM2_controlled_stop_ = new RM2_ControlledStop(2, {3,4});
	RM3_respawn_control_nodes_ = new RM3_RespawnControlNodes(3, {});
	RM4_respawn_nodes_ = new RM4_RespawnNodes(4, {});
	RM5_switch_to_teleop_ = new RM5_SwitchToTeleop(5, {3,4});

	// Declarations of the rules (linking of detection modules and recovery modules)
	// The FMT tree the built here
	// FTM_rules_.push_back(new FTM_Rule(id, predecessor, {successors}, DMx_, RMx_))
	FTM_rules_.push_back(new FTM_Rule(1, 0, {2, 3, 6}, DM1_prohibited_area_, RM1_emergency_stop_));
	FTM_rules_.push_back(new FTM_Rule(2, 1, {4}, DM2_cmd_not_updated_, RM2_controlled_stop_));
	FTM_rules_.push_back(new FTM_Rule(3, 1, {}, DM3_wrong_value_command_, RM2_controlled_stop_));
	FTM_rules_.push_back(new FTM_Rule(4, 2, {5}, DM4_node_crash_control_, RM3_respawn_control_nodes_));
	FTM_rules_.push_back(new FTM_Rule(5, 4, {}, DM5_node_crash_, RM4_respawn_nodes_));
	FTM_rules_.push_back(new FTM_Rule(6, 1, {7}, DM6_loc_not_updated_, RM5_switch_to_teleop_));
	FTM_rules_.push_back(new FTM_Rule(7, 6, {}, DM7_node_localization_crash_, RM4_respawn_nodes_));

	strategy_=new FTM_SafetyFirst();

	time_start_ = ros::Time::now();
	delay_before_start_ = 2;
	freq_=20;
}

FTM_Manager::~FTM_Manager()
{
	delete DM1_prohibited_area_;
	delete DM2_cmd_not_updated_;
	delete DM3_wrong_value_command_;
	delete DM4_node_crash_control_;
	delete DM5_node_crash_;
	delete DM6_loc_not_updated_;
	delete DM7_node_localization_crash_;

	delete RM1_emergency_stop_;
	delete RM2_controlled_stop_;
	delete RM3_respawn_control_nodes_;
	delete RM4_respawn_nodes_;
	delete RM5_switch_to_teleop_;

	for(int i=0; i<FTM_rules_.size(); ++i)
		delete FTM_rules_[i];

	delete strategy_;
}

vector<FTM_Rule*> FTM_Manager::getActiveOrRecoveryRules()
{
	active_or_recovery_rules_.clear();

	for(int i=0; i<FTM_rules_.size(); i++)
	{
		// If the rule is ACTIVE or in RECOVERY
		if(FTM_rules_[i]->getState())
		{
			active_or_recovery_rules_.push_back(FTM_rules_[i]);
		}
	}
	cout << endl;

	return active_or_recovery_rules_;
}

vector<FTM_Rule*> FTM_Manager::findDominant(vector<FTM_Rule*> rules)
{
	vector<FTM_Rule*> dominated;
	vector<FTM_Rule*> dominant;

	for (int i=0; i<rules.size(); i++)//for each rules
	{
		dominated=findDominated(rules[i],&dominated);
	}

	cout << "Dominated FTM :";
	for(int i=0; i<dominated.size(); i++)
		cout << " " << dominated[i]->getId();
	cout << endl;

	for (int i=0; i<rules.size(); i++)//for each rules
	{
		if(!findRule(dominated, rules[i]) && !findRule(dominant, rules[i]))
			dominant.push_back(rules[i]);
	}
	return dominant;
}

vector<FTM_Rule*> FTM_Manager::findDominantRecovery(vector<FTM_Rule*> rules)
{
	vector<FTM_Rule*> dominated;
	vector<FTM_Rule*> dominant;
	vector<FTM_Rule*> checked;

	checked=checkSameRM(rules);

	for (int i=0; i<rules.size(); i++)//for each rules
	{
		dominated=findDominatedRecovery(rules[i],&dominated);
	}

	cout << "Dominated RM :";
	for(int i=0; i<dominated.size(); i++)
		cout << " " << dominated[i]->getRMId();
	cout << endl;

	for (int i=0; i<rules.size(); i++)//for each rules
	{
		if(!findRule(dominated, rules[i]) && !findRM(dominant, rules[i]))
			dominant.push_back(rules[i]);
	}
	return dominant;
}

FTM_Rule* FTM_Manager::findLowestCommonDominant(vector<FTM_Rule*> dominant)
{
	return recursiveLowestCommonDominant(dominant)[0];
}

void FTM_Manager::doRecovery(vector<FTM_Rule*> rules)
{
	stoppingActionDominatedRules(rules);

	for(int i=0; i<rules.size(); i++)
	{
		if(!rules[i]->getStateRM())
			rules[i]->startRM();
	}
}

void FTM_Manager::debugDisplayRulesId(vector<FTM_Rule*> rules)
{
	for (int i=0; i<rules.size();i++)
	{
		cout<<rules[i]->getId()<<" ";
	}
	cout<<endl;
	cout<<endl;
}

void FTM_Manager::debugDisplayRMId(vector<FTM_Rule*> rules)
{
	for (int i=0; i<rules.size();i++)
	{
		cout<<rules[i]->getRMId()<<" ";
	}
	cout<<endl;
	cout<<endl;
}

void FTM_Manager::run()
{
	ros::Rate loop_rate(freq_);

	// Sleep for delay_before_start_ in order to wait for ROS to initialize
	ros::Duration(delay_before_start_).sleep();

	// Initialize DMs (watchdog, timeout, etc..)
	initDMs();

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
