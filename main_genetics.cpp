/**
 * Copyright 2019 - Gabriel Van Loon  
 * 
 * Algoritmos Genéticos + RN - Shooter Minigame
 * 
 */

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "network/matrix.h"
#include "network/neural-network.h"
#include "genetics/population.h"


int main(){
    
    // seed start
    srand(time(NULL));

    Matrix X = Matrix(32,2);
    Matrix Y = Matrix(32,1);

    for(int i = 0; i < 32; i++){
        X.set(i, 0, rand()%15000);
        X.set(i, 1, 1); // bias values

        int tempoVoo = X.values[i][0]/5;
        Y.set(i, 0, (X.values[i][0])/tempoVoo);    
    }

    X.print();

    Population pop  = Population(100);
    pop.genes_range       = 100;
    pop.mutation_rate     = 30;
    pop.mutation_range    = 10;
    pop.mutation_multiply = 1;

    pop.start();
    pop.train(100, X, Y);
    printf("\n\nRede final...\n");
    
    pop.print_best_output(X);
    printf("\nOutput Esperado:");
    Y.print();

    // //pop.print(true);
    printf("\nEstrutura do melhor indivíduo:\n");
    pop.best_ind.print();
}

