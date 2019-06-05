//juil2018 J.Guiochet @ LAAS
#include <osmosis_control/missionManager.hpp>


void MissionManager::driveMissionManager()
{
	switch (state_)
	{
		case KEYBOARD:
		goalKeyboard();

		break;

		case MISSION:
			switch (missionState_)
			{
				case WAITMISSION:
					char mission_code;
					std::cout<<"Veuillez entrez le code de la mission a effectuer" <<std::endl;
					std::cout<<"Entrez 'C' pour repasser en mode clavier" <<std::endl;
					std::cin>>mission_code;
					if (mission_code=='C')
                                        { 	
						state_=KEYBOARD;
                                        }
					else
					{
						//initMission();
						mission_.step=0;
						missionState_=WAITORDERDONE;
					}      
					break;

				case WAITORDERDONE:
					this->goal_=mission_.orders[mission_.step];
					if (this->goal_reached_==true)
					{
						if (mission_.step==mission_.orders.size())
						{
							missionState_=WAITMISSION;
							std::cout<<"Mission accomplie !";
						}
					mission_.step++;
					}	
				break;
				
			}

		break;
        }
  }

//! ROS node initialization
MissionManager::MissionManager()
{
	//set up the publisher for the goal topic
	goal_pub_ = nh_.advertise<geometry_msgs::Point>("goal", 1);
	goal_reached_sub_ = nh_.subscribe("/goal_reached", 1, &MissionManager::MissionManagerCallbackGoalReached, this); 
	goal_reached_=false;
}


void MissionManager::MissionManagerCallbackGoalReached(const std_msgs::Bool &goal_reached)
{
	this->goal_reached_=goal_reached.data;
}

void MissionManager::goalKeyboard()
{
	char ans;
	geometry_msgs::Point thegoal;
        std::cout << "This mission manager is a simple goto position mission... "<<std::endl
                  <<"Mode Mission (M) ou mode Clavier (C) ?";
	std::cin >> ans;
	if (ans=='C')
	{
	std::cout << "Enter a new goal (x,y)\nx= ";
	std::cin >> thegoal.x;

	std::cout << "y= ";
	std::cin >> thegoal.y;
	state_=KEYBOARD;

	this->goal_=thegoal;
	}
	else
	{
		state_=MISSION;
	}

}

void MissionManager::initMission(std::string name)
{
	std::cout << "Init mission" << std::endl;

	std::string filename=ros::package::getPath("osmosis_control");
	filename.append("/MISSION_" + name + ".miss");
	
	std::ifstream fichier(filename, std::ios::in);

	if(fichier)
	{
		// Parsing
		int i=0;
		std::string line;

		while(getline(fichier, line))
			parse(line);

		fichier.close();
	}

	else
		ROS_ERROR("Mission Not Found !\n");
}

void MissionManager::parse(std::string line)
{
	geometry_msgs::Point point;
	std::string xs, ys;
	float x, y;
	
	std::cout << line << std::endl;

	int coma=line.find(',');
	if(coma>=0)		
	{
		std::cout << "coma" << coma << std::endl;
		xs=line.substr(2, coma-2);
		ys=line.substr(coma+3);

		x=stof(xs);
		y=stof(ys);
		
		point.x=x;
		point.y=y;

		std::cout << "x=" << x << " y=" << y << std::endl;

		mission_.orders.push_back(point);
	}
}

bool MissionManager::is_goal_reached()
{
	return this->goal_reached_;
}

void MissionManager::run()
{
	ros::Rate loop_rate(10); //using 10 makes the robot oscillating trajectories, TBD check with the PF algo ?
	while (nh_.ok())
	    {
		//this->goalKeyboard(); // A REMETTRE
		goal_pub_.publish(goal_);
	 	ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
		loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate
	    }
}

int main(int argc, char** argv)
{
  //init the ROS node
  ros::init(argc, argv, "navigation_node");

  MissionManager myMManager;
  myMManager.run();
}
