#include <vector>
#include <functional>
#include <fstream>
#include <string>
#include<iostream>

//represents a closed interval for example [0, 1]
using Interval = std::pair<double, double>;



//The abstract class representing any ode, this is the base class of every solver
class Ode
{
public:
    Ode(Interval t, double y0, unsigned N) : time(t), y0(y0), step((t.second - t.first) / N) {}
    Ode(std::function<double(double, double)> &ode, Interval t, double y0, unsigned N) : f(ode), time(t), y0(y0), step((t.second - t.first) / N) {}


    Ode(Ode &&) = default;
    Ode(Ode &) = default;
    virtual ~Ode(){};

    void operator=(std::function<double(double, double)> &ode) { f = ode; }

    virtual void solve(std::vector<double> &){};

    void change_steps(unsigned N);

    virtual void save_to_csv(std::vector<double> &, std::string);

    virtual double accuracy(std::vector<double> &, std::function<double(double)> analytical);

protected:
    std::function<double(double, double)> f;
    Interval time;
    double step, y0;
};

//Repesents the explicit Euler method
class ExEuler : public Ode
{
public:
    ExEuler(std::function<double(double, double)> f, Interval time, double y0, double N) : Ode(time, y0, N) {}
    ExEuler(Ode &o) : Ode(o) {}
    ExEuler(ExEuler &&) = default;
    ~ExEuler(){};

    void solve(std::vector<double> &data) override;
};

//Represents the implicit Euler method
class ImpEuler : public Ode
{
public:
    ImpEuler(std::function<double(double, double)> f, Interval time, double y0, double N) : Ode(f, time, y0, N) {}
    ImpEuler(Ode &o) : Ode(o) {}
    ImpEuler(ImpEuler &&) = default;
    ~ImpEuler(){};

    void solve(std::vector<double> &data) override;
};

class RK4: public Ode
{
    public:
    RK4(std::function<double(double, double)> f, Interval time, double y0, double N) : Ode(f, time, y0, N) {}
    RK4(Ode &o) : Ode(o) {}
    RK4(ImpEuler &&) = default;
    ~RK4(){};

    void solve(std::vector<double> &data) override;
};