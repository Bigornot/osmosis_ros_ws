#include <osmosis_control/FTM_Rule.hpp>

using namespace std;

FTM_Rule::FTM_Rule(int id, int predecessor, vector<int> successors, DetectionModule* DM, RecoveryModule* RM)
{
	id_=id;
	predecessor_=predecessor;
	successors_=successors;
	DM_ = DM;
	RM_ = RM;
}

int FTM_Rule::getPredecessor()
{
	return predecessor_;
}

vector<int> FTM_Rule::getSuc()
{
	return successors_;
}

int FTM_Rule::getId()
{
	return id_;
}

void FTM_Rule::runDM()
{
	DM_->run();
}

bool FTM_Rule::getStateDM()
{
	return DM_->getState();
}

void FTM_Rule::runRM()
{
	RM_->run();
}

bool FTM_Rule::getStateRM()
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
	return RM_->getSuc();
}

