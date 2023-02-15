#include "genetic_algorithm.h"
#include <iostream>

Genetic_algorithm::Genetic_algorithm(int population_s, int iteration_n, int crossover_p, int mutation_p) {
    population_size = population_s;
    iteration_number = iteration_n;
    crossover_probability = crossover_p;
    mutation_probability = mutation_p;
}

void Genetic_algorithm::initialization() {
    for (int i = 0; i < population_size; i++) {
        Individual individual = Individual();
        population.push_back(individual);
    }
}

void Genetic_algorithm::tournament_selection() {
    selected_population.clear();

    for (int i = 0; i < int(population.size()/4); i++) {
        if (population[i].J < population[i+1].J)
            selected_population.push_back(population[i]);
        else
            selected_population.push_back(population[i]);

        if (population[i+2].J < population[i+3].J)
            selected_population.push_back(population[i+2]);
        else
            selected_population.push_back(population[i+3]);
    }
    population.clear();
}

void Genetic_algorithm::crossover(Individual first, Individual second) {
    int position;
    double probability;

    do {
        probability = draw_probability();
        position = rand()%(bit_amount-1) + 1;
    } while(probability > crossover_probability);

    for (int bufor, i = position; i < bit_amount; i++) {
        bufor = first.parameters[i];
        first.parameters[i] = second.parameters[i];
        second.parameters[i] = bufor;
    }

    selected_population.push_back(first);
    selected_population.push_back(second);
}

void Genetic_algorithm::mutation(Individual *individual) {
    double probability;

    for (int i = 0; i < bit_amount; i++) {
        probability = draw_probability();
        if (probability <= mutation_probability) {
            individual->bit_negation(i);
        }
    }
}

void Genetic_algorithm::best_individual() {
    double min_j = population[0].J;
    int index = 0;

    for (int i = 0; i < int(population.size()); i++) {
        if (population[i].J < min_j) {
            min_j = population[i].J;
            index = i;
        }
    }

    std::cout << population[index].J << " K: " << population[index].K << " T: " << population[index].T << " damping factor: " << population[index].damping_factor;
}

double Genetic_algorithm::draw_probability() {
    double probability = (rand() % 101);
    return probability/100;
}
