#pragma once
#include <vector>
#include <iostream>
#include "Particle.h"
#include <chrono>
#include <random>
class PSO
{
public:
    PSO(double (*fitness_func)(const std::vector<double>&), int num_particles, double w, double c1, double c2);
    void run(int iterations, double precision);

    std::vector<Particle> particles;
    double w, c1, c2;
    std::mt19937 rnd;
    double (*fitness_func)(const std::vector<double>&);


};
