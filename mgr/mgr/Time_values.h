#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <fstream>
class Time_values
{
public:
	double start;
	double delta;
	double end;
	double y0;

	Time_values(std::string);
};

