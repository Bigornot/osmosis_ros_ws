#include <osmosis_control/FTM_Manager.hpp>

FTM_Manager::FTM_Manager()
{
	//FTM.push_back(new FTM_Rule(1, 0, {2,3}, &DM1_prohibited_area_, &RM3_emergency_stop_));
	
	//FTM_Tree = new Tree(FTM);
	nbTriggeredFTM_=0;
}

bool FTM_Manager::run()
{
	ros::Rate loop_rate(10);
	while (nh_.ok())
	{
		// checks all DMs' state
		nbTriggeredFTM_ = FTM_Tree.getNbTriggeredFTM(); 

		// If there is only one triggered FTM
		if(nbTriggeredFTM_==1)
			FTM_Tree.doRecovery(); // Then there is no conflict, the recovery can be done

		// If there are many FTMs
		else if(nbTriggeredFTM_>1)
		{
			// If there is only one dominant
			if(FTM_Tree.onlyOneDominantFTM()) // Save the found dominants and return if there is only one
				FTM_Tree.doRecovery(); // Then there is no conflict, the recovery can be done

			// If there are many dominant FTMs
			else
			{
				// If there is only one dominant recovery
				if(FTM_Tree.onlyOneDominantRecovery()) // Check the Recovery Tree to select the right FTM to execute
					FTM_Tree.doRecovery(); // Then this recovery can be done

				// If there are still many dominant recoveries
				// The choosen strategy is applied
				else
					FTM_Tree.doLowestCommonDominantRecovery(); // Safety First : so the lowest common dominant recovy is done
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
