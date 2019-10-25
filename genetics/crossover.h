#ifndef POPULATION_H
    #include <population.h>
#endif

#ifndef CROSSOVERS_H
    #define CROSSOVERS_H

    /**
     * Parent Selection Algorithms
     */
    void cross_best_vs_all(Population &pop);

    void cross_tournament_selection(Population &pop);

    void cross_roulette(Population &pop);

    /**
     * Crossover method
     */
    Individual crossover(const Individual &p1, const Individual &p2);


#endif
