#include <osmosis_control/Tree_Vector.hpp>

using namespace std;

Tree_Vector::Tree_Vector()
{
	cout << "1" << endl;

	// FAULT TREE //
	DM_Branches.push_back({1,2,4});
	DM_Branches.push_back({1,2,5});
	DM_Branches.push_back({1,3,6});

	// RECOVERY TREE //
	Recovery_Branches.push_back({1,2,3});


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
	if(find(DM_activated.begin(), DM_activated.end(), dm) == DM_activated.end())
		DM_activated.push_back(dm);
}

void Tree_Vector::push_RM(int rm)
{
	// Check if rm is not already in the list
	if(find(RM_activated.begin(), RM_activated.end(), rm) == RM_activated.end())
		RM_activated.push_back(rm);
}

vector<int> Tree_Vector::findDMDominant()
{
	this->findDominant('D');
	return DM_dominant;
}

vector<int> Tree_Vector::findRMDominant()
{
	this->findDominant('R');
	return RM_dominant;
}

void Tree_Vector::findDominant(char moduleType)
{
	bool found=false;

	if(moduleType=='D')
	{
		// For each Branch
		for(int i=0; i<DM_Branches.size(); i++)
		{
			found=false;

			// For each tree level
			for(int j=0; j<DM_Branches[i].size()&&!found; j++)
			{
				// For each Activated DM
				for(int k=0; k<DM_activated.size()&&!found; k++)
				{
					if(DM_Branches[i][j]==DM_activated[k])
					{
						found=true;
						if(find(DM_dominant.begin(), DM_dominant.end(), DM_activated[k])==DM_dominant.end())
							DM_dominant.push_back(DM_activated[k]);
					}
				}
				
			}
		}
	}

	else if(moduleType=='R')
	{
		// For each Activated RM
		for(int k=0; k<RM_activated.size(); k++)
		{
			// For each Branch
			for(int i=0; i<Recovery_Branches.size(); i++)
			{
				found=false;

				// For each tree level
				for(int j=0; j<Recovery_Branches[i].size()&&!found; i++)
				{
					if(Recovery_Branches[i][j]==RM_activated[k])
					{
						found=true;
						
						if(find(RM_dominant.begin(), RM_dominant.end(), RM_activated[k])==RM_dominant.end());
							RM_dominant.push_back(RM_activated[k]);
					}
				}
				
			}
		}
	}

}
