#include <iostream>
#include <math.h>
#define MU 1

double* evolution_function(double t, double x, double v, double* value) // takes state(t,x,v) returns F(t,x,v) = {f(t,x,v), g(t,x,v)}
{
    value[0] = v;
    value[1] = -x + MU * v * (1 - x * x);
    return value;
}

double* rk_coefs(double* state, double t_step, double* coef)
{
    double* temp;
    temp = evolution_function(state[0], state[1], state[2], temp); // Temp now contain k_0, l_0
    coef[0] = temp[0];
    coef[1] = temp[1]; // Coef cotain k_0, l_0
    temp = evolution_function(state[0] + t_step/2, state[1] + temp[0]/2, state[2] + temp[1]/2, temp); // k_1, l_1
    coef[0] += 2*temp[0];
    coef[1] += 2*temp[1];// k_0 + 2k_1;
    temp = evolution_function(state[0] + t_step/2, state[1] + temp[0]/2, state[2] + temp[1]/2, temp); // k_2, l_2
    coef[0] += 2*temp[0];
    coef[1] += 2*temp[1];// k_0 + 2k_1 + 2k_2;
    temp = evolution_function(state[0] + t_step, state[1] + temp[0], state[2] + temp[1], temp); //k_1, l_3
    coef[0] += temp[0];
    coef[1] += temp[1];
    coef[0] = coef[0] * t_step / 6;
    coef[1] = coef[1] * t_step / 6;
    return coef;
}

int main()
{
    double coef[2] = {0, 0}; // initial values of RK coefs
    double state[3] = {0, 0, 1}; // initial values for Cauchy problem
    double t_step = 0.01; // time step
    while (state[0] < 1)
    {
        //double* temp = rk_coefs(state, t_step, coef);
        //state[0] += t_step;
        //state[1] += *temp;
        //state[2] += *(temp+1);
        std::cout << &coef << &state << std::endl;
    }
	return 0;
}
