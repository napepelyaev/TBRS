#include <iostream>
#include "matrix.cpp"

void fill_matrix(Matrix<int>& array) {
    for (size_t i = 0; i < array.rows_count(); i++)
    {
        for (size_t j = 0; j < array.cols_count(); j++)
        {
            array(i, j) = (int)(i * array.cols_count() + j);
        }
    }
}

void fill_matrix(Matrix<float>& matrix) {
    for (size_t i = 0; i < matrix.rows_count(); i++)
    {
        for (size_t j = 0; j < matrix.cols_count(); j++)
        {
            matrix(i, j) = (float)(i)+(float)(j + i * matrix.cols_count()) / 10;
        }
    }
}

Matrix<int> create_fill_matrix(int rows, int cols) {
    Matrix<int> matrix = Matrix<int>(rows, cols);
    for (size_t i = 0; i < matrix.rows_count(); i++)
    {
        for (size_t j = 0; j < matrix.cols_count(); j++)
        {
            matrix(i, j) = (int)(i * matrix.cols_count() + j);
        }
    }
    return matrix;
    /*
    * пример для 3x3:
    * 0 1 2
    * 3 4 5
    * 6 7 8
    */
}

int main()
{
    //Matrix<int> test = create_fill_matrix(3, 3);
    ////test.print();
    int* add = new int[3] { 1, 2, 3 };
    ////test.insert_row(2, add, 3);
    ////test.resize(2, 2);
    //test.print(6);

    Matrix<int> matrix1 = create_fill_matrix(4, 3);
    Matrix<int> matrix2 = (matrix1);
    matrix1.insert_col(0, add, 3);
    //fill_matrix(matrix2);
    matrix1.print();
    matrix2.print();
    swap(matrix1, matrix2);

    matrix1.print();
    matrix2.print();
    //Matrix<int> matrix_int = Matrix<int>(3, 3);
    //fill_matrix(matrix_int);
    //matrix_int.print();


    //Matrix<float> matrix_float = Matrix<float>(3, 3);
    //fill_matrix(matrix_float);
    //matrix_float(1, 1) = 0.15F;
    //matrix_float.resize(2, 2);
    ////matrix_float.remove_col(2);
    ////matrix_float.remove_col(1);
    //matrix_float.print();
    ///*for (int data : matrix_int) {
    //    std::cout << data;
    //}*/
}
