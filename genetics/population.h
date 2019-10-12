#ifndef POPULATION_H
    #define POPULATION_H

    #include "individual.h"

    class Population {
        public:
            // Population Data
            int size, epoch;
            double avgScore, stdScore, bestScore; 
            
            // Configuration Data
            int genesRange;
            int mutationRate;
            int mutationMultiply;

            Individual best;
            Individual *i;

            Population();

            Population(int populationSize);

            ~Population();

            void start();

            void train(int epochLimit);

            void kill();

            void print();

    };

#endif