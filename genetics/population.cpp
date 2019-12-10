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
    
    this->enviroment_changed = true;
}

void Population::start(){
    if(this->size() < 1) return;
        
    // Arquitetura padrão trivial para caso nenhuma tenha sido selecionada
    std::vector<int> configurations({2, 1});
    for(int i = 0; i < this->size(); i++)
        this->start(configurations);

    this->enviroment_changed = true;
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

    // Trick: Para evitar demora na busca de lugares ótimos, os 3 piores serão uma cópia do best
    this->ind[this->size()-1] = this->ind[0];
    this->ind[this->size()-2] = this->ind[0];
    // this->ind[this->size()-3] = this->ind[0];

    // 3º Calcular performance e dados gerais da geração e exibindo na tela
    this->avg_score = 0;
    for(int i = 0; i < this->size(); i++)
        this->avg_score += this->ind[i].score;
    this->avg_score = this->avg_score/this->size();

    this->std_score = 0;
    for(int i = 0; i < this->size(); i++)
        this->std_score += (this->ind[i].score-this->avg_score)*(this->ind[i].score-this->avg_score);
    this->std_score = std::sqrt(this->std_score/(this->size()-1));

    printf("Gen: %02d,\tAtual: %d,\tBest: %d,\tAvg: %lu,\tStd: %lu,\n", this->epoch, this->ind[0].score, this->best_ind.score, this->avg_score, this->std_score);
    printf("Top 5: %d\t%d\t%d\t%d\t%d\n", this->ind[0].score, this->ind[1].score, this->ind[2].score, this->ind[3].score, this->ind[4].score);

    // Verificando se houve alguma melhoria
    if(this->enviroment_changed || this->best_ind.score > this->ind[0].score){
        printf("Melhor individuo atualizado...\n");
        this->best_ind       = this->ind[0];
        this->best_ind_epoch = this->epoch;
        
        this->enviroment_changed     = false;
        this->epochs_without_improve = 0;
        this->mutation_multiply      = 1.0;
        this->mutation_divider      = 1.0;
    } else {
        this->epochs_without_improve++;
    }

    // 4º Realizando os Crossovers
    // 5º Realizando as Mutações

    // Se a variância de genes for muito baixa, não aplica a multiply pois ela prejudica
    // a geração de individuos diferentes
    int exp = 0;
    if(this->epochs_without_improve > 10){
        exp = std::min(4, (this->epochs_without_improve)/10);
        this->mutation_multiply = std::pow(0.1, exp);
    }

    // Verifica se não faz muito tempo que o melhor individuo é melhorado
    if( this->epochs_without_improve > 100){
        //int temp = this->mutation_rate;
        this->mutation_rate = 2;
        cross_best_vs_all(this);
        mutate_one(this);
        //this->mutation_rate = temp;
    
    } else if( this->epochs_without_improve > 60){
        //int temp = this->mutation_rate;
        this->mutation_rate = 5;
        cross_best_vs_all(this);
        mutate_all(this);
        //this->mutation_rate = temp;
    
    } else {
        cross_best_vs_all(this);
        mutate_all(this);
    }
    
    // Print CSV com Best e média
    printf("Mutation Multiply: %d\tEpochs Without Improve: %d\n", exp, this->epochs_without_improve);
    printf("\n");

    return true;
}
