/**
 * @class Matrix
 */
#include <stdlib.h>
#include <iostream>
#include "matrix.h"
 
Matrix::Matrix(){
    this->rows = 1;
    this->cols = 1;

    this->m = (int**) malloc(this->rows*sizeof(int*));
    for(int i = 0; i < this->rows; i++)
        this->m[i] = (int*) malloc(this->cols*sizeof(int*));
}

Matrix::Matrix(const Matrix &m2){
    this->rows = m2.rows;
    this->cols = m2.cols;

    this->m = (int**) malloc(this->rows*sizeof(int*));
    for(int i = 0; i < this->rows; i++){
        this->m[i] = (int*) malloc(this->cols*sizeof(int*));
        std::copy(m2.m[i], m2.m[i]+m2.cols, this->m[i]);
    }
}

Matrix::Matrix(int r, int c){
    this->rows = (r > 0) ? r : 1;
    this->cols = (c > 0) ? c : 1;

    this->m = (int**) malloc(this->rows*sizeof(int*));
    for(int i = 0; i < this->rows; i++)
        this->m[i] = (int*) malloc(this->cols*sizeof(int*));
}

Matrix::~Matrix(){
    for(int i = 0; i < this->rows; i++){
        free(this->m[i]);
    }
    free(this->m);
}

Matrix& Matrix::operator=(const Matrix& other){
    
    this->rows = other.rows;
    this->cols = other.cols;

    this->m = (int**) malloc(this->rows*sizeof(int*));
    for(int i = 0; i < this->rows; i++){
        this->m[i] = (int*) malloc(this->cols*sizeof(int*));
        std::copy(other.m[i], other.m[i]+other.cols, this->m[i]);
    }

}

void Matrix::set(int i, int j, int value){
    if(0 <= i && i <= this->rows && 0 <= j && j <= this->cols)
        this->m[i][j] = value;
}

Matrix Matrix::operator*(const Matrix &obj){
    Matrix C = Matrix(this->rows, obj.cols);

    for(int r = 0; r < this->rows; r++){
        for(int j = 0; j < obj.cols; j++){
            
            C.m[r][j] = 0;
            for(int d = 0; d < this->cols; d++){
                C.m[r][j] += this->m[r][d] * obj.m[d][j];
            }
        }
    }

    return C;
}

void Matrix::print(){
    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->cols; j++){
            printf("%2d  ", this->m[i][j]);
        }
        printf("\n");
    }
}