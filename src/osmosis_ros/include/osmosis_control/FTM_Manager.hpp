#ifndef DEF_FTM_MANAGER
#define DEF_FTM_MANAGER

#include <iostream>
#include <ros/ros.h>
#include <string>
#include <vector>
#include <std_msgs/Bool.h>
#include <osmosis_control/FTM_Rule.hpp>
#include <osmosis_control/Tree_Vector.hpp>

using namespace std;
class FTM_Manager
{
private :
	//Construction of FTM_rule
	ros::NodeHandle nh_;
	FTM_rule* FTM_Rule1;
	FTM_rule* FTM_Rule2;
	FTM_rule* FTM_Rule3;
	FTM_rule* FTM_Rule6;
	Tree_Vector* FTM_Tree;

	//State of the detector
	bool FTM_detect1;
	bool FTM_detect2;
	bool FTM_detect3;
	bool FTM_detect4;
	bool FTM_detect5;
	bool FTM_detect6;

	//State of the recovery to send
	bool FTM_recov1=false;
	bool FTM_recov2=false;
	bool FTM_recov3=false;

	//DECLARATION HORS ROS
	// vECTOR
	//std::vector<string> FTM_Branch1 = {"FTM4","FTM2","FTM1"};
	//std::vector<string> FTM_Branch2 = { "FTM5", "FTM2","FTM1"};
	//std::vector<string> FTM_Branch3 = { "FTM6", "FTM3","FTM1" }; //Include in Tree_Vector.cpp
	//std::vector<vector<string>> FTM_Branch = {FTM_Branch1,FTM_Branch2,FTM_Branch3};
	//std::vector<string> Liste_FTM_originale={"FTM1","FTM2","FTM3"};
	//std::vector<bool> Detection_list={FTM_detect1, FTM_detect2, FTM_detect3};
	//std::vector<bool> Recovery_list={FTM_recov1, FTM_recov2,FTM_recov3};
	//std::vector<string> Liste_FTM;
	std::vector<string>::iterator pointer;
	std::vector<string>::iterator pointer2;
	std::vector<string>::iterator pointergagnant;
	std::vector<string>::iterator pointer3;
	std::vector<string>::iterator pointer4;
	std::vector<string>::iterator pointer5;
	std::vector<string>::iterator pointergagnant1;
	std::vector<string>::iterator pointerperdant1;
	std::vector<std::vector<string>::iterator> tableau;
	std::vector<std::vector<string>::iterator> tableau1;

	//constante
	int Nb_BRANCH;//=FTM_Branch.size();
	int Nb_FTM;
	int a=0;

public :
	FTM_Manager();
	void Algo_FTM();
	bool run();

};

#endif
