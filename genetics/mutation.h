#ifndef POPULATION_H
    #include <population.h>
#endif

#ifndef MUTATIONS_H
    #define MUTATIONS_H

    /**
     * Individual Selection Algorithms
     */
        /**
         * void mutate_all(Population *pop);
         * Realiza o algoritmo de mutação em TODOS os individuos da geração com
         * exceção do melhor de todos.
         */
        void mutate_all(Population *pop);

        /**
         * void mutate_all(Population *pop);
         * Percorre todos os individuos e possui uma chance aleatória de realizar
         * ou não a mutação em cada um dos individuos.
         */
        void mutate_prob(Population *pop, int prob);

    /**
     * Mutations
     */
        /**
         * void mut_all_layers(Individual &ind, int rate, int range, int multiply);
         * Percorre toos os pesos de todas as camadas e possui uma chance de aleatóriamente
         * modificar o valor no intervalo [-range*multiply,+-range*multiply].
         */
        void mut_all_layers(Individual &ind, int rate, int range, int multiply, int precision);

        /**
         * void mut_one_layer(Individual &ind, int rate, int range, int multiply);
         * Seleciona aleatoriamente  uma camada e percorre todos os  seus pesos. 
         * Para cada peso, possui uma chance aleatória de modificar o valor
         * no intervalo [-range*multiply,+-range*multiply].
         */
        void mut_one_layer(Individual &ind, int rate, int range, int multiply, int precision);

#endif
