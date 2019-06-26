#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

class Tree_Vector
{
	private :
  bool detect=false;
  bool recov=false;

	public :
  //Contruction de l'arbre

  std::vector<string> FTM_Branch1 = { "FTM4", "FTM2", "FTM1" };
  std::vector<string> FTM_Branch2 = { "FTM5", "FTM2", "FTM1" };
  std::vector<string> FTM_Branch3 = { "FTM6", "FTM3", "FTM1" };
  std::vector<vector<string>> FTM_Branch = {FTM_Branch1,FTM_Branch2,FTM_Branch3};
  //FTM PRESENTE A TESTER
  std::vector<string> Liste_FTM_originale={"FTM1","FTM2","FTM3", "FTM4", "FTM5" , "FTM6"};
  std::vector<string> Liste_FTM;

  std::vector<bool> Detection_list={};
  std::vector<bool> Recovery_list={};

  // Recovery Tree
  std::vector<string> Recovery_Branch1 = { "R5", "R1", "R2" };
  std::vector<string> Recovery_Branch2 ={ "R3", "R2" }; //{ "R1R3", "R2" };
  std::vector<string> Recovery_Branch3 = { "R3R4", "R2" };
  std::vector<vector<string>> Recovery_Branch = {Recovery_Branch1,Recovery_Branch2,Recovery_Branch3};
  //FTM PRESENTE A TESTER
  std::vector<string> Liste_Recovery_originale={"R1","R2","R3","R4","R5","R6"};
  std::vector<string> Liste_Recovery;


  Tree_Vector();
};
