#include <iostream>
#include <chrono>
#include <mpi.h>

void print(int* matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << matrix[i * cols + j] << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char** argv) {
    int size, rank, root = 0;
    std::chrono::steady_clock::time_point start_time, end_time;
    // Инициализация MPI
    MPI_Init(&argc, &argv);
    // Получение общего количества процессоd и номера текущего
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    const int rows = 1000, cols = 1000;
    // Создание матриц
    int* A = new int[rows * cols];
    int* B = new int[rows * cols];
    int* C = new int[rows * cols];
    // Создание подматриц
    int* subA = new int[(rows / size) * cols];
    int* subC = new int[(rows / size) * cols];

    // Инициализация матриц случайными числами
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            A[i * cols + j] = rand() % 10;
            B[i * cols + j] = rand() % 10;
        }
    }

    // Если главный процесс - вывод исходных матриц и старт таймера
    if (rank == root)
    {
        //std::cout << "Matrix A" << std::endl;
        //print(A, rows, cols);
        //std::cout << "Matrix B" << std::endl;
        //print(B, rows, cols);
        start_time = std::chrono::high_resolution_clock::now();
    }

    // Распределение матрицы A между доступными процессорами
    // Данные начинаются с указателя A
    // Делятся на rows/size * cols блоков (100) по 
    // Тип данных в блоке INT
    // Адрес для начала приема в subA
    // Получается столько же элементов, сколько и отправлясется
    // Эти элементы типа INT
    // Адрес отправителя root (0)
    // Область сообщений - MPI_COMM_WORLD, которая объединяет все процессы
    MPI_Scatter(A, (rows / size) * cols, MPI_INT, subA, (rows / size) * cols, MPI_INT, root, MPI_COMM_WORLD);

    // Передача матрицы B на все процессы
    MPI_Bcast(B, rows * cols, MPI_INT, root, MPI_COMM_WORLD);

    // Умножение полученого куска матрицы A на матрицу B
    for (int i = 0; i < rows / size; i++) {
        for (int j = 0; j < cols; j++) {
            subC[i * cols + j] = 0;
            for (int k = 0; k < cols; k++) {
                subC[i * cols + j] += subA[i * cols + k] * B[k * cols + j];
            }
        }
    }

    // Получение всех результирующих подматриц C
    MPI_Gather(subC, (rows / size) * cols, MPI_INT, C, (rows / size) * cols, MPI_INT, root, MPI_COMM_WORLD);

    // Если корневой процесс - вывод времени и итоговой матрицы
    if (rank == root) {
        end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        std::cout << "Time: " << duration.count() << std::endl;
        //std::cout << "Matrix C" << std::endl;
        //print(C, rows, cols);
    }

    // Очистка используемой памяти, завершение всех процессов
    delete[] A;
    delete[] B;
    delete[] C;
    delete[] subA;
    delete[] subC;

    MPI_Finalize();
    return 0;
}
