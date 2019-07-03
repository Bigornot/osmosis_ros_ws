#include <osmosis_control/Tree.hpp>

using namespace std;

Tree::Tree()
{
	// Declarations of the recovery modules 
	// The recovery tree is built here
	// RMx_ = new RM_type(id, antecedent, {successors})
	RM1_emergency_stop_ = new RM1_EmergencyStop(1, 0, {2});
	RM2_controlled_stop_ = new RM2_ControlledStop(2, 1, {3,4,5});
	RM3_ = new RM3_test3(3, 2, {});
	RM4_ = new RM4_test4(4, 2, {});
	RM5_switch_to_teleop_ = new RM5_SwitchToTeleop(5, 2, {});

	// Declarations of the detection modules 
	// DMx_ = new DM_type()
	DM1_prohibited_area_ = new DM1_ProhibitedArea();	
	DM2_cmd_not_updated_ = new DM2_CmdNotUpdated();
	DM3_wrong_command_ = new DM3_WrongCommand();
	DM5_node_crash_ = new DM5_NodeCrash();

	// Declarations of the rules (linking of detection modules and recovery modules)
	// The FMT tree the built here
	// FTM_.push_back(new FTM_Rule(id, antecedent, {successors}, DMx_, RMx_))
	FTM_.push_back(new FTM_Rule(1, 0, {2, 3}, DM1_prohibited_area_, RM1_emergency_stop_));
	FTM_.push_back(new FTM_Rule(2, 1, {4}, DM1_prohibited_area_, RM3_));
	FTM_.push_back(new FTM_Rule(3, 1, {5,6}, DM1_prohibited_area_, RM3_));
	FTM_.push_back(new FTM_Rule(4, 2, {}, DM1_prohibited_area_, RM3_));
	FTM_.push_back(new FTM_Rule(5, 3, {}, DM1_prohibited_area_, RM1_emergency_stop_));
	FTM_.push_back(new FTM_Rule(6, 3, {}, DM1_prohibited_area_, RM3_));
}

void Tree::runDMs()
{
	for(int i=0; i<FTM_.size(); i++)
		FTM_[i]->runDM();
}

void Tree::runRMs()
{
	for(int i=0; i<FTM_.size(); i++)
		FTM_[i]->runRM();
}

bool Tree::onlyOneDominantFTM()
{
	dominant_.clear();
	dominated_.clear();

	this->findDominant();

	return dominant_.size()==1;
}

bool Tree::onlyOneDominantRecovery()
{
	this->findDominantRecovery();
	
	return dominant_.size()==1;
}

void Tree::findDominant()
{
	bool promoted_to_dominant=true;

	for (int i=0; i<Triggered_rules_.size(); i++)//for each Triggered rules
	{
		findDominated(Triggered_rules_[i]);
	}

	for (int i=0; i<Triggered_rules_.size(); i++)//for each Triggered rules
	{
		promoted_to_dominant=true;
		for (int j=0;j<dominated_.size();j++)
		{
			if(dominated_[j]->getId()==Triggered_rules_[i]->getId())
			{
				promoted_to_dominant=false;
			}
		}
		if (promoted_to_dominant && !this->findRule(dominant_, Triggered_rules_[i]))
			dominant_.push_back(Triggered_rules_[i]);
		
	}
}

void Tree::showDominants()
{
	for(int i=0; i<dominant_.size(); i++)
		cout << "dom : " << dominant_[i]->getId() << endl;
	cout << endl;
}

void Tree::findDominated(FTM_Rule* Dominant_rule)
{
	vector<int> successorsId = Dominant_rule->getSuc();
	for (int i=0; i<successorsId.size(); i++)
	{
		for(int j=0; j<FTM_.size(); j++)
		{
			if(successorsId[i]==FTM_[j]->getId() && !this->findRule(dominated_, FTM_[j]))
			{
				dominated_.push_back(FTM_[j]);
				findDominated(FTM_[j]);
			}
		}
	}
}

