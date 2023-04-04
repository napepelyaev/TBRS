#include <iostream>
#include "matrix.h"

void fill_matrix(DynamicArray2D<int>& array) {
    for (size_t i = 0; i < array.rows_count(); i++)
    {
        for (size_t j = 0; j < array.cols_count(); j++)
        {
            array(i, j) = (int)(i * array.cols_count()) + (int)j;
        }
    }
}

void fill_matrix(DynamicArray2D<float>& matrix) {
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
    DynamicArray2D<int> matrix_int = DynamicArray2D<int>(3, 3);
    fill_matrix(matrix_int);
    matrix_int.print();
    DynamicArray2D<float> matrix_float = DynamicArray2D<float>(3, 3);
    fill_matrix(matrix_float);
    matrix_float(1, 1) = 0.15F;
    matrix_float.remove_row(2);
    matrix_float.print();
}
