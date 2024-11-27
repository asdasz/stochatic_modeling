#include "PSO.h"

PSO::PSO(double (*fitness_func)(const std::vector<double>&), int num_particles, double w, double c1, double c2)
    : w(w), c1(c1), c2(c2), fitness_func(fitness_func)
{
    std::mt19937 rnd(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
    for (int i = 0; i < num_particles; i++) 
    {
        particles.push_back(Particle(fitness_func, rnd()));
        particles[i].update_global();
    }
}

void PSO::run(int iterations, double precision) 
{
    for (int iter = 0; iter < iterations; iter++) 
    {
        for (auto& particle : particles)
        {
            particle.make_a_step(fitness_func, w, c1, c2);
        }
        for (auto& particle : particles)
        {
            particle.update_global();
        }
        particles[0].show_params();

        if (Particle::global_best_fit < precision)
        {
            std::cout << "Iter : " << iter << std::endl << "Precision has been reached\n";
            break;
        }
    }
}



