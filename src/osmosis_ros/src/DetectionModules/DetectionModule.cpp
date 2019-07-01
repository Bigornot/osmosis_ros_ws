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
		  debug_msg="DETECTION_MODE";
			state_.data=this->detect();
			if (state_.data)
				driveState_=START_RECOVERY;
			break;

		case START_RECOVERY:
			debug_msg="START_RECOVERY";
			//demarrer la procedure de recovery
			driveState_=ERROR_DETECTED;
			break;

		case ERROR_DETECTED:
			debug_msg="ERROR_DETECTED";
			driveState_=DETECTION_MODE;
			break;
	}
}

void DetectionModule::run()
{
	ros::Rate loop_rate(10);
	while (nh_.ok())
	{
		this->driveDetectionModule();
		ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
		loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate
	}
}
