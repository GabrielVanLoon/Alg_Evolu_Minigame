/**
 * Copyright 2019 - Gabriel Van Loon  
 * 
 * Algoritmos Genéticos + RN - Shooter Minigame
 * 
 */

#include <iostream>
#include <stdlib.h>
#include "network/matrix.h"
#include "network/neural-network.h"
#include "genetics/population.h"


int main(){

    /** 1ª Etapa
     *  - Definir qual é o valor de entrada
     *  - Definir qual a saída esperada
     */
    Matrix in = Matrix(4,2);
    in.set(0,0,2);
    in.set(1,0,5);
    in.set(2,0,10);
    in.set(3,0,12);
    for(int i=0; i < 4; i++)
        in.set(i,1,1); // Biases

    Matrix out = Matrix(4,1);
    out.set(0,0,2*10);
    out.set(1,0,5*10);
    out.set(2,0,10*10);
    out.set(3,0,12*10);


    Population pop  = Population(100);
    pop.genes_range = 5;
    pop.mutation_rate = 30;
    pop.mutation_range = 10;
    pop.mutation_multiply = 1;

    pop.start();
    pop.train(10, in, out);
    printf("\n\nRede final...\n");
    //pop.print(true);
    pop.best_ind.print();
    pop.print_best_output(in);

}

