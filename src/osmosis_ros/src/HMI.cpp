//juil2018 J.Guiochet @ LAAS
#include <osmosis_control/HMI.hpp>

////////////////////// PRIVATE //////////////////////

void HMI::HMI_FSM()
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
				case ASKPOINT:
					goalKeyboard();
					pointState_=WAITPOINT;
					break;

				case WAITPOINT:
					if (done_point_)
					{
						state_=IDLE;
						pointState_=ASKPOINT;
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
						cout<<"Mission done !" << endl;
						missionState_=ASKMISSION;
						state_=IDLE;
					}
					break;
			}
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
	string input;

	cout << endl << "Enter the mode : ('P':Point 'M':mission)" << endl;
	cin >> input;
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

	cout << "Enter a new goal (x,y)" << endl;
	cout << "x= ";
	cin >> thegoal.x;
	cout << "y= ";
	cin >> thegoal.y;
	cout << "taxi (0,1)= ";
	cin >> n;
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

	string name;
	cout << "Enter the mission : " << endl;
	cin >> name;

	if(checkMission(name))
	{
		ok=true;
		done_mission_=false;
		order_cmd.mission_name=name;
		orders_pub_.publish(order_cmd);
	}
	return ok;
}

bool HMI::checkMission(string name)
{
	bool ok=false;
	goal_reached_=false;

	cout << "Mission in progress" << endl;

	string filename=ros::package::getPath("osmosis_control");
	filename.append("/Missions/MISSION_" + name + ".miss");

	ifstream fichier(filename, ios::in);

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
	state_=IDLE;
	pointState_=ASKPOINT;
	missionState_=ASKMISSION;
	done_point_=true;
	done_mission_=true;
}

void HMI::run()
{
	ros::Rate loop_rate(freq_); //using 10 makes the robot oscillating trajectories, TBD check with the PF algo ?
	while (nh_.ok())
	{
		HMI_FSM();
	 	ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
		loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate
	}
}

void HMI::CallbackOrderDone(const osmosis_control::Hmi_DoneMsg &done)
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
