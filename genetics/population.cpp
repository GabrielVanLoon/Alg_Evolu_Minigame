#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <iostream>
#include <algorithm>
#include <vector>

#include "../network/matrix.h"
#include "population.h"
#include "individual.h"
#include "crossover.h"
#include "mutation.h"

Population::Population(){
    this->epoch = 0;
    this->ind.resize(10);
}

Population::Population(int size){
    this->epoch = 0;
    this->ind.resize(size);
}

void Population::start(const std::vector<int> &configurations){
    if(this->size() < 1) return;
        
    srand(time(NULL));
    for(int i = 0; i < this->size(); i++)
        this->ind[i] = Individual(configurations, this->genes_range, this->genes_precision);
}

void Population::start(){
    if(this->size() < 1) return;
        
    // Arquitetura padrão trivial para caso nenhuma tenha sido selecionada
    std::vector<int> configurations({2, 1});
    for(int i = 0; i < this->size(); i++)
        this->start(configurations);
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

void Population::print_best_output(const Matrix &input){
    if(this->epoch == 0){
        printf("Error: essa população ainda não recebeu nenhum treinamento!");
        return;
    }
    
    if(input.cols != this->best_ind.weights[0].rows){
        printf("Error: por favor, verifique se a matrix de input está configurada corretamente!\n");
        return;
    }

    printf("Output melhor indivíduo:\n");
    this->best_ind.run(input);
    Matrix out = this->best_ind.get_output();
    out.print();
}

bool Population::train(int iterations, const Matrix &input, const Matrix &output){
    /**
     * Verificando se a matrix de input e output estão com as dimensões 
     * corretas para serem executadas.
     */ 
    if(input.cols != this->ind[0].weights[0].rows){
        printf("Train error: por favor, verifique se a matrix de input está configurada corretamente!\n");
        return false;
    }

    if(output.cols != this->ind[0].weights[this->ind[0].weights.size()-1].cols){
        printf("Train error: por favor, verifique se a matrix de output está configurada corretamente!\n");
        return false;
    }

    /**
     * Processos de cada iteração:
     * 1º Calcular o score de cada indivíduo
     * 2º Ordenar os individuos do melhor para o pior
     * 3º Calcular performance geral e verificar se houve melhoria
     * 4º Crossover
     * 5º Mutações nos 
     */
    for(int it = 0; it <= iterations; it++){
        int totalScore = 0;
        this->epoch   += 1;

        // 1º Calcular o score de cada indivíduo
        for(int p = 0; p < this->size(); p++){
            this->ind[p].run(input);
            this->ind[p].score = this->ind[p].get_loss(output);
            totalScore        += this->ind[p].score;
        }

        // 2º Ordenar os individuos do melhor para o pior
        std::sort(this->ind.begin(), this->ind.end(), compare_individuals_desc);

        // 3º Calcular performance geral e verificar se houve melhoria
        this->avg_score = totalScore/this->size();
        printf("Geração %02d/%02d\tScore atual: %d\tScore Médio: %d\n", it, iterations, this->ind[0].score, this->avg_score);

        if(this->epoch <= 1 || this->best_ind.score > this->ind[0].score){
            printf("Melhor individuo atualizado...\n");
            this->best_ind = this->ind[0];
        }

        // Para o loop de iterações para garantir que o vector de individuos
        // seja retornado com os scores calculados e ordenado corretamente.
        if(it == iterations) break;

        // Não há melhora a muito tempo? Aumenta a taxa de mutacao

        // Realizando o Cross-Over da populacao
        // cross_best_vs_all(this);
        cross_tournament_selection(this);

        // Realizando as Mutacoes
        mutate_all(this);

        // Insira genocidios se houver
    }

}

bool Population::itrain(){
    this->epoch   += 1;

    // 1º Calcular o score de cada indivíduo
    // No treino iterativo os Scores são definidos antes da chamada dessa função
    // isso permite que o cálculo dos scores seja dinâmico e de responsabilidade do usuário.

    // 2º Ordenar os individuos do melhor para o pior
    std::sort(this->ind.begin(), this->ind.end(), compare_individuals_desc);

    // 3º Calcular performance geral e verificar se houve melhoria
    printf("Geração %02d\tScore atual: %d\tMelhor Score: %d\n", this->epoch, this->ind[0].score, this->best_ind.score);
    if(this->epoch <= 1 || this->best_ind.score > this->ind[0].score){
        printf("Melhor individuo atualizado...\n");
        this->best_ind       = this->ind[0];

        this->best_ind_epoch = this->epoch;
        this->epochs_without_improve = 0;
        this->mutation_multiply      = 1;
    } else {
        this->epochs_without_improve++;
    }

    // 4º Realizando os Crossovers
    // 5º Realizando as Mutações

    // Verifica se não faz muito tempo que o melhor individuo é melhorado
    if(this->epochs_without_improve%3 > 0){
        this->mutation_multiply = pow(10, this->epochs_without_improve%3);
        cross_best_vs_all(this);
        mutate_all(this);
    } else {
        cross_tournament_selection(this);
        mutate_all(this);
    }
    
    return true;
}
