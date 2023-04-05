#include <iostream>
#include <iomanip>
#include <stdexcept>

#pragma once

template<typename T>
class Matrix {
private:
    T* data_;
    std::size_t rows_;
    std::size_t cols_;
public:
    /// <summary>
    /// Вывод матрицы в консоль.
    /// </summary>
    /// <param name="element_size">Количество символов для выводимого элемента (по умолчанию 5)</param>
    void print(int element_size = 5) {
        for (size_t i = 0; i < rows_; i++)
        {
            for (size_t j = 0; j < cols_; j++)
            {
                std::cout << std::setw(element_size) << this->operator()(i, j) << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

#pragma region Конструкторы, деструктор

    /// <summary>
    /// Конструктор, создающий пустой массив, 0 строк, 0 столбцов
    /// </summary>
    Matrix() : data_(nullptr), rows_(0), cols_(0) {}
    /// <summary>
    /// Конструктор, создающий пустой массив [rows] на [cols]
    /// </summary>
    /// <param name="rows">Количество столбцов</param>
    /// <param name="cols">Количество строк</param>
    Matrix(std::size_t rows, std::size_t cols)
        : data_(new T[rows * cols]), rows_(rows), cols_(cols) 
    {
        for (size_t i = 0; i < rows_ * cols_; i++) data_[i] = INT_MIN;
    }
    /// <summary>
    /// Конструктор, создающий заполненный массив [rows] на [cols]
    /// </summary>
    /// <param name="rows">Количество столбцов</param>
    /// <param name="cols">Количество строк</param>
    /// <param name="data">Значение, которым будет заполнена матрица</param>
    Matrix(std::size_t rows, std::size_t cols, T data)
        : data_(new T[rows * cols]), rows_(rows), cols_(cols)
    {
        for (size_t i = 0; i < rows_ * cols_; i++) data_[i] = data;
    }
    /// <summary>
    /// Конструктор копирования
    /// </summary>
    /// <param name="other">Объект, который необходмимо скопировать</param>
    Matrix(const Matrix& other)
        : data_(new T[other.rows_ * other.cols_]), rows_(other.rows_), cols_(other.cols_)
    {
        std::copy(other.data_, other.data_ + (other.rows_ * other.cols_), data_);
    }
    /// <summary>
    /// Деструктор объекта
    /// </summary>
    ~Matrix() {
        delete[] data_;
    }
#pragma endregion

#pragma region Изменение размера матрицы

    /// <summary>
    /// Изменение размера объекта. Созданные элементы равны INT_MIN
    /// </summary>
    /// <param name="rows">Требуемое количество столбцов</param>
    /// <param name="cols">Требуемое количестов строк</param>
    void resize(std::size_t rows, std::size_t cols) {
        Matrix<T> tmp(rows, cols);
        for (std::size_t i = 0; i < std::min(rows_, rows); ++i)
            for (std::size_t j = 0; j < std::min(cols_, cols); ++j)
                tmp(i, j) = (*this)(i, j);
        swap(*this, tmp);
    }
#pragma endregion
#pragma region Вставка и удаление столбцов

    /// <summary>
    /// Вставить столбец в объект. 
    /// Если массив больше количества строк, то запишется только допустимое количество значений.
    /// Если массив меньше количества строк, то незаполненные данные будут равны INT_MIN.
    /// </summary>
    /// <param name="index">Индекс, которым будет вставляемый столбец</param>
    /// <param name="row_data">Вставляемый стобец</param>
    void insert_col(std::size_t index, const T* col_data) {
        if (index > cols_ || index < 0) {
            throw std::out_of_range("Invalid column index");
        }
        Matrix<T> tmp(rows_, cols_ + 1);
        for (std::size_t i = 0; i < rows_; ++i) {
            for (std::size_t j = 0; j < index; ++j) {
                tmp(i, j) = (*this)(i, j);
            }
            tmp(i, index) = col_data[i];
            for (std::size_t j = index; j < cols_; ++j) {
                tmp(i, j + 1) = (*this)(i, j);
            }
        }
        swap(*this, tmp);
    }
    /// <summary>
    /// Метод удаляет столбец по его индексу
    /// </summary>
    /// <param name="index">Индекс удалемой строки</param>
    void remove_col(std::size_t index) {
        if (index >= cols_ || index < 0) {
            throw std::out_of_range("Invalid column index");
        }
        Matrix<T> tmp(rows_, cols_ - 1);
        for (std::size_t i = 0; i < rows_; ++i) {
            for (std::size_t j = 0; j < index; ++j) {
                tmp(i, j) = (*this)(i, j);
            }
            for (std::size_t j = index + 1; j < cols_; ++j) {
                tmp(i, j - 1) = (*this)(i, j);
            }
        }
        swap(*this, tmp);
    }
#pragma endregion
#pragma region Вставка и удаление строк

    /// <summary>
    /// Вставить строку в объект. 
    /// Если массив больше количества столбцов, то запишется только допустимое количество значений.
    /// Если массив меньше количества столбцов, то незаполненные данные будут равны INT_MIN.
    /// </summary>
    /// <param name="index">Индекс, которым будет вставляемая строка</param>
    /// <param name="row_data">Вставляемая строка</param>
    void insert_row(std::size_t index, const T* row_data) {
        if (index > rows_ || index < 0) {
            throw std::out_of_range("Invalid row index");
        }

        Matrix<T> tmp(rows_ + 1, cols_);
        for (std::size_t i = 0; i < index; ++i) {
            for (std::size_t j = 0; j < cols_; ++j) {
                tmp(i, j) = (*this)(i, j);
            }
        }
        for (std::size_t j = 0; j < cols_; ++j) {
            tmp(index, j) = row_data[j];
        }
        for (std::size_t i = index; i < rows_; ++i) {
            for (std::size_t j = 0; j < cols_; ++j) {
                tmp(i + 1, j) = (*this)(i, j);
            }
        }
        swap(*this, tmp);
    }

    /// <summary>
    /// Метод удаляет строку по ее индексу
    /// </summary>
    /// <param name="index">Индекс удаляемой строки</param>
    void remove_row(std::size_t index) {
        if (index >= rows_ || index < 0) {
            throw std::out_of_range("Invalid row index");
        }
        Matrix<T> tmp(rows_ - 1, cols_);
        for (std::size_t i = 0; i < index; ++i) {
            for (std::size_t j = 0; j < cols_; ++j) {
                tmp(i, j) = (*this)(i, j);
            }
        }
        for (std::size_t i = index + 1; i < rows_; ++i) {
            for (std::size_t j = 0; j < cols_; ++j) {
                tmp(i - 1, j) = (*this)(i, j);
            }
        }
        swap(*this, tmp);
    }
#pragma endregion
#pragma region Доступ по индексам

    /// <summary>
    /// Возвращает объект сместо [] (невозможно использовать из-за ограничений cpp)
    /// </summary>
    /// <param name="row">Ряд</param>
    /// <param name="col">Столбец</param>
    /// <returns></returns>
    T& operator()(std::size_t row, std::size_t col) {
        return data_[row * cols_ + col];
    }
#pragma endregion
#pragma region Количество элементов по размерностям

    /// <summary>
    /// Возвращает количество строк
    /// </summary>
    /// <returns>Количество строк в матрице</returns>
    std::size_t rows_count() const {
        return rows_;
    }
    /// <summary>
    /// Возвращает количество столбцов
    /// </summary>
    /// <returns>Количество столбцов в матрице</returns>
    std::size_t cols_count() const {
        return cols_;
    }
#pragma endregion
#pragma region Работа с итераторами
    /// <summary>
    /// Возвращает указатель на начало массива (итератор)
    /// </summary>
    /// <returns></returns>
    T* begin() {
        return data_;
    }
    /// <summary>
    /// Возвращает указатель на последний элемент массива (для остановки итератора)
    /// </summary>
    /// <returns></returns>
    T* end() {
        return data_ + (rows_ * cols_);
    }

    
#pragma endregion
#pragma region swap

    /// <summary>
    /// Меняет местами данные между двумя матрицами
    /// </summary>
    /// <param name="first">Первая матрица</param>
    /// <param name="second">Вторая матрица</param>
    friend void swap(Matrix& first, Matrix& second) {
        std::swap(first.data_, second.data_);
        std::swap(first.rows_, second.rows_);
        std::swap(first.cols_, second.cols_);
    }
#pragma endregion


   
};