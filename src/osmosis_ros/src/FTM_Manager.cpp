#include <osmosis_control/FTM_Manager.hpp>

FTM_Manager::FTM_Manager()
{
	FTM_Tree.push_DM(6);

	//TO THE USER :
	//All subscribers and publishers must be declared here
	//publishers (all the RM)
	RM3_emergency_pub_ = nh_.advertise<std_msgs::Bool>("RM3_emergency_shutdown", 1);

	//subscribers (all the DM)
	DM1_ProhibitedArea_sub_  = nh_.subscribe("DM1_ProhibitedArea", 1, &FTM_Manager::DM1_Callback, this);
	DM2_CmdNotUpdated_sub_  = nh_.subscribe("DM2_CmdNotUpdated", 1, &FTM_Manager::DM2_Callback, this);
	DM3_WrongCommand_sub_  = nh_.subscribe("DM3_WrongCommand", 1, &FTM_Manager::DM3_Callback, this);
	DM5_NodeCrash_sub_  = nh_.subscribe("DM5_NodeCrash", 1, &FTM_Manager::DM5_Callback, this);

	//We need a array of all the IDs of DM that we use, don't forget to complete it and the numbers of DM in hpp
	//same for RM

	//now we build the matrix that define the rules
	//the example under has a unique rule "if we have DM1 then do RM3"
	//
	//						_______RM______
	//						id1 id2 id3 id4
	//       |id1  0   0   1   0
	//       |id2  0   0   0   0
	//   DM  |id3  0   0   0   0
	//       |id4  0   0   0   0
	//       |id5  0   0   0   0
	//

	//it starts filled with 0 with ids on the sides

	first_line.push_back(0);
	line.push_back(0);
	for(int j=0;j<NB_RM;j++)
	{
		first_line.push_back(RM_id[j]);
		line.push_back(0);
	}

	rules_matrix.push_back(first_line);

	for (int i=1;i<=NB_DM;i++)
	{
		line[0]=DM_id[i-1];
		rules_matrix.push_back(line);
	}
	//now add your connections between DMi and RMj with add_rule(i,j)
	add_rule(1,1);
	add_rule(2,2);
	add_rule(3,2);
	add_rule(5,6);
	add_rule(5,3);
	add_rule(6,7);
	add_rule(7,2);
	add_rule(7,5);
}

bool FTM_Manager::run()
{

	ros::Rate loop_rate(10);
	while (nh_.ok())
	{
		cout<<"debut matrice"<<endl;
		for (int i=0;i<=NB_DM;i++)
		{
			for (int j=0;j<=NB_RM;j++)
			{
				cout<<rules_matrix[i][j];
			}
			cout<<endl;
		}
		cout<<endl;
		cout<<endl;


		FTM_Tree.showDMActivated();


		DM_Dominant=FTM_Tree.findDMDominant();

		cout << "DM Dominant : ";
		for (int i=0; i<DM_Dominant.size(); i++)
		{
				cout<<DM_Dominant[i]<<" ";
		}
		cout<<endl;
		cout<<endl;

		apply_rules();

		FTM_Tree.showRMActivated();

		RM_Dominant=FTM_Tree.findRMDominant();


		cout << "RM Dominant : ";
		for (int i=0; i<RM_Dominant.size(); i++)
		{
				cout<<RM_Dominant[i]<<" ";
		}
		cout<<endl;
		cout<<endl;

		RM_To_Shutdown=FTM_Tree.getRMToShutdown();

		cout << "RM To Shutdown : ";
		for (int i=0; i<RM_To_Shutdown.size(); i++)
		{
				cout<<RM_To_Shutdown[i]<<" ";
		}
		cout<<endl;
		cout<<endl;
		/*RM_To_Activate=compatibility();

		cout << "RM To activate (after compatibility) : ";
		for (int i=0; i<RM_To_Activate.size(); i++)
		{
				cout<<RM_To_Activate[i]<<" ";
		}
		cout<<endl;
*/
		ros::spinOnce();
		loop_rate.sleep();
	}

	return true;
}

/*vector<int> FTM_Manager::compatibility()
{
		//add you incompatibilities here
		//Dominance is already handle by the tree
		//be aware that order matters
/*
		vector<int>::iterator pos1=search_in_RM_Dominant(id1);
		vector<int>::iterator pos2=search_in_RM_Dominant(id2);

		if (pos1!=RM_Dominant.end()&&pos2!=RM_Dominant.end())
		{
			RM_Dominant.erase(pos1);
			RM_Dominant.erase(search_in_RM_Dominant(id2));
			RM_Dominant.push_back(id3);
		}
	*/
//}

vector<int>::iterator FTM_Manager::search_in_RM_Dominant(int id)
{
	return find(RM_Dominant.begin(), RM_Dominant.end(),id);
}

void FTM_Manager::apply_rules()
{
	int current_id_Dominant=0;
	for (int i=0;i<DM_Dominant.size();i++)
	{
		current_id_Dominant=DM_Dominant[i];

		int line_nb=1;
		while (rules_matrix[line_nb][0]!=current_id_Dominant)
			{
				line_nb++;
			}

		for (int column_nb=1;column_nb<rules_matrix[0].size();column_nb++)
		{
			if (rules_matrix[line_nb][column_nb]==1)
			{
				FTM_Tree.push_RM(rules_matrix[0][column_nb]);
			}
		}
	}
}

void FTM_Manager::add_rule(int i,int j)
{
	int line_nb=1;
	while (rules_matrix[line_nb][0]!=i)
		line_nb++;

	int column_nb=1;
	while (rules_matrix[0][column_nb]!=j)
		column_nb++;

	rules_matrix[line_nb][column_nb]=1;
}


void FTM_Manager::DM1_Callback(const std_msgs::Bool &detected)
{
	if (detected.data)
		FTM_Tree.push_DM(1);
}

void FTM_Manager::DM2_Callback(const std_msgs::Bool &detected)
{
	if (detected.data)
		FTM_Tree.push_DM(2);
}

void FTM_Manager::DM3_Callback(const std_msgs::Bool &detected)
{
	if (detected.data)
		FTM_Tree.push_DM(3);
}

void FTM_Manager::DM5_Callback(const std_msgs::Bool &detected)
{
	if (detected.data)
		FTM_Tree.push_DM(5);
}


int main(int argc, char** argv)
{
	//init the ROS node
	ros::init(argc, argv, "FTM_Manager_node");

	FTM_Manager myManager;
	myManager.run();
}
