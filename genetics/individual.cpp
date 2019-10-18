#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "individual.h"
#include "individual.h"

Individual::~Individual(){
    this->w.clear();
}

bool compare_ind(Individual lhs, Individual rhs) { 
    return lhs.score < rhs.score; // Ordena decrescente
}

int create_gene(int range){
    return (rand()%(2*range))-range;
}


Individual create_ind(int arch_size, int* configurations, int range){
    
    Individual ind = Individual();

    for(int i = 1; i <= arch_size; i++){
        // Gerando a hidden layer da rede neural.
        // [i==0] >> Neurons na camada de entrada
        // [i-0]  >> Neurons na camada anterior   i = 1 .. arch_size
        // [i]    >> Neurons na camada atual
        Matrix m = Matrix(configurations[i-1], configurations[i]);
        
        // Gerando os valores dentro do range
        for(int l = 0; l < configurations[i-1]; l++){
            for(int c = 0; c < configurations[i]; c++){
                m.set(l,c, create_gene(range));
            }
        }

        // Insere a hidden layer e segue a vida
        ind.pushLayer(m);
    }

    return ind;
}