#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <algorithm>
#include <vector>

#include "../network/matrix.h"
#include "population.h"
#include "individual.h"
#include "crossover.h"

Population::Population(){
    this->ind.resize(10);
}

Population::Population(int size){
    this->ind.resize(size);
}

void Population::start(){
    if(this->size() < 1) return;
        
    srand(time(NULL));

    // Definindo qual será a arquitetura utilizada nas redes.
    std::vector<int> configurations({2, 3, 1});
    
    for(int i = 0; i < this->size(); i++)
        this->ind[i] = Individual(configurations, this->genes_range);
}

int Population::size(){
    return this->ind.size();
}

void Population::print(bool show_ind){
     for(int i = 0; i < this->size(); i++){
        printf("Ind.[%d]. \tScore: %d.\n", i+1, this->ind[i].score);
        if(show_ind) this->ind[i].print();
        std::cout << std::endl;
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
        for(int p = 0; p < this->size(); p++){
            this->ind[p].run(&in);
            this->ind[p].score = this->ind[p].get_loss(&out);
            totalScore        += this->ind[p].score;
        }

        // Ordenando a população do melhor para o pior
        std::sort(this->ind.begin(), this->ind.end(), compare_individuals);

        // Calcula a performance da populacao como bestScore, avgScore, strScore
        this->avg_score   = totalScore/this->size();
        printf("Geração %02d/%02d\t\tScore atual: %d\n", y, epochLimit, this->ind[0].score);

        // Houve melhora? Se sim atualiza o melhor individuo
        if(this->epoch == 0 || this->best_ind.score < this->ind[0].score){
            this->best_ind = this->ind[0];
        }

        // Não há melhora a muito tempo? Aumenta a taxa de mutacao

        // Realizando o Cross-Over da populacao
        // cross_best_vs_all(this);
        // cross_tournament_selection(this);

        // Realizando as Mutacoes

        // Insira genocidios se houver
    }

}


