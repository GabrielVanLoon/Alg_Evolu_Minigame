#ifndef INDIVIDUAL_H
    #define INDIVIDUAL_H

    #include "../network/matrix.h"
    #include "../network/neural-network.h"

    /**
     * @class Individual
     */
    class Individual : public NeuralNetwork {
        public:
            int  score;
            
            Individual();
            
            /**
             * Individual(int arch_size, int* configurations, int range);
             * Cria um novo individuo tal que:
             * @param range: os pesos da rede serão iniciados aleatoriamente
             * no intervalo I = [-range,range]
             * @param configurations: vetor que irá definir a quantidade de 
             * neurônios que cada layer possuiŕia, sendo que:
             * [i==0] >> Neurons na camada de entrada
             * [i-1]  >> Neurons na camada anterior   i = 1 .. arch_size
             * [i]    >> Neurons na camada atual
             */
            Individual(const std::vector<int> &configurations, int range);
    };

    /**
     * bool compare_individuals(Individual lhs, Individual rhs);
     * Ordenar dois indivíduos em ordem decrescente baseado em seus scores.
     * Retorna true se (lhs.score < rhs.score)
     */
    bool compare_individuals(Individual lhs, Individual rhs);

    /**
     * int random_gene(int range);
     * Gera um valor aleatório entre o intervalo I = [-range, range]
     */
    int random_gene(int range);

#endif