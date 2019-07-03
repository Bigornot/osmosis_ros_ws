#include <osmosis_control/FTM_Manager.hpp>

using namespace std;

FTM_Manager::FTM_Manager()
{
}

bool FTM_Manager::run()
{
	ros::Rate loop_rate(10);
	while (nh_.ok())
	{

		Triggered_FTM = FTM_Tree_.getTriggeredFTM();
		cout<<"Triggered FTM : ";
		FTM_Tree_.debugDisplayFTMid(Triggered_FTM);

		// If there is only one triggered FTM
		if(Triggered_FTM.size()==1)
		{
			cout<< "Only one FTM triggered, so we just activate the recovery : ";
			FTM_Tree_.debugDisplayRMid(Triggered_FTM);
			FTM_Tree_.doRecovery(Triggered_FTM); // Then there is no conflict, the recovery can be done
		}
		else
		{
			cout<<"There are more than one FTM activated, maybe that one dominates the others..."<<endl;
			dominant=FTM_Tree_.findDominantFTM();
			cout<<"Dominant FTM : ";
			FTM_Tree_.debugDisplayFTMid(dominant);
			if(dominant.size()==1) // Save the found dominants and return if there is only one
			{
				cout<<"Yes, one FTM dominates the others, let's activate its recovery :";
				FTM_Tree_.debugDisplayRMid(dominant);
				FTM_Tree_.doRecovery(dominant); // Then there is no conflict, the recovery can be done
			}
			// If there are many dominant FTMs
			else
			{
				cout<< "No, there are no unique dominant FTM. Maybe one of their recovery dominates the others..."<<endl;
				dominant_recov=FTM_Tree_.findDominantRecovery(dominant);
				cout<< "Dominant Recovery :";
				FTM_Tree_.debugDisplayRMid(dominant_recov);
				// If there is only one dominant recovery
				if(dominant_recov.size()==1) // Check the Recovery Tree to select the right FTM to execute
				{
					cout<<"Yes, one RM dominates the others, let's activate it : ";
					FTM_Tree_.debugDisplayRMid(dominant_recov);
					FTM_Tree_.doRecovery(dominant_recov); // Then this recovery can be done
				}
				// If there are still many dominant recoveries
				// The choosen strategy is applied
				else
				{
					cout<< "No, there are no unique dominant RM. Let's activate the Lowest Common FTM"<<endl;
					commonDominant=FTM_Tree_.findLowestCommonDominant(dominant); // Safety First : so the lowest common dominant recovery is done
					cout<<"The common dominant is :";
					FTM_Tree_.debugDisplayFTMid({commonDominant});
					cout<<"so we activate its recovery : ";
					FTM_Tree_.debugDisplayRMid({commonDominant});
					FTM_Tree_.doRecovery({commonDominant});
				}
			}
		}
		cout<<endl;
		cout<<endl;
		cout<<endl;
		cout<<endl;
		cout<<endl;
		cout<<endl;
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
