/**
 * Copyright 2019 - Gabriel Van Loon  
 * 
 * Algoritmos Genéticos + RN - Shooter Minigame
 * 
 */

#include <iostream>
#include <stdlib.h>

#include "classes/matrix.h"
#include "classes/neural-network.h"
#include "genetics/population.h"
#include "genetics/crossover.h"


int main(){

    Population pop = Population(100);
    pop.start();
    //pop.print();
    pop.train(100);
    
    printf("\nFIM DO TREINO *******************\n");
    //pop.print();

    pop.kill();
    
}