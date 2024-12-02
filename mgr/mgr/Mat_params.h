#pragma once
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

class Mat_params
{
public:
	double epsilon;
	double T;				//Temparature
	double D;				//Grain size of austenit
	double mi;				//Kirchoff's module
	double ro_poprzednie;	//Previous dislocation density
	double ro_t_tcr;		//Dislocation density at critical time
	double t_poprzednie;	//Previous dislocation denssity
	double Q;				//Activation energy
	double b;				//Burger's vector
	double tcr_start;		//Critical starting time
	double R;				//gas constant
	double Z;				//Zener-Hollomon parameter
	double G;				//Shear modulus


public:
	Mat_params();
	Mat_params(std::string&);
	//void show_params();
	double count_Z();
};

