#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <osmosis_control/FTM_Rule.hpp>

#include <osmosis_control/DetectionModules/DM1_ProhibitedArea.hpp>
#include <osmosis_control/DetectionModules/DM2_CmdNotUpdated.hpp>
#include <osmosis_control/DetectionModules/DM3_WrongCommand.hpp>
#include <osmosis_control/DetectionModules/DM5_NodeCrash.hpp>

#include <osmosis_control/RecoveryModules/RM1_EmergencyStop.hpp>
#include <osmosis_control/RecoveryModules/RM2_ControlledStop.hpp>
#include <osmosis_control/RecoveryModules/RM3_test3.hpp>
#include <osmosis_control/RecoveryModules/RM4_test4.hpp>
#include <osmosis_control/RecoveryModules/RM5_SwitchToTeleop.hpp>

using namespace std;

class Tree
{
private :
	vector<FTM_Rule*> FTM_;

	DM1_ProhibitedArea* DM1_prohibited_area_;
	DM2_CmdNotUpdated* DM2_cmd_not_updated_;
	DM3_WrongCommand* DM3_wrong_command_;
	DM5_NodeCrash* DM5_node_crash_;

	RM1_EmergencyStop* RM1_emergency_stop_;
	RM2_ControlledStop* RM2_controlled_stop_;
	RM3_test3* RM3_;
	RM4_test4* RM4_;
	RM5_SwitchToTeleop* RM5_switch_to_teleop_;

	vector<FTM_Rule*> Triggered_rules_;
	vector<FTM_Rule*> dominant_;
	vector<FTM_Rule*> dominated_;
	vector<FTM_Rule*> RMdominant_;
	FTM_Rule* commonDominant;

	void findDominant();
	void findDominantRecovery();
	void findDominated(FTM_Rule* Dominant_rule);
	void findDominatedRecovery(FTM_Rule* Dominant_rule);

	void runDMs();
	void runRMs();

	void checkSameRM();
	bool findRule(vector<FTM_Rule*> &rules, FTM_Rule* rule);
	bool findRM(vector<FTM_Rule*> &rules, FTM_Rule* rule);

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
