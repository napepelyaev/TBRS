#include <iostream>
#include <chrono>
#include <omp.h>
// размер стороны
const int size = 500;

void print(int** array);
inline std::chrono::microseconds multiplyLinear(int** first, int** second, int** res);
inline std::chrono::microseconds multiplyOpenMP(int** first, int** second, int** res);

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

    /*int threadsNum = 2;
    omp_set_num_threads(threadsNum);
    int i, j, k;
    auto start = std::chrono::high_resolution_clock::now();
#pragma omp parallel for shared(A, B, C) private(i, j, k)


    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();


    std::cout << "OpenMP result: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;*/
    std::cout << "Linear result:  " << multiplyLinear(A, B, C).count() << " microseconds" << std::endl;
    std::cout << "OpenMPI result: " << multiplyOpenMP(A, B, C).count() << " microseconds" << std::endl;

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

inline std::chrono::microseconds multiplyLinear(int** first, int** second, int** res)
{
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                res[i][j] += first[i][k] * second[k][j];
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

inline std::chrono::microseconds multiplyOpenMP(int** first, int** second, int** res)
{
    int threadsNum = 2;
    omp_set_num_threads(threadsNum);
    int i, j, k;
    auto start = std::chrono::high_resolution_clock::now();
#pragma omp parallel for shared(first, second, res) private(i, j, k)

    
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            for (k = 0; k < size; k++) {
                res[i][j] += first[i][k] * second[k][j];
            }
        }   
    }

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

