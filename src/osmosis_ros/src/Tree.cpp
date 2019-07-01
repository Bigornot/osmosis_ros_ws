#include <osmosis_control/Tree.hpp>

using namespace std;

Tree::Tree()
{

}

void Tree::findDominant(vector<FTM_Rule> Triggered_rules_)
{
	bool promoted_to_dominant=true;
	dominant_.clear();
	dominated_.clear();

	for (int i=0; i<Triggered_rules_.size(); i++)//for each Rules
	{
		findDominated(Triggered_rules_[i]);
	}

	for (int i=0; i<Triggered_rules_.size(); i++)//for each Dominated Rules
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

void Tree::findDominated(FTM_Rule Dominant_rule)
{
	vector<int> successorsId = Dominant_rule.getSuc();
	for (int i=0; i<successorsId.size();i++)
	{
		for(int j=0; j<FTM.size(); j++)
		{
			if(successorsId[i]==FTM[j]->getId())
			{
				dominated_.push_back(*FTM[j]);
				findDominated(*FTM[j]);
			}
		}
	}
}

int Tree::getNbTriggeredFTM()
{
	return Triggered_rules_.size();
}
