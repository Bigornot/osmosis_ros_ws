//juil2018 J.Guiochet @ LAAS
#include <osmosis_control/HMI.hpp>
// test

////////////////////// PRIVATE //////////////////////

void HMI::driveHMI()
{
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
	}
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
	orders_cmd_.doMission=false;
	this->resetDone();

	geometry_msgs::Point thegoal;
	int n=0;
	std::cout << "Enter a new goal (x,y)" << std::endl;
	std::cout << "x= ";
	std::cin >> thegoal.x;
	std::cout << "y= ";
	std::cin >> thegoal.y;
	std::cout << "taxi (0,1)= ";
	std::cin >> n;
	state_and_point_cmd_.taxi = n!=0;

	state_and_point_cmd_.goal=thegoal;
	orders_cmd_.state_and_point=state_and_point_cmd_;
	orders_pub_.publish(orders_cmd_);
}

bool HMI::askMission()
{
	orders_cmd_.doMission=true;
	this->resetDone();

	bool ok=false;

	std::string name;
	std::cout << "Enter the mission : " << std::endl;
	std::cin >> name;

	if(checkMission(name))
	{
		ok=true;
		done_mission_=false;
		orders_cmd_.state_and_point=state_and_point_cmd_;
		orders_pub_.publish(orders_cmd_);
	}
	return ok;
}

bool HMI::checkMission(std::string name)
{
	bool ok=false;
	goal_reached_=false;
	orders_cmd_.mission_name=name;

	std::cout << "Mission ok" << std::endl;

	std::string filename=ros::package::getPath("osmosis_control");
	filename.append("/Missions/MISSION_" + name + ".miss");

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

void HMI::resetDone()
{
	done_point_=false;
	done_mission_=false;
}


////////////////////// PUBLIC //////////////////////

//! ROS node initialization
HMI::HMI()
{
	orders_pub_ = nh_.advertise<osmosis_control::Hmi_OrderMsg>("order", 1);
	done_sub_ = nh_.subscribe("/hmi_done", 1, &HMI::HMICallbackHmiOrder, this);
	state_=IDLE;
	pointState_=TARGETPOINT;
	missionState_=ASKMISSION;
	this->resetDone();
}

void HMI::run()
{
	ros::Rate loop_rate(10); //using 10 makes the robot oscillating trajectories, TBD check with the PF algo ?
	while (nh_.ok())
	{
		this->driveHMI();
	 	ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
		loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate
	}
}

void HMI::HMICallbackHmiOrder(const osmosis_control::Hmi_DoneMsg &done)
{
	done_point_=done.point;
	done_mission_=done.mission;
}


////////////////////// MAIN //////////////////////

int main(int argc, char** argv)
{
	//init the ROS node
	ros::init(argc, argv, "HMI_node");

	HMI myHMI;
	myHMI.run();
}
