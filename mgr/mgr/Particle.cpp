#include "Particle.h"

Particle::Particle(double (*fitness)(const std::vector<double>&, Particle&), unsigned seed)
    : rnd(seed), cur_pos(dim), vel(dim), local_best_pos(dim), A(4)
{
    for (int i = 1; i < dim; i++) 
    {
        cur_pos[i] = ((maxx[i] - minx[i]) * rnd() / rnd.max()) + minx[i];
        vel[i] = ((maxx[i] - minx[i]) * rnd() / rnd.max()) + minx[i];
    }
    //cur_fit = fitness(cur_pos, *this);
    //local_best_pos = cur_pos;
    //local_best_fit = cur_fit;
}

Particle::Particle(double (*fitness)(const std::vector<double>&, Particle&), std::vector<double>& pos, double& ff)
{
    cur_pos = pos;
    cur_fit = ff;
    local_best_pos = pos;
    local_best_fit = ff;
}

void Particle::show_params() 
{
    
    //for (size_t i = 1; i < cur_pos.size(); i++)
    //{
    //    std::cout << "\t" << cur_pos[i];
    //}
    //std::cout << std::endl;

    //for (size_t i = 1; i < local_best_pos.size(); i++)
    //{
    //    std::cout << "\t" << local_best_pos[i];
    //}
    //std::cout << std::endl;


    //for (size_t i = 1; i < global_best_pos.size(); i++)
    //{
    //    std::cout << "\t" << global_best_pos[i];
    //}
    //std::cout << std::endl << std::endl;
    std::cout << vel[1] << "\t\t" << cur_pos[1] << std::endl;

}

void Particle::show_fit()
{
    for (int i = 1; i < dim; i++)
    {
        std::cout << i << ":\t" << cur_pos[i] << std::endl;
    }
    std::cout << std::setprecision(10) << cur_fit << std::endl;
}

void Particle::update_global()
{
    if (global_best_fit > cur_fit)
    {
        global_best_fit = cur_fit;
        global_best_pos = cur_pos;
        //for (int i = 1; i < dim; i++)
        //{
        //    std::cout << global_best_pos[i] << std::endl;
        //}
        //std::cout << std::endl;
    }
}

void Particle::make_a_step(double (*fitness)(const std::vector<double>&, Particle&), double& w, double& c1, double& c2, Time_values& t)
{
    double r1 = rnd() / static_cast<double>(rnd.max());
    double r2 = rnd() / static_cast<double>(rnd.max());

    for (int i = 1; i < dim; i++)
    {
        vel[i] = w * vel[i] + 
                 c1 * r1 * (local_best_pos[i] - cur_pos[i]) + 
                 c2 * r2 * (global_best_pos[i] - cur_pos[i]);

        vel[i] = std::max(minx[i], std::min(maxx[i], vel[i]));
        cur_pos[i] += vel[i];
    }
    cur_hist = Runge_Kutty(fitness, t, *this); //fitness(cur_pos, *this);
    if (cur_fit < local_best_fit)
    {
        local_best_fit = cur_fit;
        local_best_pos = cur_pos;
    }

}

void Particle::count_A()
{
    double b = 0.25 * pow(10.0, -9.0);
    double l = cur_pos[1] * (pow(params.Z, (-1.0)*cur_pos[9]));
    double tau = params.G * pow(b, 2) / 2.0;

    A[1] = 1.0 / (b * l);
    A[2] = cur_pos[2] * exp((-(1.0) * cur_pos[3]) / (params.R * params.T));
    A[3] = cur_pos[4] * 3 * tau / params.D * exp(-(1.0) * cur_pos[5] / (params.R * params.T));
    std::cout << A[1] << "\t" << A[2] << "\t" << A[3] << "\n";
}



// __________________________________________________________//


std::vector<double> Particle::minx, Particle::maxx;
std::vector<double> Particle::global_best_pos;
std::vector<double> Particle::global_best_hist;



double Particle::global_best_fit = std::numeric_limits<double>::max();
int Particle::dim;
Mat_params Particle::params;

void load_borders(std::string& filename, int& dim, std::vector<double>& min, std::vector<double>& max)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return;
    }

    //pushing zeros so the numbering starts with 1
    min.push_back(0.0);
    max.push_back(0.0);


    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream lineStream(line);
        std::string key;
        double minValue, maxValue;

        if (lineStream >> key >> minValue >> maxValue)
        {
            min.push_back(minValue);
            max.push_back(maxValue);
        }
        else
        {
            std::cerr << "Wrong format in line: " << line << " in file: " << filename << std::endl;
        }
    }

    file.close();
    dim = min.size();
}

void load_mat_params(std::string& filename, Mat_params& params)
{
    params = Mat_params(filename);
    //std::cout << params.Q << std::endl;
}

std::vector<double> Runge_Kutty(double(*fun)(const std::vector<double>&, Particle&), Time_values& t, Particle& particle)
{
    double repeat = round((t.end - t.start) / t.delta);
    std::vector<double> x, y;
    x.push_back(t.start);
    y.push_back(t.y0);
    std::cout << "y0 = " << t.y0 << std::endl;
    std::vector<double> k(4);
    for (int i = 1; i <= repeat; i++)
    {
        k[0] = t.delta * fun({ x[i - 1],                    y[i - 1],               t.delta }, particle);
        k[1] = t.delta * fun({ x[i - 1] + 0.5 * t.delta,    y[i - 1] + k[0] / 2,    t.delta }, particle);
        k[2] = t.delta * fun({ x[i - 1] + 0.5 * t.delta,    y[i - 1] + k[1] / 2,    t.delta }, particle);
        k[3] = t.delta * fun({ x[i - 1] + t.delta,          y[i - 1] + k[2],        t.delta }, particle);
        std::cout << std::endl;
        y.push_back(y[i - 1] + (k[0] + 2 * k[1] + 2 * k[2] + k[3]) / 6);
        x.push_back(x[i - 1] + t.delta);
        std::cout << x[i] << "\t\t " << y[i] << std::endl;

    }
    std::cout << x[repeat] << "\t\t " << y[repeat] << std::endl;
    return y;
}