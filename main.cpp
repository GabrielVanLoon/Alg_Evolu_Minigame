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


int main(){

    std::vector<int> config = std::vector<int>({1,3,2});
    NeuralNetwork    nn = NeuralNetwork(&config);
    Matrix in = Matrix(2,1);
    std::vector<Matrix> vec;

    vec.push_back(in);
    vec[0].print();

    nn.run(&in);
    nn.get_output().print();

    for(int i = 0; i < 2; i++){
        NeuralNetwork nn2 = nn;
    }
    
}

