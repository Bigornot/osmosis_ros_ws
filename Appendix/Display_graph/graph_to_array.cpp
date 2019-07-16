#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <fstream>

//This works only with the test.graph syntax

float apply_line_x(std::string line)
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

float apply_line_y(std::string line)
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

int apply_line_node1(std::string line)
{
	int n=0;
	int pos_N=line.find('N');
        if (pos_N>=0)
        {
                int pos_guill=line.find('"',pos_N);
                std::string ns=line.substr(pos_N+1, pos_guill-pos_N-1);
								n=strtol(ns.c_str(), NULL,0);
        }
	return n;
}

int apply_line_node2(std::string line)
{
	int n=0;
	int pos_N=line.find('N',11);
        if (pos_N>=0)
        {
                int pos_guill=line.find('"',pos_N);
                std::string ns=line.substr(pos_N+1, pos_guill-pos_N-1);
								n=strtol(ns.c_str(), NULL,0);
        }

	return n;
}

void graph_to_list(std::vector<float> &LX, std::vector<float> &LY,std::vector<int> &LN1,std::vector<int> &LN2)
{
  std::ifstream file("test.graph", std::ios::in);  // open in read only
	float x;
	float y;
	int n1;
	int n2;
	bool node=false;

        if(file)
        {
					int i=1;
					std::string line;
        	while(getline(file, line))  // while we can add content
        	{
						int test=line.find("id");
						if (test>=0)
						{
							x=apply_line_x(line);
							y=apply_line_y(line);
							LX.push_back(x);
							LY.push_back(y);
						}
						if(node)
						{
							test=line.find('N');
							if (test>=0)
							{
								n1=apply_line_node1(line);
								n2=apply_line_node2(line);
								LN1.push_back(n1);
								LN2.push_back(n2);
							}
						}

						int test2=line.find("edge");
						if (test2>=0)
							node=true;
		       }
           file.close();
        }
        else
          std::cerr << "Can't open the file !" << std::endl;
}

int main()
{
	std::vector<float> LX,LY;
	std::vector<int> LN1,LN2;
	graph_to_list(LX,LY,LN1,LN2);

  std::ofstream file("file.txt", std::ios::out | std::ios::trunc);
	if (file)
	{
		for (int i=0; i<LX.size();i++)
		{
			file<< LX[i]<<" ";
		}
			file<<std::endl;
		for (int i=0; i<LY.size();i++)
		{
			file<<LY[i]<<" ";
		}
			file<<std::endl;
		for (int i=0; i<LN1.size();i++)
		{
			file<< LN1[i]<<" ";
		}
			file<<std::endl;
		for (int i=0; i<LN2.size();i++)
		{
			file<<LN2[i]<<" ";
		}
		file.close();
	}
	return 0;
}
