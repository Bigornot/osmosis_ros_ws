#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Tree_Vector
{
private :
	// Fault Tree 
	vector<vector<int>> DM_Branches; // DM_Branches ?
	// Recovery Tree
	vector<vector<int>> Recovery_Branches;

	vector<int> DM_activated;
	vector<int> RM_activated;

	vector<int> DM_dominant; 
	vector<int> RM_dominant;

	void findDominant(char moduleType);

public :
	Tree_Vector();

	void push_DM(int dm);
	void push_RM(int rm);
	vector<int> findDMDominant();
	vector<int> findRMDominant();
};
