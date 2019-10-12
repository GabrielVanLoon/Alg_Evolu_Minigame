#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <time.h>
#include "../classes/matrix.h"
#include "population.h"

Population::Population(){
    this->size  = 50;
    this->epoch = 0;
    this->genesRange       = 100;
    this->mutationRate     = 1;
    this->mutationMultiply = 1;
    this->i = NULL;
}

Population::Population(int populationSize){
    this->size  = populationSize;
    this->epoch = 0;
    this->genesRange       = 100;
    this->mutationRate     = 1;
    this->mutationMultiply = 1;
    this->i = NULL;
}

Population::~Population(){
    if(this->i != NULL){
        this->kill();
    }
}

void Population::start(){
    if(this->i != NULL || this->size <= 0)
        return;

    srand(time(NULL));

    // Definindo qual será a arquitetura utilizada nas redes.
    int arch_size = 2;
    int configs[3] = {2, 3, 1};
    
    this->i = (Individual*) malloc(this->size*sizeof(Individual));
    for(int i = 0; i < this->size; i++){
        this->i[i] = create_ind(arch_size, configs, this->genesRange);
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
            this->i[p].setInput(in);
            this->i[p].run();
            this->i[p].score = this->i[p].getLoss(out);
            totalScore      += this->i[p].score;
        }

        // Ordenando a população do melhor para o pior
        std::sort(this->i, this->i+this->size, compare_ind);

        // Calcula a performance da populacao como bestScore, avgScore, strScore
        this->bestScore = this->i[0].score;
        this->avgScore  = totalScore/this->size;

        // Houve melhora? Se sim atualiza o melhor individuo
        if(this->epoch == 0 || this->best.score < this->i[0].score){
            this->best = this->i[0];
        }

        // Não há melhora a muito tempo? Aumenta a taxa de mutacao

        // Realizando o Cross-Over da populacao

        // Realizando as Mutacoes

        // Insira genocidios se houver
    }
}

void Population::kill(){
    if(this->i != NULL){
        free(this->i);
        this->i = NULL;
    }
}

void Population::print(){
     for(int i = 0; i < this->size; i++){
        printf("Score: %d.\n", this->i[i].score);
        this->i[i].print();
        std::cout << std::endl;
    }
}