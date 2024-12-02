#pragma once
#include <vector>
#include <iostream>
#include <chrono>
#include <random>

#include "Particle.h"
#include "Time_values.h"

class PSO
{
public:
    PSO(double (*fitness_func)(const std::vector<double>&, Particle&), int num_particles, double w, double c1, double c2);
    void run(int iterations, double precision);

    std::vector<Particle> particles;
    double w, c1, c2;
    std::mt19937 rnd;
    double (*fitness_func)(const std::vector<double>&, Particle&);


};
