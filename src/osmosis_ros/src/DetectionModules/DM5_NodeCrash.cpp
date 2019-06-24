#include <osmosis_control/DetectionModules/DM5_NodeCrash.hpp>

//! ROS node topics publishing and subscribing initialization
DM5_NodeCrash::DM5_NodeCrash() : DetectionModule()
{
	DM5_pub_ = nh_.advertise<std_msgs::Bool>("DM5_NodeCrash", 10);

	nodesToCheck_.push_back("/DM1_ProhibitedArea_node");
	nodesToCheck_.push_back("/DM2_CmdNotUpdated_node");
	nodesToCheck_.push_back("/DM3_WrongCommand_node");
	nodesToCheck_.push_back("/HMI_node");
	nodesToCheck_.push_back("/teleop_node");
	nodesToCheck_.push_back("/emergency_shutdown_node");
	nodesToCheck_.push_back("/graph_planner_node");
	nodesToCheck_.push_back("/joy_node");
	nodesToCheck_.push_back("/joy_teleop_node");
	nodesToCheck_.push_back("/localization_node");
	nodesToCheck_.push_back("/mission_manager_node");
	nodesToCheck_.push_back("/osmosis_control_node");
	nodesToCheck_.push_back("/safety_pilot_node");
	nodesToCheck_.push_back("/teleop_node");
}

//compute detection out of zone
bool DM5_NodeCrash::detect()
{
	int i=0, j=0;
	bool found=true;

	ros::master::getNodes(aliveNodes_);	

	for(i=0; i<nodesToCheck_.size() && found; i++)
	{
		found = false;
		for(j=0; j<aliveNodes_.size() && !found; j++)
		{
			if(aliveNodes_[j]==nodesToCheck_[i])
				found = true;
		}
	}
	aliveNodes_.clear();

	if(!found)
	{
		return true;
	}
	else
		return false;
}

void DM5_NodeCrash::pub_to_FTM(std_msgs::Bool donnee)
{
	bool b = donnee.data;
	DM5_pub_.publish(donnee);
	std::cout << "Publication of DM5 : NodeCrash : ";
	std::cout << debug_msg <<" ";
	std::cout << std::boolalpha << b << std::endl;
}

int main(int argc, char** argv)
{
	//init the ROS node
	ros::init(argc, argv, "DM5_NodeCrash_node");
	DM5_NodeCrash myDM5_NodeCrash;

	ros::Duration(1).sleep();

	myDM5_NodeCrash.run();
}
