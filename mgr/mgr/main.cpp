#include <iostream>
#include <vector>
#include <random>
#include <chrono>

#include "Particle.h"
#include "PSO.h"
#include "Mat_params.h"
#include "Time_values.h"
#include "equations.h"
using namespace std;

int main()
{
    double w = 0.729; //inertia coefficient
    double c1 = 1.49445; //cognitive coefficient
    double c2 = 1.49445; //social coefficient
    int Nmax = 1;
    double precision = 1e-6;
    int num_particles = 1;

    string file = "../txt_files/a_borders.txt";
    string material_params_file = "../txt_files/material_params.txt";

    load_borders(file, Particle::dim, Particle::minx, Particle::maxx);
    load_mat_params(material_params_file, Particle::params);


    double t_start = 0.0, t_end = 0.8, t_delta = 0.01, y0 = 1.0;

    //std::mt19937 rnd(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
    //Particle particle(fitness_sphere, rnd());
    //Runge_Kutty(&fitness_sphere, t_start, t_end, t_delta, y0, particle);


    cout << Particle::dim << endl;

    PSO pso(equation, num_particles, w, c1, c2);
    pso.run(Nmax, precision);
    Particle best(equation, Particle::global_best_pos, Particle::global_best_fit);
    best.show_fit();
    
    return 0;
}

