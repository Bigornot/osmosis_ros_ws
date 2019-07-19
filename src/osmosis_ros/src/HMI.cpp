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
					if (mission_done_)
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
					if(mission_done_)
					{
						ROS_INFO("Mission done !");
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
	osmosis_control::Hmi_OrderMsg order_cmd;
	osmosis_control::State_and_PointMsg state_and_point_cmd;
	int n=0;

	order_cmd.doMission=false;
	mission_done_=false;

	ROS_INFO("Enter a new goal (x,y)");
	ROS_INFO("x= ");
	cin >> thegoal.x;
	ROS_INFO("y= ");
	cin >> thegoal.y;
	ROS_INFO("taxi (0,1)= ");
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
	mission_done_=false;

	bool ok=false;

	string name;
	ROS_INFO("Enter the mission : ");
	cin >> name;

	if(checkMission(name))
	{
		ok=true;
		mission_done_=false;
		order_cmd.mission_name=name;
		orders_pub_.publish(order_cmd);
	}
	return ok;
}

bool HMI::checkMission(string name)
{
	bool ok=false;
	goal_reached_=false;

	ROS_INFO("Mission in progress");

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
