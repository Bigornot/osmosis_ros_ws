#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <osmosis_control/FTM_Rule.hpp>

#include <osmosis_control/DetectionModules/DM1_ProhibitedArea.hpp>
//#include <osmosis_control/DetectionModules/DM2_CmdNotUpdated.hpp>
//#include <osmosis_control/DetectionModules/DM3_WrongCommand.hpp>
//#include <osmosis_control/DetectionModules/DM5_NodeCrash.hpp>

#include <osmosis_control/RecoveryModules/RM1_test1.hpp>
#include <osmosis_control/RecoveryModules/RM2_test2.hpp>
#include <osmosis_control/RecoveryModules/RM3_EmergencyStop.hpp>
#include <osmosis_control/RecoveryModules/RM4_test4.hpp>
#include <osmosis_control/RecoveryModules/RM5_test5.hpp>

using namespace std;

class Tree
{
private :
	vector<FTM_Rule*> FTM_;

	DM1_ProhibitedArea* DM1_prohibited_area_;
	//DM2_CmdNotUpdated* DM2_cmd_not_updated_;
	//DM3_WrongCommand* DM3_wrong_command_;
	//DM5_NodeCrash* DM5_node_crash_;

	RM1_test1* RM1_;
	RM2_test2* RM2_;
	RM3_EmergencyStop* RM3_emergency_stop_;
	RM4_test4* RM4_;
	RM5_test5* RM5_;

	vector<FTM_Rule*> dominant_;
	vector<FTM_Rule*> dominated_;
	vector<FTM_Rule*> Triggered_rules_;
	FTM_Rule* commonDominant;

	void findDominant();
	void findDominantRecovery();
	void findDominated(FTM_Rule* Dominant_rule);
	void findDominatedRecovery(FTM_Rule* Dominant_rule);

	void runDMs();
	void runRMs();

	bool findRule(vector<FTM_Rule*> &rules, FTM_Rule* rule);

public :
	Tree();

	void showDominants();
	bool onlyOneDominantFTM();
	bool onlyOneDominantRecovery();

	int getNbTriggeredFTM();
	void doLowestCommonDominantRecovery();
	void findLowestCommonDominant();
	void doRecovery();


};
