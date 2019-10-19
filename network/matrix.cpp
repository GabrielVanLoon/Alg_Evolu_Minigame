/**
 * @class Matrix
 */
#include <stdlib.h>
#include <iostream>
#include "matrix.h"
 
Matrix::Matrix(){
    this->rows = 0;
    this->cols = 0;
}

Matrix::Matrix(int n, int m){
    this->rows = (n > 0) ? n : 0;
    this->cols = (m > 0) ? m : 0;

    this->values.resize(n);
    for(int i = 0; i < n; i++)
        this->values[i].resize(m);
}

// Matrix& Matrix::operator=(const Matrix& other){
//     this->rows = other.rows;
//     this->cols = other.cols;

//     for(int i = 0; i < this->rows; i++){
//        this->values[i].clear();
//        for(int j = 0; j < this->cols; j++){
//            this->values[i].push_back(other.values[i][j]);
//        }
//     }
// }

Matrix Matrix::operator*(const Matrix &obj){
    Matrix C = Matrix(this->rows, obj.cols);

    for(int r = 0; r < this->rows; r++){
        for(int j = 0; j < obj.cols; j++){
    
            C.values[r][j] = 0;
            for(int d = 0; d < this->cols; d++){
                C.values[r][j] += this->values[r][d] * obj.values[d][j];
            }
        }
    }

    return C;
}

void Matrix::set(int i, int j, int value){
    if(0 <= i && i < this->rows && 0 <= j && j < this->cols)
        this->values[i][j] = value;
}

void Matrix::print(){
    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->cols; j++)
            printf("%2d  ", this->values[i][j]);
        printf("\n");
    }
}