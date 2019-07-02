#include <osmosis_control/FTM_Manager.hpp>

using namespace std;

FTM_Manager::FTM_Manager()
{
	nbTriggeredFTM_=0;
	ROS_INFO("DEBUT DEBUG\n");

	nbTriggeredFTM_ = FTM_Tree_.getNbTriggeredFTM();
	cout << "nb:" << nbTriggeredFTM_ << endl;

	
	cout << "onlyOneDominant:" << FTM_Tree_.onlyOneDominantFTM() << endl;
	FTM_Tree_.showDominants();
	
	ROS_INFO("FIN DEBUG\n");
	while(1){};
}

bool FTM_Manager::run()
{
	ros::Rate loop_rate(10);
	while (nh_.ok())
	{
		// checks all DMs' state 
		nbTriggeredFTM_ = FTM_Tree_.getNbTriggeredFTM();

		// If there is only one triggered FTM
		if(nbTriggeredFTM_==1)
			FTM_Tree_.doRecovery(); // Then there is no conflict, the recovery can be done

		// If there are many FTMs
		else if(nbTriggeredFTM_>1)
		{
			// If there is only one dominant
			if(FTM_Tree_.onlyOneDominantFTM()) // Save the found dominants and return if there is only one
				FTM_Tree_.doRecovery(); // Then there is no conflict, the recovery can be done

			// If there are many dominant FTMs
			else
			{
				// If there is only one dominant recovery
				if(FTM_Tree_.onlyOneDominantRecovery()) // Check the Recovery Tree to select the right FTM to execute
					FTM_Tree_.doRecovery(); // Then this recovery can be done

				// If there are still many dominant recoveries
				// The choosen strategy is applied
				else
					FTM_Tree_.doLowestCommonDominantRecovery(); // Safety First : so the lowest common dominant recovery is done
			}
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
