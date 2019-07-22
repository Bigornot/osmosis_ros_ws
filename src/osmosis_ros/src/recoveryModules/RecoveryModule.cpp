#include <osmosis_control/recoveryModules/RecoveryModule.hpp>

RecoveryModule::RecoveryModule(int id, vector<int> successors)
{
	drive_state_=IDLE;
	id_=id;
	successors_=successors;
	state_=false;
}

void RecoveryModule::recoveryModuleFSM()
{
	cout << "ID:" << id_ << " " << state_ << " ";
	switch(drive_state_)
	{
		case IDLE:
			cout << "IDLE" << endl;
			if(state_)
			{
				startRecovery();
				drive_state_=ACTIVATED;
			}
			break;

		case ACTIVATED:
			cout << "ACTIVATED" << endl;
			if(!state_)
			{
				stopRecovery();
				drive_state_=IDLE;
			}
			else
				doRecovery();
			break;

		default:
			drive_state_=IDLE;
			break;
	}
}

int RecoveryModule::getState()
{
	return drive_state_;
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
	recoveryModuleFSM();
}

int RecoveryModule::getId()
{
	return id_;
}

vector<int> RecoveryModule::getSuccessorsId()
{
	return successors_;
}