void Tree::doLowestCommonDominantRecovery()
{
	cout << "before check" << endl;
	showDominants();
	checkSameRM();	
	cout << "after check" << endl;
	showDominants();
	findLowestCommonDominant();
	commonDominant->startRM();
	this->runRMs();
}

void Tree::checkSameRM()
{
	vector<FTM_Rule*> back_dominant=dominant_;
	dominant_.clear();

	for(int i=0; i<back_dominant.size(); i++)
	{
		if(!findRM(dominant_, back_dominant[i]))
			dominant_.push_back(back_dominant[i]);
	}
}

void Tree::findLowestCommonDominant()
{
	vector<FTM_Rule*> new_RMdominant;
	if (onlyOneDominantRecovery())
		commonDominant=RMdominant_[0];
	else
	{
		for (int i=0; i<dominant_.size(); i++)
		{
			for (int j=0; j<FTM_.size(); j++)
			{
				if (dominant_[i]->getAnt()==FTM_[j]->getId() && !findRule(new_RMdominant, FTM_[j]))
				{
					new_RMdominant.push_back(FTM_[j]);
				}
			}
		}
		RMdominant_=new_RMdominant;
		findLowestCommonDominant();
	}
}

bool Tree::findRM(vector<FTM_Rule*> &rules, FTM_Rule* rule)
{
	bool found=false;

	for(int i=0; i<rules.size(); i++)
	{
		if(rules[i]->getRMId() == rule->getRMId())
			found=true;
	}

	return found;
}

bool Tree::findRule(vector<FTM_Rule*> &rules, FTM_Rule* rule)
{
	bool found=false;

	for(int i=0; i<rules.size(); i++)
	{
		if(rules[i]->getId() == rule->getId())
			found=true;
	}

	return found;
}

void Tree::doRecovery()
{
	if(dominant_.size())
	{
		for(int i=0; i<dominant_.size(); i++)
			dominant_[i]->startRM();
	}
	else
		Triggered_rules_[0]->startRM();

	this->runRMs();
}

void Tree::findDominantRecovery()
{
	bool promoted_to_RMdominant=true;
	RMdominant_.clear();
	dominated_.clear();

	for (int i=0; i<dominant_.size(); i++)//for each dominant
	{
		findDominatedRecovery(dominant_[i]);
	}

	for (int i=0; i<dominant_.size(); i++)//for each dominant
	{
		promoted_to_RMdominant=true;
		for (int j=0;j<dominated_.size();j++)
		{
			if(dominated_[j]->getId()==dominant_[i]->getRMId())
			{
				promoted_to_RMdominant=false;
			}
		}
		if (promoted_to_RMdominant && !this->findRM(RMdominant_, dominant_[i]))
			RMdominant_.push_back(dominant_[i]);
	}
}

void Tree::findDominatedRecovery(FTM_Rule* Dominant_rule)
{
	vector<int> successorsId = Dominant_rule->getRMSuc();
	for (int i=0; i<successorsId.size();i++)
	{
		for(int j=0; j<FTM_.size(); j++)
		{
			if(successorsId[i]==FTM_[j]->getRMId() && !findRM(dominated_, FTM_[j]))
			{
				dominated_.push_back(FTM_[j]);
				findDominatedRecovery(FTM_[j]);
			}
		}
	}
}

int Tree::getNbTriggeredFTM()
{
	Triggered_rules_.clear();
	dominant_.clear();
	dominated_.clear();

	/*this->runDMs();


	for(int i=0; i<FTM_.size(); i++)
	{
		if(FTM_[i]->getStateDM())
			Triggered_rules_.push_back(*FTM_[i]);
	}*/

	Triggered_rules_.push_back(FTM_[1]);
	Triggered_rules_.push_back(FTM_[2]);
	Triggered_rules_.push_back(FTM_[4]);

	return Triggered_rules_.size();
}


