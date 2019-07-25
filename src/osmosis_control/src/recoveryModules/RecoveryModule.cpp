#include <recoveryModules/RecoveryModule.hpp>


////////////////////// PRIVATE //////////////////////

void RecoveryModule::recoveryModuleFSM()
{
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


////////////////////// PUBLIC //////////////////////

RecoveryModule::RecoveryModule(int id, vector<int> successors)
{
	drive_state_=IDLE;
	id_=id;
	successors_=successors;
	state_=false;
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
	state_=false;
}

void RecoveryModule::run()
{
	debugShowState();
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

void RecoveryModule::debugShowState()
{
	cout << "ID:" << id_ << " " << state_ << " ";
}
