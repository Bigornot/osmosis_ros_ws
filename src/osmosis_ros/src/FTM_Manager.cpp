#include <osmosis_control/FTM_Manager.hpp>

using namespace std;

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
		Triggered_FTM = FTM_Tree_.getTriggeredFTM();
		cout<<"Triggered FTM : ";
		FTM_Tree_.debugDisplayFTMid(Triggered_FTM);

		if(Triggered_FTM.size()==1)
		{
			cout<< "Only one FTM triggered, so we just activate the recovery : ";
			FTM_Tree_.debugDisplayRMid(Triggered_FTM);
			FTM_Tree_.doRecovery(Triggered_FTM);
		}
		else if(Triggered_FTM.size()>1)
		{
			cout<<"There are more than one FTM activated, maybe one dominates the others..."<<endl;
			dominant=FTM_Tree_.findDominantFTM();
			cout<<"Dominant FTM : ";
			FTM_Tree_.debugDisplayFTMid(dominant);

			if(dominant.size()==1)
			{
				cout<<"Yes, one FTM dominates the others, let's activate its recovery :";
				FTM_Tree_.debugDisplayRMid(dominant);
				FTM_Tree_.doRecovery(dominant);
			}
		
			else
			{
				cout<< "No, there are no unique dominant FTM. Maybe one of their recovery dominates the others..."<<endl;
				dominant_recov=FTM_Tree_.findDominantRecovery(dominant);
				cout<< "Dominant Recovery :";
				FTM_Tree_.debugDisplayRMid(dominant_recov);
	
				if(dominant_recov.size()==1)
				{
					cout<<"Yes, one RM dominates the others, let's activate it : ";
					FTM_Tree_.debugDisplayRMid(dominant_recov);
					FTM_Tree_.doRecovery(dominant_recov);
				}
				
				// The choosen strategy is detailed below
				else
				{
					// Current strategy => Safety First : so the lowest common dominant FTM is applied

					switch(strategy_)
					{
						case SAFETY_FIRST:
							cout<< "No, there are no unique dominant RM. Let's activate the Lowest Common FTM"<<endl;
							commonDominant=FTM_Tree_.findLowestCommonDominant(dominant); 
							cout<<"The common dominant is :";
							FTM_Tree_.debugDisplayFTMid({commonDominant});
							cout<<"so we activate its recovery : ";
							FTM_Tree_.debugDisplayRMid({commonDominant});
							FTM_Tree_.doRecovery({commonDominant});
							break;
					}
				}
			}
		}
		cout<<endl<<endl<<endl<<endl<<endl<<endl;
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
