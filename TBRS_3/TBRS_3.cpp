#include <iostream>
#include <chrono>
#include <omp.h>
// размер стороны
const int size = 500;

void print(int** array);
inline std::chrono::microseconds multiplyLinearIJK(int** first, int** second, int** res);
inline std::chrono::microseconds multiplyOpenMP(int** first, int** second, int** res);
inline void resetMatrix(int** matrix);
//
//inline std::chrono::microseconds multiplyLinearIKJ(int** first, int** second, int** res)
//{
//    auto start = std::chrono::high_resolution_clock::now();
//
//    for (int i = 0; i < size; i++) {
//        for (int k = 0; k < size; k++) {
//            for (int j = 0; j < size; j++) {
//                res[i][j] += first[i][k] * second[k][j];
//            }
//        }
//    }
//
//    auto end = std::chrono::high_resolution_clock::now();
//    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//}
//
//inline std::chrono::microseconds multiplyLinearJIK(int** first, int** second, int** res)
//{
//    auto start = std::chrono::high_resolution_clock::now();
//
//    for (int j = 0; j < size; j++) {
//        for (int i = 0; i < size; i++) {
//            for (int k = 0; k < size; k++) {
//                res[i][j] += first[i][k] * second[k][j];
//            }
//        }
//    }
//
//    auto end = std::chrono::high_resolution_clock::now();
//    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//}
//
//inline std::chrono::microseconds multiplyLinearJKI(int** first, int** second, int** res)
//{
//    auto start = std::chrono::high_resolution_clock::now();
//
//    for (int j = 0; j < size; j++) {
//        for (int k = 0; k < size; k++) {
//            for (int i = 0; i < size; i++) {
//                res[i][j] += first[i][k] * second[k][j];
//            }
//        }
//    }
//
//    auto end = std::chrono::high_resolution_clock::now();
//    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//}
//
inline std::chrono::microseconds multiplyLinearKIJ(int** first, int** second, int** res);
//
//inline std::chrono::microseconds multiplyLinearKJI(int** first, int** second, int** res)
//{
//    auto start = std::chrono::high_resolution_clock::now();
//
//    for (int k = 0; k < size; k++) {
//        for (int j = 0; j < size; j++) {
//            for (int i = 0; i < size; i++) {
//                res[i][j] += first[i][k] * second[k][j];
//            }
//        }
//    }
//
//    auto end = std::chrono::high_resolution_clock::now();
//    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//}

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

    std::cout << "OpenMP result:\t\t" << multiplyOpenMP(A, B, C).count() << " microseconds" << std::endl;
    resetMatrix(C);
    std::cout << "Linear result:\t\t" << multiplyLinearIJK(A, B, C).count() << " microseconds" << std::endl;
    resetMatrix(C);
    //std::cout << "IKJ result\t" << multiplyLinearIKJ(A, B, C).count() << " mic/*roseconds" << std::endl;
    //resetMatrix(C);
    //std::cout << "JIK result:\t" << multiplyLinearJIK(A, B, C).count() << " microseconds" << std::endl;
    //resetMatrix(C);
    //std::cout << "JKI result:\t" << multiplyLinearJKI(A, B, C).count() << " microseconds" << std::endl;
    //resetMatrix(C);
    std::cout << "Optimal Linear result:\t" << multiplyLinearKIJ(A, B, C).count() << " microseconds" << std::endl;
    //resetMatrix(C);
    //std::cout << "KJI result:\t" << multiplyLinearKJI(A, B, C).count() << " microseconds" << std::endl;
    //resetMatrix(C);

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

inline std::chrono::microseconds multiplyLinearKIJ(int** first, int** second, int** res)
{
    auto start = std::chrono::high_resolution_clock::now();

    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                res[i][j] += first[i][k] * second[k][j];
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

inline std::chrono::microseconds multiplyLinearIJK(int** first, int** second, int** res)
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

inline void resetMatrix(int** matrix) {
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrix[i][j] = 0;
        }
    }
}