#include <FTM_Rule.hpp>


////////////////////// PUBLIC //////////////////////

void FTM_Rule::runFSM()
{
	switch(state_)
	{
		case IDLE:
			if(getStateRM())
				state_=RECOVERY;
			else if(getStateDM())
				state_=ACTIVE;
			break;
		case ACTIVE:
			if(getStateRM())
				state_=RECOVERY;
			else if(!getStateDM())
				state_=IDLE;
			break;
		case RECOVERY:
			if(!getStateRM())
			{
				if(getStateDM())
					state_=ACTIVE;
				else
					state_=IDLE;
			}
			break;
	}
}

FTM_Rule::FTM_Rule(int id, int predecessor, vector<int> successors, DetectionModule* DM, RecoveryModule* RM)
{
	id_=id;
	predecessor_=predecessor;
	successors_=successors;
	DM_ = DM;
	RM_ = RM;
	state_=IDLE;
}

int FTM_Rule::getState()
{
	return state_;
}

int FTM_Rule::getPredecessorId()
{
	return predecessor_;
}

vector<int> FTM_Rule::getSuccessorsId()
{
	return successors_;
}

int FTM_Rule::getId()
{
	return id_;
}

void FTM_Rule::initDM()
{
	DM_->init();
}

void FTM_Rule::runDM()
{
	DM_->run();
}

int FTM_Rule::getStateDM()
{
	return DM_->getState();
}

void FTM_Rule::runRM()
{
	RM_->run();
}

int FTM_Rule::getStateRM()
{
	return RM_->getState();
}

void FTM_Rule::startRM()
{
	RM_->start();
}

void FTM_Rule::stopRM()
{
	RM_->stop();
}

int FTM_Rule::getRMId()
{
	return RM_->getId();
}

vector<int> FTM_Rule::getRMSuc()
{
	return RM_->getSuccessorsId();
}
