#include <osmosis_control/detectionModules/DetectionModule.hpp>


////////////////////// PRIVATE //////////////////////

void DetectionModule::detectionModuleFSM()
{
	switch(drive_state_)
	{
		case IDLE:
			if(state_)
				drive_state_=ACTIVE;
			break;

		case ACTIVE:
			if(!state_)
				drive_state_=IDLE;
			break;
	}
}


////////////////////// PUBLIC //////////////////////

DetectionModule::DetectionModule ()
{
	state_=false;
	drive_state_=IDLE;
}

int DetectionModule::getState()
{
	return drive_state_;
}

void DetectionModule::run()
{
	detect();
	detectionModuleFSM();
	ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
}


