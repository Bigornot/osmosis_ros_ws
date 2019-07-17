#include <osmosis_control/RecoveryModules/RecoveryModule.hpp>

RecoveryModule::RecoveryModule(int id, vector<int> successors, bool managerCanStop)
{
	driveState_=IDLE;
	id_=id;
	successors_=successors;
	state_=false;
	managerCanStop_=managerCanStop;
}

void RecoveryModule::driveRecoveryModule()
{
	cout << "ID:" << id_ << " ";
	switch(driveState_)
	{
		case IDLE:
			cout << "IDLE" << endl;
			if(state_)
			{
				startRecovery();
				driveState_=ACTIVATED;
			}
			break;

		case ACTIVATED:
			cout << "ACTIVATED" << endl;
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

bool RecoveryModule::getManagerCanStop()
{
	return managerCanStop_;
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
	cout << "STOP" << endl;
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
