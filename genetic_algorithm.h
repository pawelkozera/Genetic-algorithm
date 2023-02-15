#ifndef GENETIC_ALGORITHM_H_INCLUDED
#define GENETIC_ALGORITHM_H_INCLUDED

#include <vector>
#include <fstream>
#include "individual.h"

class Genetic_algorithm {
public:
    std::vector<Individual> population;
    std::vector<Individual> selected_population;
    int population_size;
    int iteration_number;
    double crossover_probability;
    double mutation_probability;
    int bit_amount = 15;

    void initialization();
    Genetic_algorithm(int population_s, int iteration_n, int crossover_p, int mutation_p);
    void tournament_selection();
    void crossover(Individual first, Individual second);
    void mutation(Individual *individual);
    void best_individual();
    double draw_probability();
};

#endif // GENETIC_ALGORITHM_H_INCLUDED
