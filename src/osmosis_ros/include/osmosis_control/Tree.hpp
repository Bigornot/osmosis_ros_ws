#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <osmosis_control/FTM_Rule.hpp>

using namespace std;

class Tree
{
private :
	vector<FTM_Rule*> FTM;

	vector<FTM_Rule> dominant_;
	vector<FTM_Rule> dominated_;
	vector<FTM_Rule> Triggered_rules_;

public :
	Tree();
	void findDominant(vector<FTM_Rule> Triggered_rules);
	void findDominated(FTM_Rule Dominant_rule);

	bool onlyOneDominantFTM(){return true;};
	bool onlyOneDominantRecovery(){return true;};
	int getNbTriggeredFTM();
	void doLowestCommonDominantRecovery(){};
	void doRecovery(){};


};
