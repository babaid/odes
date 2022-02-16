# ODES
ODES is an ode solver project written in modern c++.

After you downloaded ODES, you can use CMake to build all the needed dependencies. 
The easiest way to build ODES is using the cmake gui software, or just plane cmake.
```cmake
cmake --build --target [options] odes --config [options]
```
Tests will run automatically once the library was built, ensuring that you can use ODES properly, without errors.



The main part of ODES is the Ode class, wich is the base of every ode
The constructor takes 4 arguments

```c++
Ode ode(Function, Interval, y0, step_count);
```

t0 and y0 are the starting points of the ode, as for y(t0) = t0.
Interval represents the interval in wich t (as in the euler method) varies.
step_count is the same as stated in the euler method

But it can also be called with 3 arguments, and you can use the assignment operator to assign a mathematical expression to the Ode object:


```c++
auto f = function<double(double, double)>([](double y, double t){return y*t}); //aurguments alwas have to be in the order (y,t) 
Ode ode(Interval, y0, step_size);
ode = f;
```



Once you choosed a solving algorithm, in our example explicit Euler, you have to instatiate a solver, pass the ode as an argument to it, and you can use the member function c++ solver(vector<double>&) to get the solution



```c++ 
    auto f = function<double(double, double)>([](double y, double t){return y*t}); //aurguments alwas have to be in the order (y,t) 
    Ode ode(Interval, y0, step_size);

    ode = f;

    std::vector<double> solution;
    ExEuler solver(ode);

    solver.solve(solution);
```

If you want to compare the analytical solution and the numerical, you can use:

```c++
    double error = ode.accuracy(solution, analytical_sol);
```


    

where solution is the one stated above, and analytical_sol is the function/lamdba containing the analytical solution.
Compare returns the mean error of the difference of the numerical solution and the analytical one.


(If one wants to save the data to a csv file for plotting, there is a helper function:



```c++
    ode.save(solution, name);
```


Where solution is a vector of pairs, name is a string, the name of the csv file.

You can help by increasing the possible solving algorithms in the following way:


```c++
    class MySolver: public Ode
    {
        public:
            Mysolver(function<double(double, double)> f, Interval t, y0, step): f(f), time(t), y0(y0), step(step){}
            MySolver(Ode& o):Ode(o){}
            void solve(solution) override; //the place of the solving algorithm
    };
```

