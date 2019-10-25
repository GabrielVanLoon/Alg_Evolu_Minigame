#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "individual.h"
#include "individual.h"

Individual::Individual(){
    
}

Individual::Individual(const std::vector<int> &configurations, int range){  
    for(int i = 1; i < configurations.size(); i++){
        // Gerando a hidden layer da rede neural.
        // [i==0] >> Neurons na camada de entrada
        // [i-0]  >> Neurons na camada anterior   i = 1 .. arch_size
        // [i]    >> Neurons na camada atual
        Matrix m = Matrix(configurations[i-1], configurations[i]);
        
        // Gerando os valores dentro do range
        for(int l = 0; l < configurations[i-1]; l++){
            for(int c = 0; c < configurations[i]; c++){
                m.set(l,c, random_gene(range));
            }
        }

        // Insere a hidden layer e segue a vida
        this->push_layer(&m);
    }
}


bool compare_individuals(Individual lhs, Individual rhs) { 
    return lhs.score < rhs.score; // Ordena decrescente
}

int random_gene(int range){
    return (rand()%(2*range))-range;
}
