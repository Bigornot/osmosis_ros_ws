#include <osmosis_control/Tree.hpp>

using namespace std;

Tree::Tree()
{
	DM1_prohibited_area_ = new DM1_ProhibitedArea();
	RM3_emergency_stop_ = new RM3_EmergencyStop(3, 0, {});

	FTM_.push_back(new FTM_Rule(1, 0, {2, 3}, DM1_prohibited_area_, RM3_emergency_stop_));
	FTM_.push_back(new FTM_Rule(2, 1, {4}, DM1_prohibited_area_, RM3_emergency_stop_));
	FTM_.push_back(new FTM_Rule(3, 1, {5,6}, DM1_prohibited_area_, RM3_emergency_stop_));
	FTM_.push_back(new FTM_Rule(4, 2, {}, DM1_prohibited_area_, RM3_emergency_stop_));
	FTM_.push_back(new FTM_Rule(5, 3, {}, DM1_prohibited_area_, RM3_emergency_stop_));
	FTM_.push_back(new FTM_Rule(6, 3, {}, DM1_prohibited_area_, RM3_emergency_stop_));
}

void Tree::runDMs()
{
	for(int i=0; i<FTM_.size(); i++)
		FTM_[i]->runDM();
}

bool Tree::onlyOneDominantFTM()
{
	this->findDominant();
	
	return dominant_.size()==1;
}

void Tree::findDominant()
{
	bool promoted_to_dominant=true;
	dominant_.clear();
	dominated_.clear();

	for (int i=0; i<Triggered_rules_.size(); i++)//for each Rules
	{
		findDominated(Triggered_rules_[i]);
	}

	for (int i=0; i<Triggered_rules_.size(); i++)//for each Triggered rules
	{
		promoted_to_dominant=true;
		for (int j=0;j<dominated_.size();j++)
		{
			if(dominated_[j].getId()==Triggered_rules_[i].getId())
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
		cout << "dom : " << dominant_[i].getId() << endl;
	cout << endl;
}

void Tree::findDominated(FTM_Rule Dominant_rule)
{
	vector<int> successorsId = Dominant_rule.getSuc();
	for (int i=0; i<successorsId.size();i++)
	{
		for(int j=0; j<FTM_.size(); j++)
		{
			if(successorsId[i]==FTM_[j]->getId())
			{
				dominated_.push_back(*FTM_[j]);
				findDominated(*FTM_[j]);
			}
		}
	}
}

int Tree::getNbTriggeredFTM()
{
	/*this->runDMs();
	
	Triggered_rules_.clear();

	for(int i=0; i<FTM_.size(); i++)
	{
		if(FTM_[i]->getStateDM())
			Triggered_rules_.push_back(*FTM_[i]);
	}*/
	
	Triggered_rules_.push_back(*FTM_[1]);
	Triggered_rules_.push_back(*FTM_[3]);
	Triggered_rules_.push_back(*FTM_[2]);
	Triggered_rules_.push_back(*FTM_[4]);
	Triggered_rules_.push_back(*FTM_[5]);
	Triggered_rules_.push_back(*FTM_[0]);


	return Triggered_rules_.size();
}


