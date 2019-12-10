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
        
        bool apply_multiply = (pop->std_score > 3000);

        for(int i = 1; i < pop->size(); i++){
            mut_all_layers(pop->ind[i], pop->mutation_rate, pop->mutation_range,
                pop->genes_precision, pop->mutation_multiply, apply_multiply);
        }
    }

    void mutate_one(Population *pop){
        if(pop == NULL || pop->size() < 1) 
            return;
        
        bool apply_multiply = (pop->std_score > 3000);

        for(int i = 1; i < pop->size(); i++){
            mut_one_layer(pop->ind[i], pop->mutation_rate, pop->mutation_range,
                pop->genes_precision, pop->mutation_multiply, apply_multiply);
        }
    }

    void mutate_prob(Population *pop, int prob){
        if(pop == NULL || pop->size() < 1) 
            return;

        bool apply_multiply = (pop->std_score > 3000);
        
        for(int i = 1; i < pop->size(); i++){
            if(rand()&100 < prob)
                mut_all_layers(pop->ind[i], pop->mutation_rate, pop->mutation_range,
                    pop->genes_precision, pop->mutation_multiply, apply_multiply);
        }
    }

/**
 * Mutations
 */
    void mut_all_layers(Individual &ind, int rate, int range, int precision, double multiply, bool apply_multiply){
        for(int layer = 0; layer < ind.weights.size(); layer++){
            for(int i = 0; i < ind.weights[layer].rows; i++ ){
                for(int j = 0; j < ind.weights[layer].cols; j++ ){
                    
                    if( rand()%100 > rate) 
                        continue;

                    // Obs: Aplicar multiply excessivamente pode acarretar na perda de variância dos genes
                    if(apply_multiply)
                        ind.weights[layer].values[i][j] += random_genef(range, precision) * multiply;
                    else
                        ind.weights[layer].values[i][j] += random_genef(range, precision);
                    
                }
            }
        }
    }

    void mut_one_layer(Individual &ind, int rate, int range, int precision, double multiply, bool apply_multiply){
        int layer = rand()%ind.size();
        for(int i = 0; i < ind.weights[layer].rows; i++ ){
            for(int j = 0; j < ind.weights[layer].cols; j++ ){  
                if( rand()%100 > rate) 
                    continue;

                if(apply_multiply)
                    ind.weights[layer].values[i][j] += random_genef(range, precision) * multiply;
                else
                    ind.weights[layer].values[i][j] += random_genef(range, precision);
            }
        }
    }