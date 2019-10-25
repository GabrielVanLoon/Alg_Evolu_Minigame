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
    in.set(0,0,200);
    in.set(1,0,400);
    in.set(2,0,600);
    in.set(3,0,800);
    for(int i=0; i < 4; i++)
        in.set(i,1,1); // Biases

    Matrix out = Matrix(4,1);
    out.set(0,0,150);
    out.set(1,0,350);
    out.set(2,0,550);
    out.set(3,0,750);


    Population pop  = Population(100);
    pop.genes_range = 10;

    pop.start();
    pop.train(100, in, out);
    //printf("\n\nRede final...\n");
    //pop.print(true);
    pop.best_ind.print();
    pop.print_best_output(in);
    

}

