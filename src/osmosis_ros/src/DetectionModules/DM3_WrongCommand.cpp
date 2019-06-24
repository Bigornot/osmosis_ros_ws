#include <osmosis_control/DetectionModules/DM3_WrongCommand.hpp>

//! ROS node topics publishing and subscribing initialization
DM3_WrongCommand::DM3_WrongCommand()
{
	cmd_sub_  = nh_.subscribe("summit_xl_a/robotnik_base_control/cmd_vel", 1, &DM3_WrongCommand::DM3_WrongCommandCallback, this);
	DM3_pub_ = nh_.advertise<std_msgs::Bool>("DM3_WrongCommand", 10);
	cmd_linear_x_max_=0;
	cmd_angular_z_max_=0;
}

//compute detection out of zone
bool DM3_WrongCommand::detect()
{
	if (cmd_.linear.x > cmd_linear_x_max_ || cmd_.angular.z > cmd_angular_z_max_ || -cmd_.linear.x < -cmd_linear_x_max_ || -cmd_.angular.z < -cmd_angular_z_max_)
	{
		std::cout << "Wrong command for the robot !!" << '\n';
		return true;
	}
	else
		return false;
}

//Topic callback
void DM3_WrongCommand::DM3_WrongCommandCallback(const geometry_msgs::Twist & cmd_msg)
{
	cmd_ = cmd_msg;
}

void DM3_WrongCommand::pub_to_FTM(std_msgs::Bool donnee)
{
	bool b = donnee.data;
	DM3_pub_.publish(donnee);
	std::cout << "Publication of DM3 : WrongCommand : ";
	std::cout << debug_msg <<" ";
	std::cout << std::boolalpha << b << std::endl;
}

int main(int argc, char** argv)
{
	//init the ROS node
	ros::init(argc, argv, "DM3_WrongCommand_node");
	DetectionModule* myDM3_WrongCommand=new DM3_WrongCommand();
	myDM3_WrongCommand->run();
}
