#include <iostream>
#include <vector>
#include <random>
#include <chrono>

#include "needed_libs.h"
#include "Particle.h"
#include "PSO.h"
#include "Mat_params.h"
#include "diff_fun.h"

using namespace std;

int main()
{
    double w = 0.729; //inertia coefficient
    double c1 = 1.49445; //cognitive coefficient
    double c2 = 1.49445; //social coefficient
    int Nmax = 1000;
    double precision = 1e-6;
    int num_particles = 1000;
    string file = "../txt_files/a_values.txt";
    string material_params_file = "../txt_files/material_params.txt";

    load_borders(file, Particle::dim, Particle::minx, Particle::maxx);
    load_mat_params(material_params_file, Particle::params);


    double t_start = 0.0, t_end = 0.3, t_delta = 0.1, y0 = 1.0;


    //Runge_Kutty(&fitness_sphere, t_start, t_end, t_delta, y0);

    cout << Particle::dim << endl;

    PSO pso(fitness_sphere, num_particles, w, c1, c2);
    pso.run(Nmax, precision);
    Particle best(fitness_sphere, Particle::global_best_pos, Particle::global_best_fit);
    best.show_fit();
    
    return 0;
}

