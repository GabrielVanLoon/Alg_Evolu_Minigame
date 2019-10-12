#ifndef NEURAL_NETWORK_H
    #define NEURAL_NETWORK_H
    
    #include <vector>
    #include "matrix.h"
    
    /**
     * @class NeuralNetwork
     */
    class NeuralNetwork {
        public:
            int size;               // num. of transforms
            std::vector<Matrix> w;  // weights  
            Matrix input;           // output Matrix
            Matrix output;          // input  Matrix

            NeuralNetwork();

            void pushLayer(Matrix hidden);

            void setInput(Matrix in);

            Matrix getOutput();

            int getLoss(Matrix outExpected);

            void run();

            void print();
    };
#endif