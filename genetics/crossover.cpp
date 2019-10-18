#include "population.h"
#include "crossover.h"
#include <stdlib.h>
#include <iostream>

/**
 * Parent Selection Algorithms
 */
void cross_best_vs_all(Population *pop){

    // Realiza o crossover do melhor individio (index 0) com todos os restantes.
    Individual* p1 = &(pop->ind[0]);
    for(int i = 1; i < pop->size; i++){
        Individual* p2 = &(pop->ind[i]);
        Individual child = crossover(p1, p2);

        p2->w.clear();
        p2->w = child.w;
    }

}

void cross_tournament_selection();

void cross_roulette();

/**
 * Crossover method
 */
Individual crossover(Individual *p1, Individual *p2){

    // 1ª Etapa - Gerando um filho com as mesmas configurações
    //            que os pais.
    int configurations[p1->size+1];
    configurations[0] = p1->w[0].rows;
    for(int c = 1; c <= p1->size; c++){
        configurations[c] = p1->w[c-1].cols;
    }

    Individual child = create_ind(p1->size, configurations, 2);

    // 2ª Etapa - Percorre cada peso de cada camada e decide se irá herdar
    //            do parent p1 ou p2
    for(int layer = 0; layer < p1->size; layer++){
        for(int l = 0; l < p1->w[layer].rows; l++){
            for(int c = 0; c < p1->w[layer].cols; c++){
                child.w[layer].m[l][c] = (rand()%100 < 50) ? 
                      p1->w[layer].m[l][c] 
                    : p2->w[layer].m[l][c];

            }
        }
    }

    return child;
}

