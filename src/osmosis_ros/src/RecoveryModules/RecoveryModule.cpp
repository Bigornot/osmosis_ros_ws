#include <osmosis_control/RecoveryModules/RecoveryModule.hpp>

RecoveryModule::RecoveryModule(int id, vector<int> successors)
{
	driveState_=IDLE;
	id_=id;
	successors_=successors;
	state_=false;
}

void RecoveryModule::driveRecoveryModule()
{
	switch(driveState_)
	{
		case IDLE:
			if(state_)
			{
				startRecovery();
				driveState_=ACTIVATED;
			}
			break;

		case ACTIVATED:
			if(!state_)
			{
				stopRecovery();
				driveState_=IDLE;
			}
			else
				doRecovery();
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
	driveRecoveryModule();
	//ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
}

int RecoveryModule::getId()
{
	return id_;
}

vector<int> RecoveryModule::getSuccessorsId()
{
	return successors_;
}
