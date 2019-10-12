#ifndef MATRIX_H
    #define MATRIX_H
    
    /**
     * @class Matrix
     */
    class Matrix {
        public:
            int   rows, cols;
            int** m;

            Matrix(); // Constructor

            Matrix(const Matrix &m2); // Copy constructor

            Matrix(int rows, int cols);

            ~Matrix(); // Desctructor

            Matrix& operator=(const Matrix& other); // Copy asignment

            void set(int i, int j, int value);

            Matrix operator*(const Matrix &obj);

            void print();
    };
#endif