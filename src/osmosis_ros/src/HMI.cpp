//juil2018 J.Guiochet @ LAAS
#include <osmosis_control/HMI.hpp>
// test

////////////////////// PRIVATE ////////////////////// 

void HMI::driveHMI()
{
	if(emergency_stop_)
		state_=EMERGENCY_STOP;

	switch (state_)
	{
		case IDLE:
			char mode;
			mode=askMode();
			if(mode=='P'||mode=='p')
				state_=POINT;
			else if(mode=='M'||mode=='m')
				state_=MISSION;
			else
				ROS_ERROR("Input Error : Please try again.\n");
			break;

		case POINT:
			switch (pointState_)
			{
				case TARGETPOINT:
					goalKeyboard();
					pointState_=WAITPOINT;
					break;

				case WAITPOINT:
					if (done_point_)
					{
						state_=IDLE;
						pointState_=TARGETPOINT;
					}
					break;
			}
			break;

		case MISSION:
			switch (missionState_)
			{
				case ASKMISSION:
					if(askMission())
						missionState_=WAITMISSION;
					else
					{
						ROS_ERROR("Mission Aborted");
						state_=IDLE;
					}
					break;

				case WAITMISSION:
					if(done_mission_)
					{
						std::cout<<"Mission done !" << std::endl;
						missionState_=ASKMISSION;
						state_=IDLE;
					}
					break;
			}
			break;

		case EMERGENCY_STOP:
			this->ordersDone();
			if(!emergency_stop_)
				state_=IDLE;
			break;

		default:
			break;
	}
}

void HMI::ordersDone()
{
	done_mission_=true;;
	done_point_=true;
}

char HMI::askMode()
{
	char mode;
	std::string input;

	std::cout << std::endl << "Enter the mode : ('P':Point 'M':mission)" << std::endl;
	std::cin >> input;
	mode=input[0];

	return mode;
}

void HMI::goalKeyboard()
{
	geometry_msgs::Point thegoal;
	osmosis_control::Hmi_OrderMsg order_cmd;
	osmosis_control::State_and_PointMsg state_and_point_cmd;
	int n=0;

	order_cmd.doMission=false;
	done_point_=false;
	
	std::cout << "Enter a new goal (x,y)" << std::endl;
	std::cout << "x= ";
	std::cin >> thegoal.x;
	std::cout << "y= ";
	std::cin >> thegoal.y;	
	std::cout << "taxi (0,1)= ";
	std::cin >> n;
	state_and_point_cmd.taxi = n!=0;

	state_and_point_cmd.goal=thegoal;
	order_cmd.state_and_point=state_and_point_cmd;
	orders_pub_.publish(order_cmd);
}

bool HMI::askMission()
{
	osmosis_control::Hmi_OrderMsg order_cmd;
	order_cmd.doMission=true;
	done_mission_=false;

	bool ok=false;

	std::string name;
	std::cout << "Enter the mission : " << std::endl;
	std::cin >> name;

	if(checkMission(name))
	{
		ok=true;
		done_mission_=false;
		order_cmd.mission_name=name;
		orders_pub_.publish(order_cmd);
	}
	return ok;
}

bool HMI::checkMission(std::string name)
{
	bool ok=false;
	goal_reached_=false;

	std::cout << "Mission in progress" << std::endl;

	std::string filename=ros::package::getPath("osmosis_control");
	filename.append("/MISSION_" + name + ".miss");

	std::ifstream fichier(filename, std::ios::in);

	if(fichier)
	{
		ok=true;
		fichier.close();
	}

	else
		ROS_ERROR("Mission Not Found !\n");

	return ok;
}


////////////////////// PUBLIC ////////////////////// 

HMI::HMI()
{
	freq_=10;
	orders_pub_ = nh_.advertise<osmosis_control::Hmi_OrderMsg>("order", 1);
	done_sub_ = nh_.subscribe("/hmi_done", 1, &HMI::CallbackOrderDone, this);
	emergency_stop_sub_ = nh_.subscribe("/do_RM1_EmergencyStop", 1, &HMI::CallbackEmergencyStop, this);
	state_=IDLE;
	pointState_=TARGETPOINT;
	missionState_=ASKMISSION;
	done_point_=true;
	done_mission_=true;
	emergency_stop_=false;
}

void HMI::run()
{
	ros::Rate loop_rate(freq_); //using 10 makes the robot oscillating trajectories, TBD check with the PF algo ?
	while (nh_.ok())
	{
		this->driveHMI();
	 	ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
		loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate
	}
}

void HMI::CallbackOrderDone(const osmosis_control::Hmi_DoneMsg &done)
{
	done_point_=done.point;
	done_mission_=done.mission;
}

void HMI::CallbackEmergencyStop(const std_msgs::Bool &stop)
{
	emergency_stop_=stop.data;
}

////////////////////// MAIN ////////////////////// 

int main(int argc, char** argv)
{
	//init the ROS node
	ros::init(argc, argv, "HMI_node");

	HMI myHMI;
	myHMI.run();
}
