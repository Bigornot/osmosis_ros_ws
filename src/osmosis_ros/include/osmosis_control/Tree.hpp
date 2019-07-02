#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <osmosis_control/FTM_Rule.hpp>

#include <osmosis_control/DetectionModules/DM1_ProhibitedArea.hpp>
//#include <osmosis_control/DetectionModules/DM2_CmdNotUpdated.hpp>
//#include <osmosis_control/DetectionModules/DM3_WrongCommand.hpp>
//#include <osmosis_control/DetectionModules/DM5_NodeCrash.hpp>

#include <osmosis_control/RecoveryModules/RM3_EmergencyStop.hpp>

using namespace std;

class Tree
{
private :
	vector<FTM_Rule*> FTM_;

	DM1_ProhibitedArea DM1_prohibited_area_;
	//DM2_CmdNotUpdated DM2_cmd_not_updated_;
	//DM3_WrongCommand DM3_wrong_command_;
	//DM5_NodeCrash DM5_node_crash_;

	RM3_EmergencyStop RM3_emergency_stop_;

	vector<FTM_Rule*> dominant_;
	vector<FTM_Rule*> dominated_;
	vector<FTM_Rule*> Triggered_rules_;
	FTM_Rule* commonDominant;

	void findDominant();
	void findDominantRecovery();
	void findDominated(FTM_Rule* Dominant_rule);
	void findDominatedRecovery(FTM_Rule* Dominant_rule);


	void runDMs();

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
