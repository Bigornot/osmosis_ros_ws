#include <osmosis_control/FTM_Manager.hpp>

FTM_Manager::FTM_Manager()
{
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
	add_rule(1,3);
	add_rule(2,4);
	add_rule(6,5);
	add_rule(9,5);
	add_rule(7,6);

}

bool FTM_Manager::run()
{

	ros::Rate loop_rate(10);
	while (nh_.ok())
	{
		///
		cout<<"debut matrice"<<endl;
		for (int i=0;i<=NB_DM;i++)
		{
			for (int j=0;j<=NB_RM;j++)
			{
				cout<<rules_matrix[i][j];
			}
			cout<<endl;
		}

		cout<<"fin matrice"<<endl;
///
		ros::spinOnce();
		loop_rate.sleep();
	}
	return true;
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
		DM_activated.push_back(1);
}

void FTM_Manager::DM2_Callback(const std_msgs::Bool &detected)
{
	if (detected.data)
		DM_activated.push_back(2);
}

void FTM_Manager::DM3_Callback(const std_msgs::Bool &detected)
{
	if (detected.data)
		DM_activated.push_back(3);
}

void FTM_Manager::DM5_Callback(const std_msgs::Bool &detected)
{
	if (detected.data)
		DM_activated.push_back(5);
}


int main(int argc, char** argv)
{
	//init the ROS node
	ros::init(argc, argv, "FTM_Manager_node");

	FTM_Manager myManager;
	myManager.run();
}
