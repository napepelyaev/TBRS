#include <iostream>
#include <iomanip> 
#include <chrono>  
#include <omp.h>   

int main() {
    const int N = 20;

    double** A = new double* [N];
    double* b = new double[N];

    for (int i = 0; i < N; i++) {
        A[i] = new double[N];
        for (int j = 0; j < N; j++) {
            if (i == j) {
                A[i][j] = 2;
            }
            else if (i == j + 1 || i == j - 1) {
                A[i][j] = -1;
            }
            else {
                A[i][j] = 0;
            }
        }
        b[i] = i + 1;
    }

    // Инициализация массива x
    double* x = new double[N];
    for (int i = 0; i < N; i++) {
        x[i] = 0;
    }

    // Решение системы линейных уравнений Ax=b
    auto start_time = std::chrono::high_resolution_clock::now();

    for (int k = 0; k < N - 1; k++) {
#pragma omp parallel for
        for (int i = k + 1; i < N; i++) {
            double coef = A[i][k] / A[k][k];
            for (int j = k; j < N; j++) {
                A[i][j] -= coef * A[k][j];
            }
            b[i] -= coef * b[k];
        }
    }

    for (int k = N - 1; k >= 0; k--) {
        x[k] = b[k];
        for (int i = k - 1; i >= 0; i--) {
            b[i] -= A[i][k] * x[k];
        }
        x[k] /= A[k][k];
    }
    auto end_time = std::chrono::high_resolution_clock::now();

    // Вывод времени выполнения
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Result: " << duration.count() << " microseconds" << std::endl;


    // Очистка памяти
    for (int i = 0; i < N; i++) {
        delete[] A[i];
    }
    delete[] A;
    delete[] b;
    delete[] x;

    return 0;
}
