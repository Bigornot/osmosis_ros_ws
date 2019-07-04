#include <osmosis_control/RecoveryModules/RecoveryModule.hpp>

using namespace std;

RecoveryModule::RecoveryModule(int id, int predecessor, vector<int> successors)
{
	driveState_=IDLE;
	id_=id;
	predecessor_=predecessor;
	successors_=successors;
	state_=false;
}

void RecoveryModule::driveRecoveryModule()
{
	switch(driveState_)
	{
		case IDLE:
			if(state_)
				driveState_=RECOVERY;
			break;
		case RECOVERY:
			this->doRecovery();
			if(!state_)
				driveState_=IDLE;
			break;
		default:
			driveState_=IDLE;
			break;
	}
}

bool RecoveryModule::getState()
{
	return state_;
}

void RecoveryModule::start()
{
	state_=true;
}

void RecoveryModule::stop()
{
	state_=false;
}

void RecoveryModule::run()
{
	this->driveRecoveryModule();
	ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
}

int RecoveryModule::getId()
{
	return id_;
}

vector<int> RecoveryModule::getSuc()
{
	return successors_;
}
