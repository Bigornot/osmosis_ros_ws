#ifndef DEF_FTM_RULE
#define DEF_FTM_RULE

#include <iostream>
#include <ros/ros.h>
#include <string>
#include <std_msgs/Bool.h>

using namespace std;

class FTM_rule
{
private :
	ros::NodeHandle nh_;
	string detection_name_topic_;
	string recovery_name_topic_;
	ros::Subscriber Detect_sub_;
	ros::Publisher Recov_pub_;
	string name_recovery_;
	bool detection_etat_;
	std_msgs::Bool recouvrement_;

public :
	FTM_rule(string name1,string name2); //constructor
	void RulesCallbackDetection(const std_msgs::Bool &detecteur); //récupere donnée du topics
	bool detection_state(); //method to recuperate the state of detection
	void recovery_state(bool recovery_etat); //method to send to the topic the recovery state
	//string get_name_recovery();
};

#endif
