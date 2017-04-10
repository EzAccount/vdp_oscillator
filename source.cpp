#include <algorithm>
#include <functional>
#include <iostream>
#include <array>
#include <iomanip> //for output formating
#define MU 4 //defined by macros (stupid)
#define time_limit 2 // same stupidity for time
std::array<double,3> operator+(const std::array<double,3>& a, const std::array<double,3>& b) // overloaded sum
{
    std::array<double, 3> result;
    std::array<double, 3>::iterator begin = result.begin();
    *begin = *(std::begin(a)) + *(std::begin(b)); //dump but working
    *(++begin) = *(std::begin(a) + 1) + *(std::begin(b) + 1);
    *(++begin) = *(std::begin(a) + 2) + *(std::begin(b) + 2);
    return result;
}
std::array<double,3> operator/(const std::array<double,3>& a, const double& b) // overloaded array * scalar
{
    std::array<double, 3> result;
    std::array<double, 3>::iterator begin = result.begin();
    *begin = *(std::begin(a)) / b;
    *(++begin) = *(std::begin(a) + 1) / b;
    *(++begin) = *(std::begin(a) + 2) / b;
    return result;
}
std::array<double,3> operator*(const std::array<double,3>& a, const double& b) //same with division
{
    std::array<double, 3> result;
    std::array<double, 3>::iterator begin = result.begin();
    *begin = *(std::begin(a)) * b;
    *(++begin) = *(std::begin(a) + 1) * b;
    *(++begin) = *(std::begin(a) + 2) * b;
    return result;
}

std::array<double,3> evolution_function(const std::array<double,3>&  state, const double& time_step) // takes state(t,x,v) returns F(t,x,v) = {t_step,f(t,x,v), g(t,x,v)}
{
    std::array<double,3> value;
    value[0] = 1;
    value[1] = state[2];
    value[2] = -state[1] + MU * state[2] * (1 - state[1]*state[1]);
    return value;
}

std::array<double,3> rk_coefs(std::array<double,3> state, double t_step)
{
    std::array<double,3> coef = evolution_function(state, t_step) * t_step; //{time_step, k_0, l_0}
    std::array<double,3> temp_state = state;
    std::array<double,3> temp_evolution = {0,0,0};
    temp_state = temp_state + coef / 2;
    temp_evolution = evolution_function(temp_state, t_step) * t_step;
    temp_state = temp_state + temp_evolution/2;
    coef = coef + temp_evolution * 2;
    temp_state = temp_state + coef / 2;
    temp_evolution = evolution_function(temp_state, t_step) * t_step;
    temp_state = temp_state + temp_evolution/2;
    coef = coef + temp_evolution * 2;
    temp_state = temp_state + coef;
    coef = coef + evolution_function(temp_state, t_step) * t_step;
    coef = coef/ 6; //returning not exactly RK coefs, but sum of them devided by 6. {6*t_step, sum of k, sum of l}/6
    return coef;
}

int main()
{
    std::array<double,3> coef = {0,0,0}; //initial RK coefs
    std::array<double,3> state = {0,0,2}; //initial values for Cauchy problem
    double t_step = 0.01; // time step
    std::cout << std::setw(15) << "Time" << std::setw(15) << "Coordinate" << std::setw(15) << "Speed" << std::endl;
    while (state[0] < time_limit) // Evaluate untill time_limit
    {
        coef = rk_coefs(state, t_step);
        state = state + coef;
        std::cout << std::setw(15) << state[0] << std::setw(15) << state[1] << std::setw(15) <<state[2] << std::endl; //out to std, move by > operator
    }
	return 0;
}
