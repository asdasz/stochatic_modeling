#include "equations.h"
double fitness_sphere(const std::vector<double>& position, Particle& particle)
{
    return fitness_sphere(position);
}
double fitness_sphere(const std::vector<double>& position)
{
    double fitnessVal = 0.0;
    for (int i = 1; i < position.size(); i++)
    {
        fitnessVal += ((position[i] - 5 * i) * (position[i] - 5 * i));
    }
    //cout << fitnessVal << endl;
    return fitnessVal;
}

double fitness_rastrigin(const std::vector<double>& position, Particle& particle)
{
    return fitness_rastrigin(position);
}
double fitness_rastrigin(const std::vector<double>& position)
{
    double fitnessVal = 0.0;
    for (double xi : position) {
        fitnessVal += (xi * xi) - (10 * cos(2 * M_PI * xi)) + 10;
    }
    return fitnessVal;
}




double equation(const std::vector<double>& prev_sol, Particle& particle)
{
    const double& epsilon = prev_sol[2];

    double A1part, A2part, A3part;
    A1part = particle.A[1] * epsilon;
    A2part = particle.A[2] * prev_sol[1] * pow(epsilon, 1 - particle.cur_pos[7]);
    A3part = particle.A[3] * pow(prev_sol[1], particle.cur_pos[6]);

    //std::cout << particle.A[1] << "\t" << particle.A[2] << "\t" << particle.A[3] << "\t" << "\n";
    //std::cout << "prev_sol[1] * pow(epsilon, 1 - particle.cur_pos[7]):   " << prev_sol[1] << " * " << epsilon << " " << particle.cur_pos[7] << std::endl;

    std::cout << A1part << "\t" << A2part << "\t" << A3part << "\t" << A1part - A2part - A3part << "\n";
    return A1part - A2part - A3part;
}