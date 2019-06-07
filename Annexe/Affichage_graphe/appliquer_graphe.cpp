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
        }
        return y;
}

int traiter_ligne_noeud1(std::string line)
{
	int n=66;
	int pos_N=line.find('N');
        if (pos_N>=0)
        {
                int pos_guill=line.find('"',pos_N);
                std::string ns=line.substr(pos_N+1, pos_guill-pos_N-1);
		n=strtol(ns.c_str(), NULL,0);
        }

	return n;
}

int traiter_ligne_noeud2(std::string line)
{
	int n=7;
	int pos_N=line.find('N',11);
        if (pos_N>=0)
        {
                int pos_guill=line.find('"',pos_N);
                std::string ns=line.substr(pos_N+1, pos_guill-pos_N-1);
		n=strtol(ns.c_str(), NULL,0);
        }

	return n;
}

 
void graphe_vers_liste(std::vector<float> &LX, std::vector<float> &LY,std::vector<int> &LN1,std::vector<int> &LN2)
{
        std::ifstream fichier("test.graph", std::ios::in);  // on ouvre en lecture
	float x;
	float y;
	int n1;
	int n2;
	bool noeud=false;

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
			if(noeud)
			{	
			test=ligne.find('N');
				if (test>=0)
				{
					n1=traiter_ligne_noeud1(ligne);
					n2=traiter_ligne_noeud2(ligne);
					LN1.push_back(n1);
					LN2.push_back(n2);
				}
			}

			int test2=ligne.find("edge");
			if (test2>=0)
				noeud=true;
        	}      
 
               fichier.close();

        }

        else
                std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
 
}



int main()
{
	std::vector<float> LX,LY;
	std::vector<int> LN1,LN2;
	graphe_vers_liste(LX,LY,LN1,LN2);
	
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
			fichier<<std::endl;
		for (int i=0; i<LN1.size();i++)
		{
			fichier<< LN1[i]<<" ";	
		}
			fichier<<std::endl;
		for (int i=0; i<LN2.size();i++)
		{
			fichier<<LN2[i]<<" ";
		}

	fichier.close();
	}
	return 0;
	


	
}
