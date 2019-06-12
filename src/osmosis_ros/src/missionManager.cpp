//juil2018 J.Guiochet @ LAAS
#include <osmosis_control/missionManager.hpp>

void MissionManager::driveMissionManager()
{
	switch (state_)
	{
		case IDLE:
			char mode;
			mode=askMode();
			if(mode=='K'||mode=='k')
				state_=TARGETPOINT;
			else if(mode=='M'||mode=='m')
				state_=MISSION;
			else
				ROS_ERROR("Input Error : Please try again.\n");
			break;

		case TARGETPOINT:
			goalKeyboard();
			state_=IDLE;
			break;

		case MISSION:
			switch (missionState_)
			{
				case WAITMISSION:
					if(askMission())
						missionState_=EXECUTEMISSION;
					else
					{
						ROS_ERROR("Mission Aborted");
						state_=IDLE;
					}
				break;

				case EXECUTEMISSION:
					this->doMission();
					if(missionAborted_)
					{
						std::cout<<"Mission aborted !" << std::endl;
						missionAborted=false;
						missionState_=WAITMISSION;
						state_=IDLE;
					}

					else if(missionOver_)
					{
						std::cout<<"Mission done !" << std::endl;
						missionState_=WAITMISSION;
						state_=IDLE;
					}
					break;
			}
			break;
        }
  }

void MissionManager::doMission()
{
	if(ros::Time::now()-timeStartMission_>timeout_)
	{
		missionAborted_=true;
		missionOver_=true;
	}

	else if(goal_reached_)
	{
		mission_.step++;
		if(this->isMissionOver())
		{
			missionOver_=true;
		}
		else
			this->sendNextOrder();
	}
}

bool MissionManager::isMissionOver()
{
	bool over=false;;

	if(mission_.step==mission_.orders.size())
		over=true;

	return over;
}

void MissionManager::sendNextOrder()
{
	pub_on_=true;
	goal_reached_=false;
	state_and_point_cmd_=mission_.orders[mission_.step];
}

char MissionManager::askMode()
{
	char mode;
	std::string input;

	std::cout << std::endl << "Enter the mode : ('K':keyboard 'M':mission)" << std::endl;
	std::cin >> input;
	mode=input[0];

	return mode;
}

bool MissionManager::askMission()
{
	bool ok=false;

	std::string name;
	std::cout << "Enter the mission : " << std::endl;
	std::cin >> name;

	if(initMission(name))
	{
		ok=true;
		timeStartMission_=ros::Time::now();
		missionOver_=false;
		pub_on_=true;
		mission_.step=0;
		state_and_point_cmd_=mission_.orders[mission_.step];
	}

	return ok;
}

//! ROS node initialization
MissionManager::MissionManager()
{
	//set up the publisher for the goal topic
	goal_pub_ = nh_.advertise<osmosis_control::State_and_PointMsg>("goal", 1);
	hmi_done_pub_ = nh_.advertise<osmosis_control::Hmi_DoneMsg>("hmi_done", 1);
	goal_reached_sub_ = nh_.subscribe("/goal_reached", 1, &MissionManager::MissionManagerCallbackGoalReached, this);
	emergency_sub_ = nh_.subscribe("/emergency_shutdown", 1, &MissionManager::MissionManagerCallbackEmergencyHit, this);
	hmi_order_sub_ = nh_.subscribe("/hmi_order", 1, &MissionManager::MissionManagerCallbackOrder, this);

	goal_reached_=false;
	pub_on_=false;
	state_=IDLE;
	missionState_=WAITMISSION;
	state_and_point_cmd_.taxi=true;
	missionAborted_=false;
	missionOver_=true;
	hmi_point_=false;
	hmi_mission_=false;
	timeStartMission_=ros::Time::now();
	timeout_=ros::Duration(30*60); // Timeout after the mission is stopped
}


void MissionManager::MissionManagerCallbackGoalReached(const std_msgs::Bool &goal_reached)
{
	goal_reached_=goal_reached.data;
}

void MissionManager::MissionManagerCallbackEmergencyHit(const std_msgs::Bool &emergency_hit)
{
	missionAborted_=emergency_hit.data;
	missionOver_=emergency_hit.data;
}

void MissionManager::MissionManagerCallbackOrder(const osmosis_control::Hmi_OrderMsg)
{
	
}

void MissionManager::goalKeyboard()
{
	geometry_msgs::Point thegoal;
	std::cout << "Enter a new goal (x,y)\nx= ";
	std::cin >> thegoal.x;

	std::cout << "y= ";
	std::cin >> thegoal.y;
	state_=TARGETPOINT;

	pub_on_=true;
	state_and_point_cmd_.goal=thegoal;
}

bool MissionManager::initMission(std::string name)
{
	bool ok=false;
	goal_reached_=false;

	std::cout << "Init mission" << std::endl;

	std::string filename=ros::package::getPath("osmosis_control");
	filename.append("/MISSION_" + name + ".miss");

	std::ifstream fichier(filename, std::ios::in);

	if(fichier)
	{

		int i;
		int taille=mission_.orders.size();
		for(i=0;i<taille;i++)
			mission_.orders.pop_back();

		std::string line;

		while(getline(fichier, line))
			parse(line);

		for(i=0; i<mission_.orders.size();i++)
		{
			std::cout<<"x:"<<mission_.orders[i].goal.x << " y:" << mission_.orders[i].goal.y;
			if(mission_.orders[i].taxi)
				std::cout << " taxi=true" << std::endl;
			else
				std::cout << " taxi=false" << std::endl;
		}

		ok=true;
		fichier.close();
	}

	else
		ROS_ERROR("Mission Not Found !\n");

	return ok;
}

void MissionManager::parse(std::string line)
{
	osmosis_control::State_and_PointMsg order;

	if(line.size()>=14)
	{
		int coma=line.find(',');
		if(coma>=0)
		{
			int coma2=line.find(',', coma+1);
			if(coma2>=0)
			{
				order.goal.x=stof(line.substr(2, coma-2));
				order.goal.y=stof(line.substr(coma+3, coma2-coma-3));
				order.taxi=stoi(line.substr(coma2+6,1))!=0;

				mission_.orders.push_back(order);
			}
		}
	}
}

bool MissionManager::is_goal_reached()
{
	return goal_reached_;
}

void MissionManager::run()
{
	ros::Rate loop_rate(10); //using 10 makes the robot oscillating trajectories, TBD check with the PF algo ?
	while (nh_.ok())
	    {
		this->driveMissionManager();
		if(pub_on_)
		{
			goal_pub_.publish(state_and_point_cmd_);
			pub_on_=false;
		}
	 	ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
		loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate
	    }
}

int main(int argc, char** argv)
{
	//init the ROS node
	ros::init(argc, argv, "mission_manager_node");

	MissionManager myMManager;
	myMManager.run();
}
