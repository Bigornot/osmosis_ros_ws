#include <recoveryModules/RM1_EmergencyStop.hpp>


////////////////////// PUBLIC //////////////////////

RM1_EmergencyStop::RM1_EmergencyStop(int id, vector<int> successors) : RecoveryModule(id, successors)
{
}

void RM1_EmergencyStop::startingAction()
{
	string command = "rosnode kill ";
	string node;
	string cmd;

	node = "osmosis_control_node";
	cmd=command+node;
	system(cmd.c_str());

	node = "safety_pilot_node";
	cmd=command+node;
	system(cmd.c_str());

	node = "localization_node";
	cmd=command+node;
	system(cmd.c_str());

	node = "teleop_node";
	cmd=command+node;
	system(cmd.c_str());

	node = "graph_planner_node";
	cmd=command+node;
	system(cmd.c_str());

	node = "mission_manager_node";
	cmd=command+node;
	system(cmd.c_str());

	node = "checkProhibitedArea_node";
	cmd=command+node;
	system(cmd.c_str());

	node = "joy_teleop_node";
	cmd=command+node;
	system(cmd.c_str());

	node = "HMI_node";
	cmd=command+node;
	system(cmd.c_str());

	node = "joy_node";
	cmd=command+node;
	system(cmd.c_str());

	node = "fault_injection_node";
	cmd=command+node;
	system(cmd.c_str());

	node = "FTM_Manager_node";
	cmd=command+node;
	system(cmd.c_str());
}

void RM1_EmergencyStop::doRecovery()
{
}

void RM1_EmergencyStop::stoppingAction()
{
}
