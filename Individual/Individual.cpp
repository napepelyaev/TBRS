#include <iostream>
#include "matrix.h"
template<typename T>
void fill_matrix(DynamicArray2D<T> &array);

int main()
{
    DynamicArray2D<int> matrix_int = DynamicArray2D<int>(3, 3);
    fill_matrix<int>(matrix_int);
    matrix_int.print();
    DynamicArray2D<float> matrix_float = DynamicArray2D<float>(3, 3);
    fill_matrix<float>(matrix_float);
    matrix_float(1, 1) = 0.15F;
    matrix_float.remove_row(2);
    matrix_float.print();
    std::cout << "Hello World!\n";
}

template<typename T>
void fill_matrix(DynamicArray2D<T> &array) {
    for (size_t i = 0; i < array.rows_count(); i++)
    {
        for (size_t j = 0; j < array.cols_count(); j++)
        {
            array(i, j) = (T)(i * array.cols_count()) + (T)j;
        }
    }
}