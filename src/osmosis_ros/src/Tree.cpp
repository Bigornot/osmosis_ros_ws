#include <osmosis_control/Tree.hpp>

using namespace std;

Tree::Tree()
{
	RM1_ = new RM1_test1(1, 0, {2,3});
	RM2_ = new RM2_test2(2, 1, {4,5});
	RM3_emergency_stop_ = new RM3_EmergencyStop(3, 2, {});
	RM4_ = new RM4_test4(4, 2, {});
	RM5_ = new RM5_test5(5, 2, {});

	DM1_prohibited_area_ = new DM1_ProhibitedArea();

	FTM_.push_back(new FTM_Rule(1, 0, {2, 3}, DM1_prohibited_area_, RM1_));
	FTM_.push_back(new FTM_Rule(2, 1, {4}, DM1_prohibited_area_, RM2_));
	FTM_.push_back(new FTM_Rule(3, 1, {5,6}, DM1_prohibited_area_, RM2_));
	FTM_.push_back(new FTM_Rule(4, 2, {}, DM1_prohibited_area_, RM4_));
	FTM_.push_back(new FTM_Rule(5, 3, {}, DM1_prohibited_area_, RM3_emergency_stop_));
	FTM_.push_back(new FTM_Rule(6, 3, {}, DM1_prohibited_area_, RM5_));
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
		if (promoted_to_dominant)
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
			if(successorsId[i]==FTM_[j]->getId())
			{
				dominated_.push_back(FTM_[j]);
				findDominated(FTM_[j]);
			}
		}
	}
}

void Tree::doLowestCommonDominantRecovery()
{
	findLowestCommonDominant();
	commonDominant->startRM();
	this->runRMs();
}

void Tree::findLowestCommonDominant()
{
	vector<FTM_Rule*> new_dominant;
	if (onlyOneDominantFTM())
		commonDominant=dominant_[0];
	else
	{
		cout << "Taille du dominant " << dominant_.size() << endl;
		for (int i=0; i<dominant_.size(); i++)
		{
			for (int j=0; j<FTM_.size(); j++)
			{
				cout << "do" << i << " Ant " << dominant_[i]->getAnt() << "FTM id " << FTM_[j]->getId() << endl;
				if (dominant_[i]->getAnt()==FTM_[j]->getId() && !findRule(new_dominant, FTM_[j]))
				{
					new_dominant.push_back(FTM_[j]);
				}
			}
		}
		cout << "new_dom size " << new_dominant.size() << endl;
		for(int i=0; i<new_dominant.size(); i++)
			cout << "new_dom " << new_dominant[i]->getId() << endl;
		cout << endl;
		Triggered_rules_=new_dominant;
		findLowestCommonDominant();
	}
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
	bool promoted_to_dominant=true;
	dominant_.clear();
	dominated_.clear();

	for (int i=0; i<Triggered_rules_.size(); i++)//for each Triggered rules
	{
		findDominatedRecovery(Triggered_rules_[i]);
	}

	for (int i=0; i<Triggered_rules_.size(); i++)//for each Triggered rules
	{
		promoted_to_dominant=true;
		for (int j=0;j<dominated_.size();j++)
		{
			if(dominated_[j]->getId()==Triggered_rules_[i]->getRMId())
			{
				promoted_to_dominant=false;
			}
		}
		if (promoted_to_dominant)
			dominant_.push_back(Triggered_rules_[i]);
	}
}

void Tree::findDominatedRecovery(FTM_Rule* Dominant_rule)
{
	vector<int> successorsId = Dominant_rule->getRMSuc();
	for (int i=0; i<successorsId.size();i++)
	{
		for(int j=0; j<FTM_.size(); j++)
		{
			if(successorsId[i]==FTM_[j]->getRMId())
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

	Triggered_rules_.push_back(FTM_[4]);
	Triggered_rules_.push_back(FTM_[5]);

	return Triggered_rules_.size();
}


