#ifndef MATRIX_H
    #define MATRIX_H
    
    #include <vector>

    /**
     * @class Matrix
     */
    class Matrix {
        public:
            int   rows, cols;
            std::vector<std::vector<double>> values;

            /**
             * Matrix();
             * Cria a instância de uma Matriz 0x0 trivial sem nenhum valor associado.
             */
            Matrix();

            /**
             * Matrix(int n, int m);
             * Cria a instância de uma NxM trivial preenchida por 0's.
             */
            Matrix(int n, int m);

            /**
             * Matrix& operator=(const Matrix &other);
             * Sobrecarga do operador '=' que permite atribuição de objetos.
             */
            // Matrix& operator=(const Matrix &other);

            /**
             * Matrix  operator*(const Matrix &obj);
             * Sobrecarga do operador '*' que permite a multiplicação de objetos
             */
            Matrix  operator*(const Matrix &obj);

            /**
             * void set(int i, int j, int value);
             * Define, de maneira segura, um valor na posição Aij da Matriz.
             */
            void set(int i, int j, double value);

            /**
             * void print();
             * Exibe a matriz na tela
             */
            void print();
    };
#endif