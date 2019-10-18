#ifndef POPULATION_H
    #include <population.h>
#endif

#ifndef CROSSOVERS_H
    #define CROSSOVERS_H

    /**
     * Parent Selection Algorithms
     */
    void cross_best_vs_all(Population*);

    void cross_tournament_selection(Population*);

    void cross_roulette(Population*);

    /**
     * Crossover method
     */
    Individual crossover(Individual *p1, Individual *p2);


#endif
