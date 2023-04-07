#include <iostream>
#include "matrix.h"

void fill_matrix(Matrix<int>& array) {
    for (size_t i = 0; i < array.rows_count(); i++)
    {
        for (size_t j = 0; j < array.cols_count(); j++)
        {
            array(i, j) = (int)(i * array.cols_count()) + (int)j;
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

int main()
{
    Matrix<int> matrix_int = Matrix<int>(3, 3);
    fill_matrix(matrix_int);
    matrix_int.print();
    Matrix<float> matrix_float = Matrix<float>(3, 3);
    fill_matrix(matrix_float);
    matrix_float(1, 1) = 0.15F;
    matrix_float.remove_row(2);
    matrix_float.print();
}
