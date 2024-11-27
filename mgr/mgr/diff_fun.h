#pragma once
#include <vector>
#include <iostream>
#define M_PI 3.14159265358979323846

std::vector<double> Runge_Kutty(double(*fun)(const std::vector<double>&), double& t_start, double& t_end, double& t_delta, double& y0);

double fitness_sphere(const std::vector<double>& position);
double fitness_rastrigin(const std::vector<double>& position);
double function(const std::vector<double>& position);




