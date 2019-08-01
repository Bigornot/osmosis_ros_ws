#include <detectionModules/DM3_WrongCommand.hpp>


////////////////////// PRIVATE //////////////////////

void DM3_WrongCommand::detect()
{
	if (cmd_.linear.x > cmd_linear_x_max_ || cmd_.angular.z > cmd_angular_z_max_ || cmd_.linear.x < cmd_linear_x_min_ || cmd_.angular.z < cmd_angular_z_min_)
		state_=true;
	else
		state_=false;
}

////////////////////// PUBLIC //////////////////////

DM3_WrongCommand::DM3_WrongCommand()
{
	cmd_sub_  = nh_.subscribe("summit_xl_a/robotnik_base_control/cmd_vel", 1, &DM3_WrongCommand::DM3_WrongCommandCallback, this);
	cmd_linear_x_max_=max_linear;
	cmd_linear_x_min_=-max_linear;
	cmd_angular_z_max_=max_angular;
	cmd_angular_z_min_=-max_angular;
}

void DM3_WrongCommand::init()
{
}


void DM3_WrongCommand::DM3_WrongCommandCallback(const geometry_msgs::Twist & cmd_msg)
{
	cmd_ = cmd_msg;
}
