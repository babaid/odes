#define CATCH_CONFIG_MAIN

#include <iostream>
#include <cmath>
#include "catch2/catch.hpp"

#include "../include/odes.h"

TEST_CASE("Solving algorithm ExEuler is being tested", "[ExEuler::solve]")
{
    // The ode wich we want to solve
    auto f = std::function<double(double, double)>([](double y, double t) { return y / t; });
    //Analytical solution of the ode
    auto y = std::function<double(double)>([](double t) { return t; });

    //a short interval to avoid big errors
    Interval t(1, 5);
    Ode ode(f, t, 1.0, 1e4);
    

    double tolerance = 1;
    REQUIRE(t.first < t.second);
    //maybe test if f is continous on the interval..
    
    SECTION("Exeuler performs well")
    {
        std::vector<double> sol;
        ExEuler *ex = new ExEuler(ode);
        ex->solve(sol);

        for(auto elem:sol) REQUIRE(!std::isinf(elem));
        REQUIRE(ode.accuracy(sol, y) < tolerance);

    }
    SECTION("ImpEuler performs well")
    {
        std::cout << "etst" <<std::endl;
        std::vector<double> sol;
        ImpEuler *imp = new ImpEuler(ode);
        imp->solve(sol);

        for(auto elem:sol) REQUIRE(!std::isinf(elem));
        REQUIRE(ode.accuracy(sol, y) < tolerance);
    }
}

