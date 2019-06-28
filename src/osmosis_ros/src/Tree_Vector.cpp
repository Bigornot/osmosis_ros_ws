#include <osmosis_control/Tree_Vector.hpp>

using namespace std;

Tree_Vector::Tree_Vector()
{
	// FAULT TREE //
	DM_Branches_.push_back({1,7});
	DM_Branches_.push_back({1,2,5});
	DM_Branches_.push_back({1,3,5,6});


	// RECOVERY TREE //
	RM_Branches_.push_back({1,2,6});
	RM_Branches_.push_back({1,2,3,7});
	RM_Branches_.push_back({1,5});


//////////////////// Example ////////////////////
/*

	// Tree -> The longest different branches

	This :
		DM_Branches.push_back({4,2,1});
		DM_Branches.push_back({5,2,1});
		DM_Branches.push_back({6,3,1});

	 Corresponds to :

                     FTM1
                      |
                      OR
             _______/ | \______
            |         |        |
           FTM2     FTM2      FTM3
            |                  |
            OR                FTM6
          _/ \_
         |     |
        FTM4  FTM5
*/
/////////////////////////////////////////////////

}

void Tree_Vector::push_DM(int dm)
{
	// Check if dm is not already in the list
	if(find(DM_activated_.begin(), DM_activated_.end(), dm) == DM_activated_.end())
		DM_activated_.push_back(dm);
}

void Tree_Vector::push_RM(int rm)
{
	// Check if rm is not already in the list
	if(find(RM_activated_.begin(), RM_activated_.end(), rm) == RM_activated_.end())
		RM_activated_.push_back(rm);
}

vector<int> Tree_Vector::findDMDominant()
{
	this->findDominant('D');
	return DM_dominant_;
}

vector<int> Tree_Vector::findRMDominant()
{
	this->findDominant('R');
	return RM_dominant_;
}

void Tree_Vector::findDominant(char moduleType)
{
	bool found=false;

	if(moduleType=='D')
	{
		// For each Branch
		for(int i=0; i<DM_Branches_.size(); i++)
		{
			found=false;

			// For each tree level
			for(int j=0; j<DM_Branches_[i].size()&&!found; j++)
			{
				// For each Activated DM
				for(int k=0; k<DM_activated_.size()&&!found; k++)
				{
					if(DM_Branches_[i][j]==DM_activated_[k])
					{
						found=true;
						if(find(DM_dominant_.begin(), DM_dominant_.end(), DM_activated_[k])==DM_dominant_.end())
							DM_dominant_.push_back(DM_activated_[k]);
					}
				}

			}
		}
	}

	// Find the dominant RMs and the ones to shutdown
	else if(moduleType=='R')
	{
		// For each Branch
		for(int i=0; i<RM_Branches_.size(); i++)
		{
			found=false;

			// For each tree level
			for(int j=0; j<RM_Branches_[i].size(); j++)
			{
				// For each Activated RM
				if(!found)
				{
					for(int k=0; k<RM_activated_.size(); k++)
					{
						if(RM_Branches_[i][j]==RM_activated_[k])
						{
							found=true;
							if(find(RM_dominant_.begin(), RM_dominant_.end(), RM_activated_[k])==RM_dominant_.end())
								RM_dominant_.push_back(RM_activated_[k]);
						}
					}
				}
				else
				{
					if(find(RM_toShutdown_.begin(), RM_toShutdown_.end(), RM_Branches_[i][j])==RM_toShutdown_.end())
						RM_toShutdown_.push_back(RM_Branches_[i][j]);
				}
			}
		}

	}

}

vector<int> Tree_Vector::getRMToShutdown()
{
	return RM_toShutdown_;
}


void Tree_Vector::showDMActivated()
{
	cout << "DM activated : ";
	for(int i=0; i<DM_activated_.size(); i++)
		cout << DM_activated_[i]<<" ";
	cout << endl << endl;
}


void Tree_Vector::showRMActivated()
{
	cout << "RM activated : ";
	for(int i=0; i<RM_activated_.size(); i++)
		cout << RM_activated_[i]<<" ";
	cout << endl << endl;
}
