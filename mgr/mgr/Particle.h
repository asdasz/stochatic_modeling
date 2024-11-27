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


class Particle
{
public:
    Particle(double (*fitness)(const std::vector<double>&), unsigned);
    Particle(double (*fitness)(const std::vector<double>&), std::vector<double>&, double&);
    std::mt19937 rnd;

    std::vector<double> A;  // 1 - hardening, 
                            // 2 - recovery, 
                            // 3 - recrystallization
    std::vector<double> cur_pos, vel;
    double cur_fit;

    std::vector<double> local_best_pos;
    double local_best_fit;

    static std::vector<double> global_best_pos;
    static double global_best_fit;
    static std::vector<double> minx, maxx;
    static int dim;
    static Mat_params params;

    void show_params();
    void show_fit();
    void update_global();
    void make_a_step(double (*fitness)(const std::vector<double>&), double&, double&, double&);
    void count_A(Mat_params&);
};

void load_borders(std::string& filename, int& dim, std::vector<double>& min, std::vector<double>& max);
void load_mat_params(std::string& filename, Mat_params& params);
