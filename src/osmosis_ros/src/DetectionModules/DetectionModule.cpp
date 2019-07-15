#include <osmosis_control/DetectionModules/DetectionModule.hpp>

DetectionModule::DetectionModule ()
{
	driveState_=IDLE;
}

void DetectionModule::driveDetectionModule()
{
	switch(driveState_)
	{
		case IDLE:
			if(state_)
				driveState_=TRIGGERED;
			break;

		case TRIGGERED:
			if(!state_)
				driveState_=IDLE;
			break;
	}
}

void DetectionModule::run()
{
	detect();
	driveDetectionModule();
	ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
}

bool DetectionModule::getState()
{
	return state_;
}

