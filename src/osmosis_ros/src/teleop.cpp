#include <osmosis_control/teleop.hpp>


//compute drive commands based on keyboard input
void Teleop::FSMKeyboard()
{
	geometry_msgs::Twist base_cmd;
	char cmd[50];
	cin.getline(cmd, 50);

	switch (state_)
	{
		case DESACTIVATED:
			if(cmd[0]!='1' && cmd[0]!='+' && cmd[0]!='l' && cmd[0]!='r' && cmd[0]!='.')
			{
				cout << "unknown command:" << cmd << "\n";
				//continue;
			}
			else if (cmd[0]=='1')
			{
				state_=ACTIVATED;
				teleop_cmd_.is_active=true;
			}
			break;

		case ACTIVATED:
			//move forward
			if(cmd[0]=='+') base_cmd.linear.x = 0.25;

			//turn left (yaw) and drive forward at the same time
			else if(cmd[0]=='l')
			{
				base_cmd.angular.z = 0.75;
				base_cmd.linear.x = 0.25;
			}
			//turn right (yaw) and drive forward at the same time
			else if(cmd[0]=='r')
			{
				base_cmd.angular.z = -0.75;
				base_cmd.linear.x = 0.25;
			}
			//quit
			else if(cmd[0]=='.')
			{
				state_=DESACTIVATED;
				teleop_cmd_.is_active=false;
			}
			break;

		default: break;

	}
	teleop_cmd_.cmd_vel=base_cmd;
}


//! ROS node topics publishing and subscribing initialization
Teleop::Teleop()
{
	freq_=10;
	cmd_teleop_pub_ = nh_.advertise<osmosis_control::TeleopMsg>("/cmd_vel_teleop", 1);
	teleop_cmd_.is_active=false;
	teleop_cmd_.cmd_vel.linear.x=teleop_cmd_.cmd_vel.linear.y=teleop_cmd_.cmd_vel.angular.z=0;
	state_=DESACTIVATED;
}


void Teleop::run()
{
	cout << "Type a command and then press enter.  "
	"Use '1' to activate the telecommand then'+' to move forward, 'l' to turn left, "
	"'r' to turn right, '.' to exit.\n";

	ros::Rate loop_rate(freq_);
	while (nh_.ok())
	{
		cout <<".";
		KeyboardFSM();
		cmd_teleop_pub_.publish(teleop_cmd_);
		loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate
	}
}


int main(int argc, char** argv)
{
	//init the ROS node
	ros::init(argc, argv, "teleop_node");

	Teleop myTeleop;
	myTeleop.run();
}
