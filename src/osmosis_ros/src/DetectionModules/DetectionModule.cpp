#include <osmosis_control/DetectionModules/DetectionModule.hpp>

DetectionModule::DetectionModule ()
{
	driveState_=DETECTION_MODE;
}

void DetectionModule::driveDetectionModule()
{
	switch (driveState_)
	{
		case DETECTION_MODE:
			state_=this->detect();
			if (state_)
				driveState_=START_RECOVERY;
			break;

		case START_RECOVERY:
			driveState_=ERROR_DETECTED;
			break;

		case ERROR_DETECTED:
			driveState_=DETECTION_MODE;
			break;
	}
}

void DetectionModule::run()
{
	this->driveDetectionModule();
	ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
}

bool DetectionModule::getState()
{
	return state_;
}

