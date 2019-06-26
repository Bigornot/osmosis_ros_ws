#include <osmosis_control/Tree_Vector.hpp>

using namespace std;

Tree_Vector::Tree_Vector()
{
	for(int i=0; i<Liste_FTM_originale.size();i++)
	{
		Detection_list.push_back(detect);
		Recovery_list.push_back(recov);
	}
	//Recovery_list={false, false ,false ,false ,false, false, false, false};
	//Detection_list={false, false ,false ,false ,false, false, false, false};
}
