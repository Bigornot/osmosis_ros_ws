//juil2018 J.Guiochet @ LAAS
#include <osmosis_control/missionManager.hpp>

////////////////////// PRIVATE //////////////////////

void MissionManager::driveMissionManager()
{
	if(emergency_stop_)
	{
		abortMission();
		state_=EMERGENCY_STOP;
	}

	switch (state_)
	{
		case IDLE:
			ROS_INFO("IDLE\n");
			if(hmi_mission_)
			{
				resetIdle();
				state_=MISSION;
			}
			else if(hmi_point_)
			{
				resetIdle();
				state_=POINT;
			}
			break;

		case POINT:
			switch (pointState_)
			{
				case TARGETPOINT:
					ROS_INFO("POINT TARGETPOINT\n");
					goalKeyboard();
					pointState_=WAITPOINT;
					break;

				case WAITPOINT:
					ROS_INFO("POINT WAITPOINT\n");
					if(goal_reached_)
					{
						endPoint();
						pointState_=TARGETPOINT;
						state_=IDLE;
					}
					break;
			}
			break;


		case MISSION:
			switch (missionState_)
			{
				case INITMISSION:
					ROS_INFO("MISSION INITMISSION\n");
					initMission(mission_name_);
					missionState_=EXECUTEMISSION;
					break;

				case EXECUTEMISSION:
					ROS_INFO("MISSION EXECUTEMISSION\n");
					doMission();
					if(missionAborted_)
					{
						abortMission();
						missionState_=INITMISSION;
						state_=IDLE;
					}

					else if(missionOver_)
					{
						endMission();
						missionState_=INITMISSION;
						state_=IDLE;
					}
					break;
			}
			break;

		case EMERGENCY_STOP:
			ROS_INFO("EMERGENCY_STOP\n");
			if(!emergency_stop_)
			{
				missionState_=INITMISSION;
				pointState_=WAITPOINT;
				state_=IDLE;
			}
			break;

		default:
			ROS_INFO("defaut\n");
			break;

        }
}

void MissionManager::resetIdle()
{
	hmi_mission_=false;
	hmi_point_=false;
}

bool MissionManager::isGoalReached()
{
	return goal_reached_;
}

void MissionManager::goalKeyboard()
{
	goal_reached_=false;
	cout<<"x= " << state_and_point_cmd_.goal.x << " y= " << state_and_point_cmd_.goal.y << " taxi=";
	if(state_and_point_cmd_.taxi)
		cout << "true" << endl;
	else
		cout << "false" << endl;

	goal_pub_.publish(state_and_point_cmd_);
}

void MissionManager::endPoint()
{
	osmosis_control::Hmi_DoneMsg done;
	done.mission=false;
	done.point=true;
	hmi_done_pub_.publish(done);
}

void MissionManager::initMission(string name)
{
	goal_reached_=false;
	missionAborted_=false;
	missionOver_=false;

	cout << "Init mission" << endl;

	int i;
	int taille=mission_.mission_steps.size();
	for(i=0;i<taille;i++)
		mission_.mission_steps.pop_back();

	string filename=ros::package::getPath("osmosis_control");
	filename.append("/Missions/MISSION_" + name + ".miss");

	ifstream fichier(filename, ios::in);
	string line;

	while(getline(fichier, line))
		parse(line);
	fichier.close();

	for(i=0; i<mission_.mission_steps.size();i++)
	{
		cout<<"x:"<<mission_.mission_steps[i].goal.x << " y:" << mission_.mission_steps[i].goal.y;
		if(mission_.mission_steps[i].taxi)
			cout << " taxi=true" << endl;
		else
			cout << " taxi=false" << endl;
	}

	timeStartMission_=ros::Time::now();

	missionOver_=false;
	mission_.step=0;
	state_and_point_cmd_=mission_.mission_steps[mission_.step];
	goal_pub_.publish(state_and_point_cmd_);
}

void MissionManager::parse(string line)
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

				mission_.mission_steps.push_back(order);
			}
		}
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
		if(isMissionOver())
		{
			missionOver_=true;
		}
		else
			sendNextOrder();
	}
}

bool MissionManager::isMissionOver()
{
	bool over=false;;

	if(mission_.step==mission_.mission_steps.size())
		over=true;

	return over;
}

void MissionManager::sendNextOrder()
{
	goal_reached_=false;
	state_and_point_cmd_=mission_.mission_steps[mission_.step];
	goal_pub_.publish(state_and_point_cmd_);
}

void MissionManager::abortMission()
{
	missionAborted_=false;
	missionOver_=true;

	osmosis_control::Hmi_DoneMsg done;
	done.mission=true;
	done.point=false;
	hmi_done_pub_.publish(done);
}

void MissionManager::endMission()
{
	osmosis_control::Hmi_DoneMsg done;
	done.mission=true;
	done.point=false;
	hmi_done_pub_.publish(done);
}


////////////////////// PUBLIC  //////////////////////

//! ROS node initialization
MissionManager::MissionManager()
{
	//set up the publisher for the goal topic
	goal_pub_ = nh_.advertise<osmosis_control::State_and_PointMsg>("goal", 1);
	hmi_done_pub_ = nh_.advertise<osmosis_control::Hmi_DoneMsg>("hmi_done", 1);
	goal_reached_sub_ = nh_.subscribe("/goal_reached", 1, &MissionManager::CallbackGoalReached, this);
	emergency_stop_sub_ = nh_.subscribe("/do_RM1_EmergencyStop", 1, &MissionManager::CallbackEmergencyStop, this);
	hmi_order_sub_ = nh_.subscribe("/order", 1, &MissionManager::CallbackOrder, this);

	emergency_stop_=false;
	goal_reached_=false;
	state_=IDLE;
	missionState_=INITMISSION;
	pointState_=TARGETPOINT;
	state_and_point_cmd_.taxi=true;
	missionAborted_=false;
	missionOver_=true;
	hmi_point_=false;
	hmi_mission_=false;
	timeStartMission_=ros::Time::now();
	timeout_=ros::Duration(30*60); // Timeout after the mission is aborted
}

void MissionManager::run()
{
	ros::Rate loop_rate(10); //using 10 makes the robot oscillating trajectories, TBD check with the PF algo ?
	while (nh_.ok())
	    {
		driveMissionManager();
	 	ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
		loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate
	    }
}

void MissionManager::CallbackGoalReached(const std_msgs::Bool &goal_reached)
{
	goal_reached_=goal_reached.data;
}

void MissionManager::CallbackEmergencyStop(const std_msgs::Bool &stop)
{
	missionAborted_=true;
	missionOver_=true;
	emergency_stop_=stop.data;
}

void MissionManager::CallbackOrder(const osmosis_control::Hmi_OrderMsg &order)
{
	if(order.doMission)
	{
		ROS_INFO("\nMISSION\n");

		hmi_mission_=true;
		hmi_point_=false;
		mission_name_=order.mission_name;
	}

	else
	{
		ROS_INFO("\nPOINT\n");

		hmi_mission_=false;
		hmi_point_=true;
		state_and_point_cmd_=order.state_and_point;
	}
}


////////////////////// MAIN  //////////////////////

int main(int argc, char** argv)
{
	//init the ROS node
	ros::init(argc, argv, "mission_manager_node");

	MissionManager myMManager;
	myMManager.run();
}
