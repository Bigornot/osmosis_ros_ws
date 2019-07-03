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
		// checks all DMs' state

		Triggered_FTM = FTM_Tree_.getTriggeredFTM();

		// If there is only one triggered FTM
		if(Triggered_FTM.size()==1)
			FTM_Tree_.doRecovery(Triggered_FTM); // Then there is no conflict, the recovery can be done

		dominant=FTM_Tree_.findDominantFTM();
		if(dominant.size()==1) // Save the found dominants and return if there is only one
		{
			FTM_Tree_.doRecovery(dominant); // Then there is no conflict, the recovery can be done
		}
		// If there are many dominant FTMs
		else
		{
			dominant_recov=FTM_Tree_.findDominantRM();
			// If there is only one dominant recovery
			if(dominant_recov.size()==1) // Check the Recovery Tree to select the right FTM to execute
					FTM_Tree_.doRecovery(dominant_recov); // Then this recovery can be done
			// If there are still many dominant recoveries
			// The choosen strategy is applied
			else
			{
				commonDominant=FTM_Tree_.findLowestCommonDominant(dominant); // Safety First : so the lowest common dominant recovery is done
				FTM_Tree_.doRecovery({commonDominant});
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
