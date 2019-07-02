#include <osmosis_control/FTM_Rule.hpp>

using namespace std;

FTM_Rule::FTM_Rule(int id, int antecedent, vector<int> successors, DetectionModule* DM, RecoveryModule* RM)
{
	id_=id;
	antecedent_=antecedent;
	successors_=successors;
	DM_ = DM;
	RM_ = RM;
	
}

int FTM_Rule::getAnt()
{
	return antecedent_;
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

