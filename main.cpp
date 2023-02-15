#include <iostream>

#include "genetic_algorithm.h"

using namespace std;

int main()
{
    srand(time(NULL));
    Genetic_algorithm genetic_algorithm(20, 300, 0.4, 0.05);
    genetic_algorithm.initialization();

    for (int i = 0; i < genetic_algorithm.population.size(); i++) {
        genetic_algorithm.population[i].binary_to_decimal_parameters();
        genetic_algorithm.population[i].assessment();
    }

    for (int i = 0; i < genetic_algorithm.iteration_number; i++) {
        genetic_algorithm.tournament_selection();

        for (int k = 0; k < genetic_algorithm.selected_population.size(); k++) {
            genetic_algorithm.mutation(&genetic_algorithm.selected_population[k]);
        }

        for (int k = 0; k < genetic_algorithm.selected_population.size()/2; k += 2) {
            genetic_algorithm.crossover(genetic_algorithm.selected_population[k], genetic_algorithm.selected_population[k+1]);
        }

        genetic_algorithm.population = genetic_algorithm.selected_population;

        for (int i = 0; i < genetic_algorithm.population.size(); i++) {
            genetic_algorithm.population[i].binary_to_decimal_parameters();
            genetic_algorithm.population[i].assessment();
        }
    }

    genetic_algorithm.best_individual();

    return 0;
}
