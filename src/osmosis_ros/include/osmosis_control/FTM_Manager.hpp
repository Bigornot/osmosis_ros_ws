#ifndef DEF_FTM_MANAGER
#define DEF_FTM_MANAGER

#include <iostream>
#include <ros/ros.h>
#include <vector>
#include <algorithm>
#include <std_msgs/Bool.h>
#include <osmosis_control/Tree_Vector.hpp>

#define NB_DM 8
#define NB_RM 5

using namespace std;

class FTM_Manager
{
private:
	ros::NodeHandle nh_;
	ros::Publisher RM3_emergency_pub_;

	ros::Subscriber DM1_ProhibitedArea_sub_;
	ros::Subscriber DM2_CmdNotUpdated_sub_;
	ros::Subscriber DM3_WrongCommand_sub_;
	ros::Subscriber DM5_NodeCrash_sub_;

	vector<int> DM_activated;
	vector<int> RM_activated;
	int DM_id[NB_DM]={1, 2, 3, 5, 7, 6, 4, 9};
	int RM_id[NB_RM]={3, 4, 1, 6, 5};

	vector<int> line;
	vector<int> first_line;
	vector<vector<int>> rules_matrix;

	vector<int> DM_Dominant;
	vector<int> RM_Dominant;

public:
	FTM_Manager();
	bool run();
	void DM1_Callback(const std_msgs::Bool & detected);
	void DM2_Callback(const std_msgs::Bool & detected);
	void DM3_Callback(const std_msgs::Bool & detected);
	void DM5_Callback(const std_msgs::Bool & detected);
	void add_rule(int i,int j);
	void apply_rules();

};

#endif
