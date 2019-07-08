#include <osmosis_control/RecoveryModules/RecoveryModule.hpp>

RecoveryModule::RecoveryModule(int id, int predecessor, vector<int> successors, ros::Duration delay)
{
	activation_time_=ros::Time::now()-next_activation_delay_; 
	next_activation_delay_=delay;
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
			if(state_ && ros::Time::now()-activation_time_>next_activation_delay_)
			{
				activation_time_=ros::Time::now();
				driveState_=RECOVERY;
			}
			break;
		case RECOVERY:
			this->doRecovery();
			state_=WAIT_STOP;
			break;

		case WAIT_STOP:
			if(!state_)
				driveState_=STOP;
			break;

		case STOP:
			state_=IDLE;
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
