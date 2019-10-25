#ifndef POPULATION_H
    #define POPULATION_H

    #include "individual.h"
    #include <vector>

    class Population {
        public:
            /**
             * Parâmetros da População
             * @param ind - vetor de individups da população
             * @param best_ind - melhor individuo da população
             * @param epoch - época atual da população
             * @param avg_score - pontuação média da época atual
             * @param std_score - desvio padrão da época atual
             */
            std::vector<Individual> ind;
            Individual best_ind;
            int epoch;
            int avg_score; 
            int std_score;
            
            /**
             * Parâmetros de Configuração
             * @param genes_range - Range em que os pesos da rede serão iniciados
             * @param mutation_rate - Chance porcentual de mutação de cada indivíduo
             * @param mutation_range
             * @param mutation_multiply
             */
            int genes_range;
            int mutation_rate;
            int mutation_range;
            int mutation_multiply;

            /**
             * Population();
             * Inicia uma população com o tamanho padrão de 10 individuos.
             */
            Population();

            /**
             * Population(int size);
             * Inicia uma população
             * @param size quantidade de individuos na pop.
             */ 
            Population(int size);

            /**
             * void start();
             * Inicia os individuos da população com valores aleatórios.
             * É necessário que os parâmetros de configuração já tenham sido
             * atribuidos corretamente.
             */
            void start();

            /**
             * int size();
             * Retorna a quantidade de individuos que existe na população
             */
            int size();
            
            /**
             * void print();
             * Exibe o score e, caso solicitado, os individuos da população
             */
            void print(bool show_ind);

            /**
             * void train(int epochLimit);
             * @ TODO
             */
            void train(int epochLimit);

    };

#endif