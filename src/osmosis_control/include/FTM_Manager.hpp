/*
 * Copyright 2018 LAAS-CNRS
 *
 * This file is part of the OSMOSIS project.
 *
 * Osmosis is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * Osmosis is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#ifndef OSMOSIS_FTM_Manager_HPP
#define OSMOSIS_FTM_Manager_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <FTM_Rule.hpp>

#include <detectionModules/DM1_ProhibitedArea.hpp>
#include <detectionModules/DM2_CmdNotUpdated.hpp>
#include <detectionModules/DM3_WrongValueCommand.hpp>
#include <detectionModules/DM4_NodeCrashControl.hpp>
#include <detectionModules/DM5_NodeCrash.hpp>
#include <detectionModules/DM6_LocNotUpdated.hpp>
#include <detectionModules/DM7_NodeLocalizationCrash.hpp>

#include <recoveryModules/RM1_EmergencyStop.hpp>
#include <recoveryModules/RM2_ControlledStop.hpp>
#include <recoveryModules/RM3_RespawnControlNodes.hpp>
#include <recoveryModules/RM4_RespawnNodes.hpp>
#include <recoveryModules/RM5_SwitchToTeleop.hpp>

class FTM_Strategy;

class FTM_Manager
{
private :
	///////// Attributes /////////
	ros::NodeHandle nh_;
	double freq_;
	vector<FTM_Rule*> FTM_rules_;

	DM1_ProhibitedArea* DM1_prohibited_area_;
	DM2_CmdNotUpdated* DM2_cmd_not_updated_;
	DM3_WrongValueCommand* DM3_wrong_value_command_;
	DM4_NodeCrashControl* DM4_node_crash_control_;
	DM5_NodeCrash* DM5_node_crash_;
	DM6_LocNotUpdated* DM6_loc_not_updated_;
	DM7_NodeLocalizationCrash* DM7_node_localization_crash_;

	RM1_EmergencyStop* RM1_emergency_stop_;
	RM2_ControlledStop* RM2_controlled_stop_;
	RM3_RespawnControlNodes* RM3_respawn_control_nodes_;
	RM4_RespawnNodes* RM4_respawn_nodes_;
	RM5_SwitchToTeleop* RM5_switch_to_teleop_;

	vector<FTM_Rule*> active_or_recovery_rules_;

	FTM_Strategy* strategy_;
	double delay_before_start_;
	ros::Time time_start_;

	///////// Methods /////////
	void initDMs();
	void runDMs();
	void runRules();
	void runRMs();
	vector<FTM_Rule*> findDominated(FTM_Rule* dominant_rule, vector<FTM_Rule*>* dominated);
	vector<FTM_Rule*> findDominatedRecovery(FTM_Rule* dominant_rule, vector<FTM_Rule*>* dominated);
	vector<FTM_Rule*> recursiveLowestCommonDominant(vector<FTM_Rule*> recursive_dominant);
	bool findRM(vector<FTM_Rule*> rules, FTM_Rule* rule);
	bool findRule(vector<FTM_Rule*> rules, FTM_Rule* rule);
	vector<FTM_Rule*> checkSameRM(vector<FTM_Rule*> rules);
	void stoppingActionDominatedRules(vector<FTM_Rule*> rules);

public :
	FTM_Manager();

	vector<FTM_Rule*> getActiveOrRecoveryRules();
	vector<FTM_Rule*> findDominant(vector<FTM_Rule*> Rules);
	vector<FTM_Rule*> findDominantRecovery(vector<FTM_Rule*> Rules);
	FTM_Rule* findLowestCommonDominant(vector<FTM_Rule*> dominant);
	void doRecovery(vector<FTM_Rule*> rules);

	void debugDisplayRulesId(vector<FTM_Rule*> rules);
	void debugDisplayRMId(vector<FTM_Rule*> rules);

	void run();
};

/////////////////////////////////////////////////////////////////

class FTM_Strategy
{
private :

protected:
	string name_;

public :
	FTM_Strategy(){};
	virtual void execute(FTM_Manager* myManager)=0;
};

/////////////////////////////////////////////////////////////////

class FTM_SafetyFirst : public FTM_Strategy
{
private:
	vector<FTM_Rule*> active_or_recovery_rules_;
	vector<FTM_Rule*> dominant_;
	vector<FTM_Rule*> dominant_recov_;
	FTM_Rule* common_dominant_;
public:
	FTM_SafetyFirst();
	void execute(FTM_Manager* myManager);
};

#endif
