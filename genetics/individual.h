#ifndef INDIVIDUAL_H
    #define INDIVIDUAL_H

    #include "../classes/matrix.h"
    #include "../classes/neural-network.h"

    /**
     * @class Individual
     */
    class Individual : public NeuralNetwork {
        public:
            int  score;

            ~Individual();
    };

    /**
     * Functions
     */
    bool compare_ind(Individual lhs, Individual rhs);

    int create_gene(int range);

    Individual create_ind(int arch_size, int* configurations, int range);




#endif