#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h> 
#include <vector>
#include <fstream>




float traiter_ligne_x(std::string line)
{
	float x=0;
	int pos_x=line.find('x');
	if (pos_x>=0)
	{
		int pos_comax=line.find(',',pos_x);
		std::string xs=line.substr(pos_x+4, pos_comax-pos_x-4);	
		x=strtof(xs.c_str(), NULL);
	}
	return x;
}

float traiter_ligne_y(std::string line)
{
	float y=0;
        int pos_y=line.find('y');
        if (pos_y>=0)
        {
                int pos_bracky=line.find('}',pos_y);
                std::string ys=line.substr(pos_y+4, pos_bracky-pos_y-4);
		y=strtof(ys.c_str(), NULL);
		y=strtof(ys.c_str(), NULL);
        }
        return y;
}
 
void graphe_vers_liste(std::vector<float> &LX, std::vector<float> &LY)
{
        std::ifstream fichier("test.graph", std::ios::in);  // on ouvre en lecture
	float x;
	float y;

        if(fichier)  // si l'ouverture a fonctionné
        {	
		int i=1;
		std::string ligne;
        	while(getline(fichier, ligne))  // tant que l'on peut mettre la ligne dans "contenu"
        	{
			int test=ligne.find("id");
			if (test>=0)
			{
				x=traiter_ligne_x(ligne);
				y=traiter_ligne_y(ligne);
				LX.push_back(x);
				LY.push_back(y);
			}
        	}      
 
               fichier.close();

        }

        else
                std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
 
}



int main()
{
	std::vector<float> LX,LY;

	graphe_vers_liste(LX,LY);
	
        std::ofstream fichier("tableau.txt", std::ios::out | std::ios::trunc);
	if (fichier)
	{
		for (int i=0; i<LX.size();i++)
		{
			fichier<< LX[i]<<" ";	
		}
			fichier<<std::endl;
		for (int i=0; i<LY.size();i++)
		{
			fichier<<LY[i]<<" ";
		}
	
	fichier.close();
	}
	return 0;
	


	
}
