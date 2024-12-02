#pragma once
#include <vector>
#include "Particle.h"
#define M_PI 3.14159265358979323846

double fitness_sphere(const std::vector<double>& position, Particle&);
double fitness_sphere(const std::vector<double>& position);

double fitness_rastrigin(const std::vector<double>& position, Particle&);
double fitness_rastrigin(const std::vector<double>& position);


double equation(const std::vector<double>& prev_sol, Particle& particle);

