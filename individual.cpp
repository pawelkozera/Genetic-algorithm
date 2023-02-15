#include "individual.h"
#include <iostream>

Individual::Individual() {
    int bit;
    for (int i = 0; i < bit_amount; i++) {
        bit = rand() % 2;
        parameters.push_back(bit);
    }

    K = T = damping_factor = 0;
}

void Individual::assessment() {
    int N = 20;
    long double result;
    long double model_h;
    long double algorithm_h;
    long double model_g;
    long double algorithm_g;
    long double sum_h = 0;
    long double sum_g = 0;

    for (double t = 0; t < N; t++) {
        model_h = assessment_h(t);
        algorithm_h = assessment_h(t, T, K, damping_factor);
        sum_h += (model_h - algorithm_h) * (model_h - algorithm_h);

        model_g = assessment_g(t);
        algorithm_g = assessment_g(t, T, K, damping_factor);
        sum_g += (model_g - algorithm_g) * (model_g - algorithm_g);
    }

    result = sum_h/N + sum_g/N;

    J = result;
}

double Individual::assessment_h(double t, double T_parameter, double K_parameter, double damping_factor_parameter) {
    double first_part = 1-(exp(-(damping_factor_parameter)/(T_parameter)*t))/(sqrt(1-damping_factor_parameter*damping_factor_parameter));
    double arctg_part = atan(sqrt(1-damping_factor_parameter*damping_factor_parameter)/damping_factor_parameter);
    double second_part = sin(sqrt(1-damping_factor_parameter*damping_factor_parameter)/T_parameter*t + arctg_part);
    double result = K_parameter*(first_part*second_part)*1;

    return result;
}

double Individual::assessment_g(double t, double T_parameter, double K_parameter, double damping_factor_parameter) {
    double first_part = (K_parameter)/(T_parameter*sqrt(1-damping_factor_parameter*damping_factor_parameter));
    double second_part = exp(-damping_factor_parameter/T_parameter*t);
    double third_part = sin(sqrt(1-damping_factor_parameter*damping_factor_parameter)/T_parameter*t);
    double result = (first_part*second_part*third_part)*1;

    return result;
}

void Individual::print_parameters() {
    for (int i = 0; i < 15; i++) {
        std::cout << parameters[i];
    }
    std::cout << std::endl;
}

void Individual::bit_negation(int bit) {
    if (parameters[bit] == 1)
        parameters[bit] = 0;
    else
        parameters[bit] = 1;
}

void Individual::binary_to_decimal_parameters() {
    std::vector<int> K_decimal;
    std::vector<int> T_decimal;
    std::vector<int> damping_factor_decimal;

    for (int i = 0; i < parameters.size(); i++) {
        if (i <= 4) K_decimal.push_back(parameters[i]);
        else if (i > 4 && i <= 7) T_decimal.push_back(parameters[i]);
        else damping_factor_decimal.push_back(parameters[i]);
    }

    K = binary_to_decimal(K_decimal);
    T = binary_to_decimal(T_decimal);
    if (T == 0) T += 0.01;
    damping_factor = double(binary_to_decimal(damping_factor_decimal))/127;
    if (damping_factor == 0) damping_factor = 0.000001;
}

int Individual::binary_to_decimal(const std::vector<int> &bin) {
    int decimal = 0;
    int base = 1;
    for (int i = bin.size() - 1; i >= 0; i--) {
        if (bin[i] == 1) {
            decimal += base;
        }
        base *= 2;
    }
    return decimal;
}

