#include <osmosis_control/FTM_Manager.hpp>

FTM_Manager::FTM_Manager()
{
	//Initialisation du graphe

	//Initialisation des FTM
	FTM_Rule1 = new FTM_rule("DM1_ProhibitedArea","/Call_EmergencyStop");
	//FTM_Rule2 = new FTM_rule("CmdNotUpdated","/Call_ControlStop");
	//FTM_Rule3 = new FTM_rule("OutRange","/Call_ControlStop");
	//FTM_Rule6 = new FTM_rule("BadApprox","/Call_ControlStop");
	//FTM_Tree = new Tree_Vector();

	//FTM_Tree->Recovery_list={false, false ,false ,false ,false, false, false, false};
}

bool FTM_Manager::run()
{
	ros::Rate loop_rate(10);
	while (nh_.ok())
	{
		ros::spinOnce();
		loop_rate.sleep();

		FTM_detect1=FTM_Rule1->detection_state();
		FTM_detect2=FTM_Rule2->detection_state();
		FTM_detect3=false;//FTM_Rule3->detection_state();
		FTM_detect4=false;
		FTM_detect5=false;
		FTM_detect6=FTM_Rule6->detection_state();

		FTM_Tree->Detection_list[0]=FTM_detect1;
		FTM_Tree->Detection_list[1]=FTM_detect2;
		FTM_Tree->Detection_list[2]=FTM_detect3;
		FTM_Tree->Detection_list[3]=FTM_detect4;
		FTM_Tree->Detection_list[4]=FTM_detect5;
		FTM_Tree->Detection_list[5]=FTM_detect6;

		FTM_Manager::Algo_FTM();
		//Send the state of recovery to trigger it or not
		std::cout << "1"<<FTM_Tree->Recovery_list[0] << '\n';
		std::cout << "2"<<FTM_Tree->Recovery_list[1] << '\n';
		std::cout << "3"<<FTM_Tree->Recovery_list[2] << '\n';
		std::cout << "4"<<FTM_Tree->Recovery_list[3] << '\n';
		std::cout << "5"<<FTM_Tree->Recovery_list[4] << '\n';
		std::cout << "6"<<FTM_Tree->Recovery_list[5] << '\n';

		FTM_Rule1->recovery_state(FTM_Tree->Recovery_list[0]);
		FTM_Rule2->recovery_state(FTM_Tree->Recovery_list[1]);
		//FTM_Rule3->recovery_state(FTM_Tree->Recovery_list[2]);
		FTM_Rule6->recovery_state(FTM_Tree->Recovery_list[5]);
	}

	return true;
}

void FTM_Manager::Algo_FTM()
{
	//Get the data of the detection
	FTM_Tree->Liste_FTM.clear();
	for (int k=0;k<FTM_Tree->Detection_list.size();k++)
	{
		bool test=FTM_Tree->Detection_list[k];
		if(test)
		{
			FTM_Tree->Liste_FTM.push_back(FTM_Tree->Liste_FTM_originale[k]);
		}
		else
		{

		}
	}

	Nb_FTM=FTM_Tree->Liste_FTM.size();
	Nb_BRANCH=FTM_Tree->FTM_Branch.size();

	for (int i=0;i<Nb_BRANCH;i++)
	{
		tableau.clear();
		for (int j=0;j<Nb_FTM;j++)
		{
			pointer=std::find(FTM_Tree->FTM_Branch[i].begin(),FTM_Tree->FTM_Branch[i].end(),FTM_Tree->Liste_FTM[j]);
			if (*pointer==FTM_Tree->Liste_FTM[j])
			{	
				tableau.push_back(pointer);
			}
		}
		if (tableau.size()==1)
		{
			pointer2=std::find(FTM_Tree->Liste_FTM_originale.begin(),FTM_Tree->Liste_FTM_originale.end(),*tableau[0]);
			if(*pointer2==*tableau[0])
			{
				FTM_Tree->Recovery_list[std::distance(FTM_Tree->Liste_FTM_originale.begin(),pointer2)]=true;
			}
		}

		if(tableau.size()>1)
		{
			for(int l=0;l<tableau.size()-1;l++)
			{
				if(distance(tableau[l],tableau[l+1])<0)
				{
					pointergagnant=tableau[l];
				}
			}
			pointer2=std::find(FTM_Tree->Liste_FTM_originale.begin(),FTM_Tree->Liste_FTM_originale.end(),*pointergagnant);
			if(*pointer2==*pointergagnant)
			{
				FTM_Tree->Recovery_list[std::distance(FTM_Tree->Liste_FTM_originale.begin(),pointer2)]=true;
			}

		}
		else
		{
		}
	}
	//FROM HERE WE HAVE ALREADY CHOOSEN THE FTM WHICH WIN OVER

	FTM_Tree->Liste_Recovery.clear();

	for (int k=0;k<FTM_Tree->Recovery_list.size();k++)
	{
		bool test2=FTM_Tree->Recovery_list[k];
		if(test2)
		{
			FTM_Tree->Liste_Recovery.push_back(FTM_Tree->Liste_Recovery_originale[k]);
		}
		else
		{
		}
	}

	int Nb_Recovery=FTM_Tree->Liste_Recovery.size();
	int Nb_BRANCH1=FTM_Tree->Recovery_Branch.size();

	for (int i=0;i<Nb_BRANCH1;i++)
	{
		tableau1.clear();
		for (int j=0;j<Nb_Recovery;j++)
		{
			pointer3=std::find(FTM_Tree->Recovery_Branch[i].begin(),FTM_Tree->Recovery_Branch[i].end(),FTM_Tree->Liste_Recovery[j]);
			if (*pointer3==FTM_Tree->Liste_Recovery[j])
			{
				tableau1.push_back(pointer3);
			}
		}
		if (tableau1.size()==1)
		{
			pointer4=std::find(FTM_Tree->Liste_Recovery_originale.begin(),FTM_Tree->Liste_Recovery_originale.end(),*tableau1[0]);
			if(*pointer4==*tableau1[0])
			{
				FTM_Tree->Recovery_list[std::distance(FTM_Tree->Liste_Recovery_originale.begin(),pointer4)]=true;
			}
		}
		if(tableau1.size()>1)
		{
			for(int l=0;l<tableau1.size()-1;l++)
			{
				if(distance(tableau1[l],tableau1[l+1])<0)
				{
					pointergagnant1=tableau1[l];
					pointerperdant1=tableau1[l+1];
				}
			}
			pointer4=std::find(FTM_Tree->Liste_Recovery_originale.begin(),FTM_Tree->Liste_Recovery_originale.end(),*pointergagnant1);
			pointer5=std::find(FTM_Tree->Liste_Recovery_originale.begin(),FTM_Tree->Liste_Recovery_originale.end(),*pointerperdant1);
			if(*pointer4==*pointergagnant1)
			{
				FTM_Tree->Recovery_list[std::distance(FTM_Tree->Liste_Recovery_originale.begin(),pointer4)]=true;
			}

			if(*pointer5==*pointerperdant1)
			{
				FTM_Tree->Recovery_list[std::distance(FTM_Tree->Liste_Recovery_originale.begin(),pointer5)]=false;
			}


		}
		else
		{
		}
	}

	a=0;
}

int main(int argc, char** argv)
{
	//init the ROS node
	ros::init(argc, argv, "FTM_Manager_node");

	FTM_Manager myManager;
	myManager.run();
}
