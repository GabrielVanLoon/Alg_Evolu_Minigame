#include <iostream>
#include <stdlib.h>
#include <vector>
#include <array>
#include "neural-network.h"
#include "matrix.h"


NeuralNetwork::NeuralNetwork(){
    // Do Nothing.
}

NeuralNetwork::NeuralNetwork(const std::vector<int> *configurations){
    // Gerando as Layers
    // [i==0] >> Neurons na camada de entrada
    // [i-0]  >> Neurons na camada anterior   i = 1 .. arch_size
    // [i]    >> Neurons na camada atual
    for(int i = 1; i < configurations->size(); i++){
        this->weights.push_back( Matrix((*configurations)[i-1], (*configurations)[i]) );
    }
}

void NeuralNetwork::push_layer(const Matrix *layer){
    this->weights.push_back(Matrix(*layer));
}

void NeuralNetwork::run(const Matrix &input){
    Matrix results = input;
    for(unsigned i = 0; i < this->weights.size(); i++){
        results = results * this->weights[i];
    }
    this->output = results;
}

Matrix NeuralNetwork::get_output(){
    return this->output;
}

int NeuralNetwork::get_loss(const Matrix &outExpected){
    
    if(this->output.cols != outExpected.cols || this->output.rows != outExpected.rows)
        return 99999999;

    int loss = 0;
    for(int i = 0; i < outExpected.rows; i++){
        for(int j = 0; j < outExpected.cols; j++){
            // LOSS por enquanto será uma MSE (Mean Squared Error)
            loss += abs((this->output.values[i][j]-outExpected.values[i][j]));
        }
    }

    return loss/(outExpected.cols*outExpected.rows);
}

int NeuralNetwork::size(){
    return this->weights.size();
}

void NeuralNetwork::print(){
    for(int i = 0; i < this->size(); i++){
        printf("Hidden Layer %d neuronio(s)\n", this->weights[i].cols);
        this->weights[i].print();
    }
}