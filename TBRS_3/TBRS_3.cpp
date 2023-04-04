#include <iostream>
#include <chrono>  
#include <omp.h>   

const int N = 2000;
void initArrays(double** A, double* b, double* x);
void eraseArrays(double** A, double* b, double* x);

long calculateParallel(double** A, double* b, double* x) {
    auto start_time = std::chrono::high_resolution_clock::now();
    // Прямой ход
    // Перебор строк. Для высчитывания следующих строк нужны законченные предыдущие
    for (int k = 0; k < N - 1; k++) {
#pragma omp parallel for
        // Перебор столбцов. Вычисления каждого столбца независят от других
        for (int i = k + 1; i < N; i++) {
            // Вычисление коэффициента от элемента на главной диагонали
            double coef = A[i][k] / A[k][k];
            // Вычисление новых значений в каждом столбце выбранной строки, для получения треугольника 0
            for (int j = k; j < N; j++) {
                A[i][j] -= coef * A[k][j];
            }
            // Изменение значений правой части в соответсвии со строкой
            b[i] -= coef * b[k];
        }
    }
    // Обратный ход
    // Перебор строк с конца. Для каждой следующей строки нужна предыдущая
    for (int i = N - 1; i >= 0; i--) {
        // Подсчет суммы левой части, от уже известных значений x (не считая самой первой рассматриваемой строки)
        double sum = 0;
        for (int j = i + 1; j < N; j++) {
            sum += A[i][j] * x[j];
        }
        // Вычисление значения x
        x[i] = (b[i] - sum) / A[i][i];
    }
    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    return long(duration.count());
}
long calculateSequential(double** A, double* b, double* x) {
    auto start_time = std::chrono::high_resolution_clock::now();
    // Прямой ход
    // Перебор строк. Для высчитывания следующих строк нужны законченные предыдущие
    for (int k = 0; k < N - 1; k++) {
        // Перебор столбцов. Вычисления каждого столбца независят от других
        for (int i = k + 1; i < N; i++) {
            // Вычисление коэффициента от элемента на главной диагонали
            double coef = A[i][k] / A[k][k];
            // Вычисление новых значений в каждом столбце выбранной строки, для получения треугольника 0
            for (int j = k; j < N; j++) {
                A[i][j] -= coef * A[k][j];
            }
            // Изменение значений правой части в соответсвии со строкой
            b[i] -= coef * b[k];
        }
    }
    // Обратный ход
    // Перебор строк с конца. Для каждой следующей строки нужна предыдущая
    for (int i = N - 1; i >= 0; i--) {
        // Подсчет суммы левой части, от уже известных значений x (не считая самой первой рассматриваемой строки)
        double sum = 0;
        for (int j = i + 1; j < N; j++) {
            sum += A[i][j] * x[j];
        }
        // Вычисление значения x
        x[i] = (b[i] - sum) / A[i][i];
    }
    auto end_time = std::chrono::high_resolution_clock::now();

    // Вывод времени выполнения
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    return long(duration.count());
}

int main() {

    double** A = new double* [N];
    double* b = new double[N];
    double* x = new double[N];

    initArrays(A, b, x);

    std::cout << "Result paralleled: " << calculateParallel(A, b, x) << " microseconds" << std::endl;
    std::cout << "Result sequential: " << calculateSequential(A, b, x) << " microseconds" << std::endl;

    eraseArrays(A, b, x);
    return 0;
}

void initArrays(double** A, double* b, double* x) {
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

    for (int i = 0; i < N; i++) {
        x[i] = 0;
    }
}
void eraseArrays(double** A, double* b, double* x) {
    for (int i = 0; i < N; i++) {
        delete[] A[i];
    }
    delete[] A;
    delete[] b;
    delete[] x;
}