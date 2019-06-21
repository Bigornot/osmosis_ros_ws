#include <osmosis_control/DM1_ProhibitedArea.hpp>
#include <osmosis_control/DetectionModule.hpp>


//! ROS node topics publishing and subscribing initialization
DM1_ProhibitedArea::DM1_ProhibitedArea()
{
	position_sub_  = nh_.subscribe("pose", 1, &DM1_ProhibitedArea::DM1_ProhibitedAreaCallback, this);
	DM1_pub_ = nh_.advertise<std_msgs::Bool>("DM1_ProhibitedArea", 10);
	x_min = -10;
	x_max = 10;
	y_min = -15;
	y_max = 15;
}

//compute detection out of zone
bool DM1_ProhibitedArea::detect()
{
	if (robot_pose_.x < x_min || x_max < robot_pose_.x || robot_pose_.y < y_min || y_max < robot_pose_.y)
	{
		std::cout << "The robot is in a prohibited area." << '\n';
		return true;
	}
	else
		return false;
}

//Topic callback
void DM1_ProhibitedArea::DM1_ProhibitedAreaCallback(const geometry_msgs::Pose2D & position_msg)
{
	robot_pose_ = position_msg;
}


void DM1_ProhibitedArea::pub_to_FTM(std_msgs::Bool donnee)
{
	DM1_pub_.publish(donnee);
	std::cout << "Publication de DM1 : ProhibitedArea" << '\n';
}

int main(int argc, char** argv)
{
	//init the ROS node
	ros::init(argc, argv, "DM1_ProhibitedArea_node");
	
	DetectionModule myDM1_ProhibitedArea;
	myDM1_ProhibitedArea.run();
}
