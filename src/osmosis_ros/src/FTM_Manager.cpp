#include <osmosis_control/FTM_Manager.hpp>

FTM_Manager::FTM_Manager()
{
	//FTM.push_back(new FTM_Rule(1, 0, {2,3}, &DM1_prohibited_area_, &RM3_emergency_stop_));
	
	//FTM_Tree = new Tree(FTM);
}

bool FTM_Manager::run()
{
	ros::Rate loop_rate(10);
	while (nh_.ok())
	{
		/*
		int nbTriggeredFTM = FTM_Tree.nbTriggeredFTM(); // checks all DMs' state and push in a vector the triggeredFTMs
		if(nbTriggeredFTM==1)
		{
			FTM_Tree.doRecovery(); // Do the recovery of the only FTM in the vector of triggeredFTM
		}

		else if(nbTriggeredFTM>1)
		{
			if()
		}
		*/

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
