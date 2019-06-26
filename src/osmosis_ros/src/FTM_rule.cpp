#include <osmosis_control/FTM_rule.hpp>

//constructor

FTM_rule::FTM_rule(string name1,string name2)
{
	detection_name_topic_=name1;
	recovery_name_topic_=name2;
	Detect_sub_=nh_.subscribe(detection_name_topic_,10,&FTM_rule::RulesCallbackDetection,this);
	Recov_pub_=nh_.advertise<std_msgs::Bool>(recovery_name_topic_,10);
}

void FTM_rule::RulesCallbackDetection(const std_msgs::Bool &detecteur)
{
	detection_etat_=detecteur.data;
	std::cout << std::boolalpha;
}

bool FTM_rule::detection_state()
{
	return detection_etat_;
}

void FTM_rule::recovery_state(bool recovery_etat)
{
	recovery_.data=recovery_etat;

	Recov_pub_.publish(recovery_);
}

