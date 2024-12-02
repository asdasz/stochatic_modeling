#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include "Mat_params.h"
#include "Time_values.h"

class Particle
{
public:
    Particle(double (*fitness)(const std::vector<double>&, Particle&), unsigned);
    Particle(double (*fitness)(const std::vector<double>&, Particle&), std::vector<double>&, double&);
    std::mt19937 rnd;

    std::vector<double> A;  // 1 - hardening, 
                            // 2 - recovery, 
                            // 3 - recrystallization
    std::vector<double> cur_pos, vel;
    std::vector<double> cur_hist;
    double cur_fit;

    std::vector<double> local_best_pos;
    std::vector<double> local_best_hist;
    double local_best_fit;

    static std::vector<double> global_best_pos;
    static std::vector<double> global_best_hist;
    static double global_best_fit;

    static std::vector<double> minx, maxx;
    static int dim;
    static Mat_params params;

    void show_params();
    void show_fit();
    void update_global();
    void make_a_step(double (*fitness)(const std::vector<double>&, Particle&), double&, double&, double&, Time_values&);
    void count_A();
};

void load_borders(std::string& filename, int& dim, std::vector<double>& min, std::vector<double>& max);
void load_mat_params(std::string& filename, Mat_params& params);
std::vector<double> Runge_Kutty(double(*fun)(const std::vector<double>&, Particle&), Time_values&, Particle&);
