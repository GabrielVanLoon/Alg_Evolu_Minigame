#ifndef POPULATION_H
    #include <population.h>
#endif

#ifndef CROSSOVERS_H
    #define CROSSOVERS_H

    /**
     * Parent Selection Algorithms
     */

        /**
         * void cross_best_vs_all(Population *pop);
         * O melhor individuo da geração atual faz um filho com todos
         * os individuos restantes.
         */
        void cross_best_vs_all(Population *pop);

        /**
         * void cross_tournament_selection(Population *pop);
         * Dois individuos são selecionados aleatóriamente e são
         * utilizados para gerar os filhos.
         */ 
        void cross_tournament_selection(Population *pop);

        void cross_roulette(Population *pop);

    /**
     * Crossover methods
     */

        /** 
         * Individual crossover(const Individual &p1, const Individual &p2);
         * Gera um novo individuo tal que cada gene tem 50% de chance de vir
         * de qualquer um dos parents.
         */
        Individual crossover(const Individual &p1, const Individual &p2);


#endif
