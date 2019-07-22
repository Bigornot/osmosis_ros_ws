#include <osmosis_control/detectionModules/DetectionModule.hpp>

DetectionModule::DetectionModule ()
{
	state_=false;
	driveState_=IDLE;
}

void DetectionModule::detectionModuleFSM()
{
	switch(driveState_)
	{
		case IDLE:
			if(state_)
				driveState_=ACTIVE;
			break;

		case ACTIVE:
			if(!state_)
				driveState_=IDLE;
			break;
	}
}

void DetectionModule::run()
{
	detect();
	detectionModuleFSM();
	ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
}

int DetectionModule::getState()
{
	return driveState_;
}

