#ifndef DEF_FTM_MANAGER
#define DEF_FTM_MANAGER

#include <iostream>
#include <ros/ros.h>
#include <vector>
#include <algorithm>
#include <std_msgs/Bool.h>
#include <osmosis_control/Tree_Vector.hpp>

#define NB_DM 6
#define NB_RM 6

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

	Tree_Vector FTM_Tree;

	int DM_id[NB_DM]={1, 2, 3, 5, 6, 7};
	int RM_id[NB_RM]={1, 2, 3, 5, 6, 7};

	vector<int> line;
	vector<int> first_line;
	vector<vector<int>> rules_matrix;

	vector<int> DM_Dominant;
	vector<int> RM_Dominant;
	vector<int> RM_To_Shutdown;
	vector<int> RM_To_Activate;

public:
	FTM_Manager();
	bool run();
	void DM1_Callback(const std_msgs::Bool & detected);
	void DM2_Callback(const std_msgs::Bool & detected);
	void DM3_Callback(const std_msgs::Bool & detected);
	void DM5_Callback(const std_msgs::Bool & detected);
	void add_rule(int i,int j);
	void apply_rules();
	vector<int>::iterator search_in_RM_Dominant(int id);
	//vector<int> compatibility():

};

#endif
