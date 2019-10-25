#ifndef NEURAL_NETWORK_H
    #define NEURAL_NETWORK_H
    
    #include <vector>
    #include <array>
    #include "matrix.h"
    
    /**
     * @class NeuralNetwork
     */
    class NeuralNetwork {
        public:
            std::vector<Matrix> weights;  // weights  
            Matrix              output;   // input  Matrix

            /**
             * NeuralNetwork();
             * Cria a instância de uma NN sem nenhuma layer
             */
            NeuralNetwork();

            /**
             * NeuralNetwork();
             * Cria a instância de uma NN cuja estrutura será baseada da seguinte forma:
             * - configurations[0] - Neuronios de Entrada
             * - Configurations[i] - Neuronios na i-ésima layer
             */
            NeuralNetwork(const std::vector<int> *configurations);

            /**
             * void push_layer(Matrix *hidden);
             * Insere uma nova layer no fim da NN.
             */
            void push_layer(const Matrix *layer);
            
            /**
             * void run(const Matrix *input);
             * Executa a rede neural dando como parâmetro os da camada de entrada.
             */
            void run(const Matrix &input);

            /**
             * Matrix getOutput();
             * Retorna os resultados da rede neural após uma execução.
             */
            Matrix get_output();

            /**
             * int getLoss(Matrix outExpected);
             * Calcula e retorna o MSE da saída produzida comparada com um output esperado.
             */
            int get_loss(const Matrix &outExpected);

            /**
             * int size();
             * Retorna o tamanho da Network (Quantidade de Hidden Layers)
             */
            int size();

            /**
             * void print();
             * Exibe as Matrizes de peso das camadas na tela.
             */
            void print();
    };
#endif