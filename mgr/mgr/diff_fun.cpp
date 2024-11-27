#include "diff_fun.h"
std::vector<double> Runge_Kutty(double(*fun)(const std::vector<double>&), double& t_start, double& t_end, double& t_delta, double& y0)
{
    double repeat = round((t_end - t_start) / t_delta);
    std::vector<double> x, y;
    x.push_back(t_start);
    y.push_back(y0);

    std::vector<double> k(4);
    for (int i = 1; i <= repeat; i++)
    {
        k[0] = t_delta * fun({ x[i - 1],                    y[i - 1] });
        k[1] = t_delta * fun({ x[i - 1] + 0.5 * t_delta,    y[i - 1] + k[0] / 2 });
        k[2] = t_delta * fun({ x[i - 1] + 0.5 * t_delta,    y[i - 1] + k[1] / 2 });
        k[3] = t_delta * fun({ x[i - 1] + t_delta,          y[i - 1] + k[2] });

        y.push_back(y[i - 1] + (k[0] + 2 * k[1] + 2 * k[2] + k[3]) / 6);
        x.push_back(x[i - 1] + t_delta);
    }
    std::cout << x[repeat] << " " << y[repeat] << std::endl;
    return y;
}

double fitness_sphere(const std::vector<double>& position) {
    double fitnessVal = 0.0;
    for(int i=1; i<position.size(); i++)
    {
        fitnessVal += ((position[i] - 5 * i) * (position[i] - 5 * i));
    }
    //cout << fitnessVal << endl;
    return fitnessVal;
}

double fitness_rastrigin(const std::vector<double>& position) {
    double fitnessVal = 0.0;
    for (double xi : position) {
        fitnessVal += (xi * xi) - (10 * cos(2 * M_PI * xi)) + 10;
    }
    return fitnessVal;
}

double function(const std::vector<double>& position)
{
    //return cos(position[0]) - sin(position[0]) - position[1];
    return position[0] + position[1];
}