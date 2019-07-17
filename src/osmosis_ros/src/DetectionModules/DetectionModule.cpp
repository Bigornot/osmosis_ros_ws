#include <osmosis_control/DetectionModules/DetectionModule.hpp>

DetectionModule::DetectionModule ()
{
	state_=false;
	driveState_=IDLE;
}

void DetectionModule::driveDetectionModule()
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
	driveDetectionModule();
	ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
}

int DetectionModule::getState()
{
	return driveState_;
}

