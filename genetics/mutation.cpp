#include "population.h"
#include "mutation.h"
#include <stdlib.h>
#include <iostream>

/**
 * Individual Selection Algorithms
*/
    void mutate_all(Population *pop){
        if(pop == NULL || pop->size() < 1) 
            return;

        for(int i = 1; i < pop->size(); i++){
            mut_all_layers(pop->ind[i], pop->mutation_rate, pop->mutation_range, pop->mutation_multiply, pop->genes_precision);
        }
    }

    void mutate_prob(Population *pop, int prob){
        if(pop == NULL || pop->size() < 1) 
            return;

        for(int i = 1; i < pop->size(); i++){
            if(rand()&100 < prob)
                mut_all_layers(pop->ind[i], pop->mutation_rate, pop->mutation_range, pop->mutation_multiply, pop->genes_precision);
        }
    }

/**
 * Mutations
 */
    void mut_all_layers(Individual &ind, int rate, int range, int multiply, int precision){
        for(int layer = 0; layer < ind.weights.size(); layer++){
            for(int i = 0; i < ind.weights[layer].rows; i++ ){
                for(int j = 0; j < ind.weights[layer].cols; j++ ){
                    
                    if( rand()%100 > rate) 
                        continue;

                    ind.weights[layer].values[i][j] += random_genef(range, precision)/((double)multiply);
                }
            }
        }
    }

    void mut_one_layer(Individual &ind, int rate, int range, int multiply, int precision){
        int layer = rand()%ind.size();
        for(int i = 0; i < ind.weights[layer].rows; i++ ){
            for(int j = 0; j < ind.weights[layer].cols; j++ ){  
                if( rand()%100 > rate) 
                    continue;

                ind.weights[layer].values[i][j] += random_genef(range, precision)/((double)multiply);
            }
        }
    }