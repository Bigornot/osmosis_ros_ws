#include <osmosis_control/Tree.hpp>

using namespace std;

Tree::Tree()
{

}

void Tree::FindDominant(vector<FTM_Rule> Triggered_rules_)
{
	bool promoted_to_dominant=true;
	dominant.clear();
	vector<FTM_Rule> dominated;
	vector<FTM_Rule> successors;

	for (int i=0; i<Triggered_rules_.size(); i++)//for each Rules
	{
		FindDominated(Triggered_rules_[i]);
	}

	for (int i=0; i<Triggered_rules_.size(); i++)//for each Dominated Rules
	{
		promoted_to_dominant=true;
		for (int j=0;j<dominated.size();j++)
		{
			if (dominated[j]==Triggered_rules_[i])
			{
				promoted_to_dominant=false;
			}
		}
		if (promoted_to_dominant)
			dominant.push_back(Triggered_rules_);
	}
}

void Tree::FindDominated(FTM_Rule Dominant_rule)
{
	successors=getSuc(Dominant_rule);
	for (int i=0; i<successors.size();i++)
	{
		dominated.push_back(successors[i]);
		FindDominated(successors[i]);
	}
}

int Tree::getNbTriggeredFTM()
{
	return Triggered_rules_.size();
}
