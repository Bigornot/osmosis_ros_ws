#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Tree
{
private :
	vector<FTM_Rule> dominant_;
	vector<FTM_Rule> Triggered_rules_;


public :
	Tree();
	void findDominant(vector<FTM_Rule> Triggered_rules);
	void findDominated(FTM_Rule Dominant_rule);

	bool onlyOneDominantFTM();
	bool onlyOneDominantRecovery();
	int getNbTriggeredFTM();
	void doLowestCommonDominantRecovery();
	void doRecovery();


};
