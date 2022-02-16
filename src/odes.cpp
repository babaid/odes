#include "../include/odes.h"
#include<cmath>

//Solves the ode with the explicit euler method, saves it in the vector data
void ExEuler::solve(std::vector<double> &data)
{
    double t{time.first}, y{y0};
    data.push_back(y);

    while (t < time.second)
    {
        t += step;
        y = y + step * f(y, t);
        data.push_back(y);
    }
}

//Solves the ode with the implicit euler method, saves it in the vector data
void ImpEuler::solve(std::vector<double> &data)
{
    double y_ki{y0}, y{y0}, limit{0}, t{time.first};
    data.push_back(y_ki);

    while (t < time.second)
    {
        t += step;

        while (std::abs(y_ki - limit) >= 0.001)
        {
            limit = y + step * f(y_ki, t);  
            y_ki = limit;
        }
        y = limit;
        limit = 0;
        data.push_back(y_ki);
    }
}
//Saves the solution of the ode in a csv file
void Ode::save_to_csv(std::vector<double> &data, std::string filename)
{
    if (filename == "$")
        return;

    filename += ".csv";
    double t{time.first};

    std::ofstream datafile;
    datafile.open(filename);
    for (auto elem : data)
    {
        datafile << t << "," << elem << std::endl;
        t += step;
    }
    datafile.close();
}

//calculates the accuracy of the choosen method, returns the mean error of the solver
double Ode::accuracy(std::vector<double> &solution, std::function<double(double)> analytical)
{
    double error{0.0}, t{time.first};
    for (auto elem : solution)
    {
        error +=std::pow(elem - analytical(t), 2);
        t += step;
    }
    return error / solution.size();
}

void Ode::change_steps(unsigned N)
{
    this->step = (this->time.second - this->time.first)/N;
}