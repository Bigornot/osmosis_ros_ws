#include <osmosis_control/joy_teleop.hpp>

//compute drive commands based on keyboard input
  void Joy_teleop::driveJoy()
  {

    char cmd[50];
    cmd[0]='1';
    //std::cin.getline(cmd, 50);

    switch (state_)
	{
	 	case DESACTIVATED:
			if(cmd[0]!='1' && cmd[0]!='.')
      			{
        		std::cout << "unknown command:" << cmd << "\n";
        		//continue;
      			}
			else if (cmd[0]=='1')
				{
				state_=ACTIVATED;
				joy_teleop_cmd_.is_active=true;
				std::cout << "Activation de la manette" << std::endl;
				}
			break;
		case ACTIVATED:
		        //quit
		        if(cmd[0]=='.'){
			        state_=DESACTIVATED;
			        joy_teleop_cmd_.is_active=false;
				std::cout << "Desactivation de la manette" << std::endl;
		        }
			break;
		default: break;

	}
  }

void Joy_teleop::teleopCallbackJoy(const sensor_msgs::Joy & joy_msg)
  {
        this->joy_msg_=joy_msg;
	geometry_msgs::Twist base_cmd;
	float axe1, axe2;
	int button1;
	int button2;

	axe1=this->joy_msg_.axes[1];
	axe2=this->joy_msg_.axes[3];

	button1=this->joy_msg_.buttons[0];
	button2=this->joy_msg_.buttons[1];

	base_cmd.linear.x=3*axe1*(1+button1);
	base_cmd.linear.z=1000*button2;
	base_cmd.angular.z=7*axe2;

	joy_teleop_cmd_.cmd_vel.linear.x=base_cmd.linear.x;
	joy_teleop_cmd_.cmd_vel.angular.z=base_cmd.angular.z;
  }


//! ROS node topics publishing and subscribing initialization
Joy_teleop::Joy_teleop()
	  {
	    cmd_joy_teleop_pub_ = nh_.advertise<osmosis_control::TeleopMsg>("/cmd_vel_teleop", 1);
	    cmd_joystick_sub_= nh_.subscribe("/joy", 1, &Joy_teleop::teleopCallbackJoy, this);

	    joy_teleop_cmd_.is_active=false;
	    joy_teleop_cmd_.cmd_vel.linear.x=joy_teleop_cmd_.cmd_vel.linear.y=joy_teleop_cmd_.cmd_vel.angular.z=0;
   	    state_=DESACTIVATED;
	  }


void Joy_teleop::run()
  {
	std::cout << "Si tout se passe bien on peut desormais activer la manette\n";

	ros::Rate loop_rate(10);
	while (nh_.ok())
	    {
		std::cout <<".";
		this->driveJoy();
		cmd_joy_teleop_pub_.publish(joy_teleop_cmd_);
	 	ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
		loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate

	    }
   }


int main(int argc, char** argv)
{
  /init the ROS node
  ros::init(argc, argv, "joy_teleop_node");

  Joy_teleop myJoyTeleop;
  myJoyTeleop.run();
}
