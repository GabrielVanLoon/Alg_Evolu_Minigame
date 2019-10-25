#include "population.h"
#include "crossover.h"
#include <stdlib.h>
#include <iostream>

/**
 * Parent Selection Algorithms
 */
void cross_best_vs_all(Population *pop){

    // Realiza o crossover do melhor individio (index 0) com todos os restantes.
    Individual p1 = pop->ind[0];
    for(int i = 1; i < pop->size(); i++){
        Individual p2    = pop->ind[i];
        Individual child = crossover(p1, p2);
        pop->ind[i]       = child;
    }
}

void cross_tournament_selection(Population *pop){

    // Realiza um sorteio dentre todos os membros para escolher
    // ambos os pais de cada filho.
    Individual p1, p2;
    std::vector<Individual> children;

    children.resize(pop->size());
    children[0] = pop->ind[0];

    for(int c = 1; c < pop->size(); c++){
        p1 = pop->ind[rand()%pop->size()]; 
        p2 = pop->ind[rand()%pop->size()];
        children[c] = crossover(p1,p2);
    }

    for(int i = 1; i < pop->size(); i++){ 
        pop->ind[i] = children[i];
    }
}

void cross_roulette(Population *pop);

/**
 * Crossover method
 */
Individual crossover(const Individual &p1, const Individual &p2){

    // 1ª Etapa - Gerando um filho com as mesmas configurações
    //            que os pais.
    std::vector<int> configurations;
    configurations.push_back(p1.weights[0].rows);

    for(int c = 1; c <= p1.weights.size(); c++){
        configurations.push_back(p1.weights[c-1].cols);
    }

    Individual child = Individual(configurations, 2);

    // 2ª Etapa - Percorre cada peso de cada camada e decide se irá herdar
    //            do parent p1 ou p2
    for(int layer = 0; layer < p1.weights.size(); layer++){
        for(int l = 0; l < p1.weights[layer].rows; l++){
            for(int c = 0; c < p1.weights[layer].cols; c++){
                child.weights[layer].values[l][c] = (rand()%100 < 50) ? 
                      p1.weights[layer].values[l][c] 
                    : p2.weights[layer].values[l][c];
            }
        }
    }

    return child;
}

