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
				state_=REACH_POINT_MISSION;
			else if(mode=='M'||mode=='m')
				state_=RUNWAY_MISSION;
			else
				ROS_ERROR("Input Error : Please try again.\n");
			break;

		case REACH_POINT_MISSION:
			switch (pointState_)
			{
				case ASK_MISSION:
					goalKeyboard();
					publishOrder();
					pointState_=WAIT_END_MISSION;
					break;

				case WAIT_END_MISSION:
					if (mission_done_)
					{
						state_=IDLE;
						pointState_=ASK_MISSION;
					}
					break;
			}
			break;

		case RUNWAY_MISSION:
			switch (missionState_)
			{
				case ASK_MISSION:
					if(askMission())
					{
						publishOrder();
						missionState_=WAIT_END_MISSION;
					}
					else
					{
						ROS_ERROR("Mission Aborted");
						state_=IDLE;
					}
					break;

				case WAIT_END_MISSION:
					if(mission_done_)
					{
						ROS_INFO("Mission done !");
						missionState_=ASK_MISSION;
						state_=IDLE;
					}
					break;
			}
			break;

		default: break;
	}
}

void HMI::ordersDone()
{
	mission_done_=true;
}

char HMI::askMode()
{
	char mode;
	string input;

	ROS_INFO("Enter the mode : ('P':Point 'M':mission)");
	cin >> input;
	mode=input[0];

	return mode;
}

void HMI::goalKeyboard()
{
	geometry_msgs::Point thegoal;
	int n=0;

	mission_cmd_.doRunwayMission=false;
	mission_done_=false;

	ROS_INFO("Enter a new goal (x,y)");
	ROS_INFO("x= ");
	cin >> thegoal.x;
	ROS_INFO("y= ");
	cin >> thegoal.y;
	ROS_INFO("taxi (0,1)= ");
	cin >> n;

	mission_cmd_.mission_goal.taxi = n!=0;
	mission_cmd_.mission_goal.point = thegoal;
}

void HMI::publishOrder()
{
	orders_pub_.publish(mission_cmd_);
}

bool HMI::askMission()
{
	mission_cmd_.doRunwayMission=true;
	mission_done_=false;

	bool ok=false;

	string name;
	ROS_INFO("Enter the mission : ");
	cin >> name;

	if(checkMission(name))
	{
		ok=true;
		mission_done_=false;
		mission_cmd_.mission_name=name;
	}
	return ok;
}

bool HMI::checkMission(string name)
{
	bool ok=false;
	goal_reached_=false;

	ROS_INFO("Mission in progress");

	string filename=ros::package::getPath("osmosis_control");
	filename.append("/../../ressources/missions/MISSION_" + name + ".miss");

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
	orders_pub_ = nh_.advertise<osmosis_control::MissionMsg>("order", 1);
	done_sub_ = nh_.subscribe("/hmi_done", 1, &HMI::CallbackOrderDone, this);
	state_=IDLE;
	pointState_=ASK_MISSION;
	missionState_=ASK_MISSION;
	mission_done_=true;
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

void HMI::CallbackOrderDone(const std_msgs::Bool &mission_done)
{
	mission_done_=mission_done.data;
}

////////////////////// MAIN //////////////////////
int main(int argc, char** argv)
{
	//init the ROS node
	ros::init(argc, argv, "HMI_node");

	HMI myHMI;
	myHMI.run();
}
