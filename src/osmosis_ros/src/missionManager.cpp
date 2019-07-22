//juil2018 J.Guiochet @ LAAS
#include <osmosis_control/missionManager.hpp>

////////////////////// PRIVATE //////////////////////

void MissionManager::MissionManagerFSM()
{
	switch (state_)
	{
		case IDLE:
			ROS_INFO("IDLE\n");
			if(mission_received_)
			{
				mission_received_=false;
				if(mission_msg_.doRunwayMission)
					state_=RUNWAY_MISSION;
				else
					state_=REACH_POINT_MISSION;
			}
			break;

		case REACH_POINT_MISSION:
			switch (mission_state_)
			{
				case INIT_MISSION:
					ROS_INFO("REACH_POINT_MISSION INIT_MISSION\n");
					goalKeyboard();
					publishMissionGoal();
					mission_state_=EXECUTE_MISSION;
					break;

				case EXECUTE_MISSION:
					ROS_INFO("REACH_POINT_MISSION EXECUTE_MISSION\n");
					if(goal_reached_)
					{
						endPoint();
						publishDone();
						mission_state_=INIT_MISSION;
						state_=IDLE;
					}
					break;
			}
			break;


		case RUNWAY_MISSION:
			switch (mission_state_)
			{
				case INIT_MISSION:
					ROS_INFO("RUNWAY_MISSION INIT_MISSION\n");
					initMission(mission_msg_.mission_name);
					publishMissionGoal();
					mission_state_=EXECUTE_MISSION;
					break;

				case EXECUTE_MISSION:
					ROS_INFO("RUNWAY_MISSION EXECUTE_MISSION\n");
					doMission();
					if(checkNextStep())
						publishMissionGoal();

					if(missionAborted_)
					{
						abortMission();
						publishDone();
						mission_state_=INIT_MISSION;
						state_=IDLE;
					}

					else if(missionOver_)
					{
						endMission();
						publishDone();
						mission_state_=INIT_MISSION;
						state_=IDLE;
					}

					break;
			}
			break;

		default: break;
	}
}

bool MissionManager::isGoalReached()
{
	return goal_reached_;
}

void MissionManager::goalKeyboard()
{
	goal_reached_=false;

	goal_cmd_=mission_msg_.mission_goal;

	ROS_INFO("x= %f",goal_cmd_.point.x);
	ROS_INFO("y= %f",goal_cmd_.point.y);
	ROS_INFO("taxi= %d",goal_cmd_.taxi);
}

void MissionManager::publishMissionGoal()
{
	goal_pub_.publish(goal_cmd_);
}

void MissionManager::endPoint()
{
	done_.data=true;
}

void MissionManager::publishDone()
{
	hmi_done_pub_.publish(done_);
}

void MissionManager::initMission(string name)
{
	goal_reached_=false;
	missionAborted_=false;
	missionOver_=false;

	ROS_INFO("Init mission");

	int i;
	int taille=mission_.mission_steps.size();
	for(i=0;i<taille;i++)
		mission_.mission_steps.pop_back();

	string filename=ros::package::getPath("osmosis_control");
	filename.append("/../../ressources/missions/MISSION_" + name + ".miss");

	ifstream fichier(filename, ios::in);
	string line;

	while(getline(fichier, line))
		parse(line);
	fichier.close();

	for(i=0; i<mission_.mission_steps.size();i++)
	{
		ROS_INFO("x: %f",mission_.mission_steps[i].point.x);
		ROS_INFO("y: %f",mission_.mission_steps[i].point.y);
		ROS_INFO("taxi= %d",mission_.mission_steps[i].taxi);
	}

	time_start_mission_=ros::Time::now();

	missionOver_=false;
	mission_.step=0;
	goal_cmd_=mission_.mission_steps[mission_.step];
}

void MissionManager::parse(string line)
{
	osmosis_control::GoalMsg step;

	if(line.size()>=14)
	{
		int coma=line.find(',');
		if(coma>=0)
		{
			int coma2=line.find(',', coma+1);
			if(coma2>=0)
			{
				step.point.x=stof(line.substr(2, coma-2));
				step.point.y=stof(line.substr(coma+3, coma2-coma-3));
				step.taxi=stoi(line.substr(coma2+6,1))!=0;

				mission_.mission_steps.push_back(step);
			}
		}
	}
}

void MissionManager::doMission()
{
	if(ros::Time::now()-time_start_mission_>timeout_)
	{
		missionAborted_=true;
		missionOver_=true;
	}
}

bool MissionManager::checkNextStep()
{
	bool next=false;

	if(goal_reached_)
	{
		mission_.step++;
		if(isMissionOver())
		{
			missionOver_=true;
		}
		else
		{
			next=true;
			nextStep();
		}
	}

	return next;
}

bool MissionManager::isMissionOver()
{
	bool over=false;;

	if(mission_.step==mission_.mission_steps.size())
		over=true;

	return over;
}

void MissionManager::nextStep()
{
	goal_reached_=false;
	goal_cmd_=mission_.mission_steps[mission_.step];
}

void MissionManager::abortMission()
{
	missionAborted_=false;
	missionOver_=true;

	done_.data=false;
}

void MissionManager::endMission()
{
	done_.data=true;
}

////////////////////// PUBLIC  //////////////////////

//! ROS node initialization
MissionManager::MissionManager()
{
	//set up the publisher for the goal topic
	goal_pub_ = nh_.advertise<osmosis_control::GoalMsg>("mission_goal", 1);
	hmi_done_pub_ = nh_.advertise<std_msgs::Bool>("hmi_done", 1);
	goal_reached_sub_ = nh_.subscribe("/goal_reached", 1, &MissionManager::callbackGoalReached, this);
	hmi_mission_sub_ = nh_.subscribe("/mission", 1, &MissionManager::callbackMission, this);

	goal_reached_=false;
	state_=IDLE;
	mission_state_=INIT_MISSION;
	goal_cmd_.taxi=true;
	missionAborted_=false;
	missionOver_=true;
	mission_received_=false;
	time_start_mission_=ros::Time::now();
	timeout_=ros::Duration(30*60); // Timeout after the mission is aborted
}

void MissionManager::run()
{
	ros::Rate loop_rate(10); //using 10 makes the robot oscillating trajectories, TBD check with the PF algo ?
	while (nh_.ok())
	{
		MissionManagerFSM();
		ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
		loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate
	}
}

void MissionManager::callbackGoalReached(const std_msgs::Bool &goal_reached)
{
	goal_reached_=goal_reached.data;
}

void MissionManager::callbackMission(const osmosis_control::MissionMsg &mission)
{
	mission_received_=true;
	mission_msg_=mission;
}


////////////////////// MAIN  //////////////////////

int main(int argc, char** argv)
{
	//init the ROS node
	ros::init(argc, argv, "mission_manager_node");

	MissionManager myMManager;
	myMManager.run();
}
