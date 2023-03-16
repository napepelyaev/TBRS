#include <iostream>
// размер стороны
const int size = 500;

void print(int** array);

int main()
{
#pragma region Инициализация массивов
    int** A = new int* [size];
    int** B = new int* [size];
    int** C = new int* [size];

    for (int i = 0; i < size; i++) {
        A[i] = new int[size];
        B[i] = new int[size];
        C[i] = new int[size];
    }
#pragma endregion

#pragma region Заполнение массивов
    // перебор строк
    for (int i = 0; i < size; i++) {
        // перебор столбцов
        for (int j = 0; j < size; j++) {
            A[i][j] = rand() % 500 - 250;
            B[i][j] = rand() % 500 - 250;
        }
    }
#pragma endregion

    print(A);

#pragma region Удаление массивов
    for (int i = 0; i < size; i++) {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }

    delete[] A;
    delete[] B;
    delete[] C;
#pragma endregion
}

// Вывод матрицы с размером [size]
void print(int** array) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << array[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}
