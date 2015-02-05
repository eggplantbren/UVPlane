#include "Data.h"
#include <fstream>
#include <iostream>

using namespace std;

Data Data::instance;

Data::Data()
{

}

void Data::load(const char* filename)
{
	fstream fin(filename, ios::in);
	if(!fin)
	{
		cerr<<"# Error. Couldn't open file "<<filename<<"."<<endl;
		return;
	}

	// Empty the vectors
	u.clear();
	v.clear();
	intensity.clear();
	sigma.clear();

	double temp1, temp2, temp3, temp4;
	while(fin>>temp1 && fin>>temp2 && fin>>temp3 && fin>>temp4)
	{
		u.push_back(temp1);
		v.push_back(temp2);
		intensity.push_back(temp3);
		sigma.push_back(temp4);
	}

	cout<<"# Loaded "<<u.size()<<" data points from file "
			<<filename<<"."<<endl;
	fin.close();
}

