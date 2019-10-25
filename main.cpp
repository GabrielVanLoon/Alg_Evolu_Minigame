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

    Population pop  = Population(3);
    pop.genes_range = 1;

    pop.start();
    pop.train(10);
    printf("\n\nRede final...\n");
    pop.print(true);
    
}

