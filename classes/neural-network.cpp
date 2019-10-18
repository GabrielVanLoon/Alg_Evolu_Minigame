#include <vector>
#include <iostream>
#include <stdlib.h>
#include "neural-network.h"


NeuralNetwork::NeuralNetwork(){
    this->size = 0;
    this->input = Matrix();
    this->output = Matrix();
}

NeuralNetwork::~NeuralNetwork(){
    // this->w.clear();
}

void NeuralNetwork::pushLayer(Matrix hidden){

    // @TODO: Verificações de dimensão da matriz que vai entrar
    // com a ultima matriz existente.
    this->w.push_back(hidden);
    this->size += 1;
}

void NeuralNetwork::setInput(Matrix in){
    this->input = in;
}

Matrix NeuralNetwork::getOutput(){
    return this->output;
}

int NeuralNetwork::getLoss(Matrix outExpected){
    
    if(this->output.cols != outExpected.cols || this->output.rows != outExpected.rows)
        return 99999999;

    int loss = 0;

    for(int i = 0; i < outExpected.rows; i++){
        for(int j = 0; j < outExpected.cols; j++){
            // LOSS por enquanto será uma MSE (Mean Squared Error)
            loss += (this->output.m[i][j]-outExpected.m[i][j])*(this->output.m[i][j] - outExpected.m[i][j]);
        }
    }

    loss = loss/(outExpected.cols*outExpected.rows);
    return loss;
}

void NeuralNetwork::run(){
    Matrix results = this->input;

    for(unsigned i = 0; i < this->w.size(); i++){
        //results.print();
        //std::cout << std::endl; 
        results = results * this->w[i];
    }

    this->output = results;
}

void NeuralNetwork::print(){

    for(int i = 0; i < this->size; i++){
        printf("Hidden Layer %d neuronio(s)\n", this->w[i].cols);
        this->w[i].print();
    }

}