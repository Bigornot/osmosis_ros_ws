#include <osmosis_control/FTM_Manager.hpp>

FTM_Manager::FTM_Manager()
{
	freq_=10;
	strategy_=SAFETY_FIRST;
}

bool FTM_Manager::run()
{
	ros::Rate loop_rate(freq_);
	while (nh_.ok())
	{
		// The choosen strategy is detailed below
		// Current strategy => Safety First : so the lowest common dominant FTM is applied
		switch(strategy_)
		{
			case SAFETY_FIRST:
				triggered_rules_ = FTM_tree_.getTriggeredFTM();
				cout<<"------------------------------" << endl;
				cout<<"Triggered rules : ";
				FTM_tree_.debugDisplayFTMid(triggered_rules_);

				if(triggered_rules_.size()==1)
				{
					cout<<"Only one triggered rule, so we just activate its recovery : ";
					FTM_tree_.debugDisplayRMid(triggered_rules_);
					FTM_tree_.doRecovery(triggered_rules_);
				}
				else if(triggered_rules_.size()>1)
				{
					cout<<"There are more than one triggered rule, maybe one dominates the others..."<<endl;
					dominant_=FTM_tree_.findDominant(triggered_rules_);
					cout<<"Dominant rules : ";
					FTM_tree_.debugDisplayFTMid(dominant_);

					if(dominant_.size()==1)
					{
						cout<<"Yes, one rule dominates the others, let's activate its recovery :";
						FTM_tree_.debugDisplayRMid(dominant_);
						FTM_tree_.doRecovery(dominant_);
					}
				
					else
					{
						cout<<"No, there are no unique dominant rule. Maybe one of their recovery dominates the others..."<<endl;
						dominant_recov_=FTM_tree_.findDominantRecovery(dominant_);
						cout<<"Dominant Recovery :";
						FTM_tree_.debugDisplayRMid(dominant_recov_);
			
						if(dominant_recov_.size()==1)
						{
							cout<<"Yes, one RM dominates the others, let's activate it : ";
							FTM_tree_.debugDisplayRMid(dominant_recov_);
							FTM_tree_.doRecovery(dominant_recov_);
						}
						
						else
						{
							cout<<"No, there are no unique dominant RM. Let's activate the Lowest Common Dominant"<<endl;
							commonDominant_=FTM_tree_.findLowestCommonDominant(dominant_); 
							cout<<"The common dominant is :";
							FTM_tree_.debugDisplayFTMid({commonDominant_});
							cout<<"so we activate its recovery : ";
							FTM_tree_.debugDisplayRMid({commonDominant_});
							FTM_tree_.doRecovery({commonDominant_});
							break;
						}
					}
				}
				FTM_tree_.runRMs();
				cout<<endl<<endl<<endl<<endl<<endl<<endl;
				break;

			default:
				break;
		}

		ros::spinOnce();
		loop_rate.sleep();
	}
	
	return true;
}

int main(int argc, char** argv)
{
	//init the ROS node
	ros::init(argc, argv, "FTM_Manager_node");

	FTM_Manager myManager;
	myManager.run();
}
