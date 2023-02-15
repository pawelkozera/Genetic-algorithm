#ifndef INDIVIDUAL_H_INCLUDED
#define INDIVIDUAL_H_INCLUDED

#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <bitset>

class Individual {
public:
    long double T;
    long double K;
    long double damping_factor;
    long double J;
    int bit_amount = 15;
    /*
        K = 0 - 4
        T = 5 - 7
        wsp = 8 - 14
    */
    std::vector<int> parameters;

    Individual();
    void assessment();
    double assessment_h(double t, double T_parameter = 1, double K_parameter = 1, double damping_factor_parameter = 0.3);
    double assessment_g(double t, double T_parameter = 1, double K_parameter = 1, double damping_factor_parameter = 0.3);
    void initialization ();
    void print_parameters();
    void bit_negation(int bit);
    void binary_to_decimal_parameters();
    int binary_to_decimal(const std::vector<int> &bin);
};

#endif // INDIVIDUAL_H_INCLUDED
