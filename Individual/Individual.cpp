#include <iostream>
#include "matrix.h"

int main()
{
    DynamicArray2D<int> matrix = DynamicArray2D<int>(3, 3, 0);
    for (size_t i = 0; i < matrix.rows_count(); i++)
    {
        for (size_t j = 0; j < matrix.cols_count(); j++)
        {
            matrix(i, j) = (int)i* matrix.cols_count() + (int)j;
        }
    }
    matrix.print(1);
    std::cout << "Hello World!\n";
}
