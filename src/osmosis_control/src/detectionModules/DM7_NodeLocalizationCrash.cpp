#include <detectionModules/DM7_NodeLocalizationCrash.hpp>

////////////////////// PRIVATE //////////////////////

void DM7_NodeLocalizationCrash::detect()
{
	int i,j;
	bool found=true;

	ros::master::getNodes(aliveNodes_);
	for(i=0; i<nodesToCheck_.size() && found; i++)
	{
		found = false;
		for(j=0; j<aliveNodes_.size() && !found; j++)
		{
			if(aliveNodes_[j]==nodesToCheck_[i])
				found = true;
		}
	}
	aliveNodes_.clear();

	if(!found)
		state_=true;
	else
		state_=false;
}


////////////////////// PUBLIC //////////////////////

DM7_NodeLocalizationCrash::DM7_NodeLocalizationCrash() : DetectionModule()
{
	nodesToCheck_.push_back("/localization_node");
}

void DM7_NodeLocalizationCrash::init()
{
}
