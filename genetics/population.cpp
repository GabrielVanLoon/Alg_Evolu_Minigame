#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <time.h>
#include "../classes/matrix.h"
#include "population.h"
#include "crossover.h"

Population::Population(){
    this->size  = 50;
    this->epoch = 0;
    this->genesRange       = 100;
    this->mutationRate     = 1;
    this->mutationMultiply = 1;
    this->ind = NULL;
}

Population::Population(int populationSize){
    this->size  = populationSize;
    this->epoch = 0;
    this->genesRange       = 100;
    this->mutationRate     = 1;
    this->mutationMultiply = 1;
    this->ind = NULL;
}

Population::~Population(){
    this->kill();
}

void Population::start(){
    if(this->ind != NULL || this->size <= 0)
        return;

    srand(time(NULL));

    // Definindo qual será a arquitetura utilizada nas redes.
    int arch_size = 2;
    int configs[3] = {2, 3, 1};
    
    this->ind = (Individual*) malloc(this->size*sizeof(Individual));
    for(int i = 0; i < this->size; i++){
        this->ind[i] = create_ind(arch_size, configs, this->genesRange);
    }
}

void Population::train(int epochLimit){

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
    out.set(0,0,0);
    out.set(1,0,0);
    out.set(2,0,0);
    out.set(3,0,0);

    for(int y = 0; y < epochLimit; y++){
        
        int totalScore = 0;
        this->epoch   += 1;

        // Calculando os scores da população
        for(int p = 0; p < this->size; p++){
            this->ind[p].setInput(in);
            this->ind[p].run();
            this->ind[p].score = this->ind[p].getLoss(out);
            totalScore      += this->ind[p].score;
        }

        // Ordenando a população do melhor para o pior
        std::sort(this->ind, this->ind+this->size, compare_ind);

        // Calcula a performance da populacao como bestScore, avgScore, strScore
        this->bestScore = this->ind[0].score;
        this->avgScore  = totalScore/this->size;
        printf("Score %d/%d: %lf\n", y, epochLimit, this->bestScore);

        // Houve melhora? Se sim atualiza o melhor individuo
        if(this->epoch == 0 || this->best.score < this->ind[0].score){
            this->best = this->ind[0];
        }

        // Não há melhora a muito tempo? Aumenta a taxa de mutacao

        // Realizando o Cross-Over da populacao
        // cross_best_vs_all(this);
        cross_tournament_selection(this);

        // Realizando as Mutacoes

        // Insira genocidios se houver


    }

}

void Population::kill(){
    if(this->ind != NULL){ 
        for(int i = 0; i < this->size; i++){
            this->ind[i].~Individual();
        }
    
        free(this->ind);
        this->ind = NULL;
    }
}

void Population::print(){
     for(int i = 0; i < this->size; i++){
        printf("Score: %d.\n", this->ind[i].score);
        this->ind[i].print();
        std::cout << std::endl;
    }
}