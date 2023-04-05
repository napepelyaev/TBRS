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
    /// ����� ������� � �������.
    /// </summary>
    /// <param name="element_size">���������� �������� ��� ���������� �������� (�� ��������� 5)</param>
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

#pragma region ������������, ����������

    /// <summary>
    /// �����������, ��������� ������ ������, 0 �����, 0 ��������
    /// </summary>
    Matrix() : data_(nullptr), rows_(0), cols_(0) {}
    /// <summary>
    /// �����������, ��������� ������ ������ [rows] �� [cols]
    /// </summary>
    /// <param name="rows">���������� ��������</param>
    /// <param name="cols">���������� �����</param>
    Matrix(std::size_t rows, std::size_t cols)
        : data_(new T[rows * cols]), rows_(rows), cols_(cols) 
    {
        for (size_t i = 0; i < rows_ * cols_; i++) data_[i] = INT_MIN;
    }
    /// <summary>
    /// �����������, ��������� ����������� ������ [rows] �� [cols]
    /// </summary>
    /// <param name="rows">���������� ��������</param>
    /// <param name="cols">���������� �����</param>
    /// <param name="data">��������, ������� ����� ��������� �������</param>
    Matrix(std::size_t rows, std::size_t cols, T data)
        : data_(new T[rows * cols]), rows_(rows), cols_(cols)
    {
        for (size_t i = 0; i < rows_ * cols_; i++) data_[i] = data;
    }
    /// <summary>
    /// ����������� �����������
    /// </summary>
    /// <param name="other">������, ������� ����������� �����������</param>
    Matrix(const Matrix& other)
        : data_(new T[other.rows_ * other.cols_]), rows_(other.rows_), cols_(other.cols_)
    {
        std::copy(other.data_, other.data_ + (other.rows_ * other.cols_), data_);
    }
    /// <summary>
    /// ���������� �������
    /// </summary>
    ~Matrix() {
        delete[] data_;
    }
#pragma endregion

#pragma region ��������� ������� �������

    /// <summary>
    /// ��������� ������� �������. ��������� �������� ����� INT_MIN
    /// </summary>
    /// <param name="rows">��������� ���������� ��������</param>
    /// <param name="cols">��������� ���������� �����</param>
    void resize(std::size_t rows, std::size_t cols) {
        Matrix<T> tmp(rows, cols);
        for (std::size_t i = 0; i < std::min(rows_, rows); ++i)
            for (std::size_t j = 0; j < std::min(cols_, cols); ++j)
                tmp(i, j) = (*this)(i, j);
        swap(*this, tmp);
    }
#pragma endregion
#pragma region ������� � �������� ��������

    /// <summary>
    /// �������� ������� � ������. 
    /// ���� ������ ������ ���������� �����, �� ��������� ������ ���������� ���������� ��������.
    /// ���� ������ ������ ���������� �����, �� ������������� ������ ����� ����� INT_MIN.
    /// </summary>
    /// <param name="index">������, ������� ����� ����������� �������</param>
    /// <param name="row_data">����������� ������</param>
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
    /// ����� ������� ������� �� ��� �������
    /// </summary>
    /// <param name="index">������ �������� ������</param>
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
#pragma region ������� � �������� �����

    /// <summary>
    /// �������� ������ � ������. 
    /// ���� ������ ������ ���������� ��������, �� ��������� ������ ���������� ���������� ��������.
    /// ���� ������ ������ ���������� ��������, �� ������������� ������ ����� ����� INT_MIN.
    /// </summary>
    /// <param name="index">������, ������� ����� ����������� ������</param>
    /// <param name="row_data">����������� ������</param>
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
    /// ����� ������� ������ �� �� �������
    /// </summary>
    /// <param name="index">������ ��������� ������</param>
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
#pragma region ������ �� ��������

    /// <summary>
    /// ���������� ������ ������ [] (���������� ������������ ��-�� ����������� cpp)
    /// </summary>
    /// <param name="row">���</param>
    /// <param name="col">�������</param>
    /// <returns></returns>
    T& operator()(std::size_t row, std::size_t col) {
        return data_[row * cols_ + col];
    }
#pragma endregion
#pragma region ���������� ��������� �� ������������

    /// <summary>
    /// ���������� ���������� �����
    /// </summary>
    /// <returns>���������� ����� � �������</returns>
    std::size_t rows_count() const {
        return rows_;
    }
    /// <summary>
    /// ���������� ���������� ��������
    /// </summary>
    /// <returns>���������� �������� � �������</returns>
    std::size_t cols_count() const {
        return cols_;
    }
#pragma endregion
#pragma region ������ � �����������
    /// <summary>
    /// ���������� ��������� �� ������ ������� (��������)
    /// </summary>
    /// <returns></returns>
    T* begin() {
        return data_;
    }
    /// <summary>
    /// ���������� ��������� �� ��������� ������� ������� (��� ��������� ���������)
    /// </summary>
    /// <returns></returns>
    T* end() {
        return data_ + (rows_ * cols_);
    }

    
#pragma endregion
#pragma region swap

    /// <summary>
    /// ������ ������� ������ ����� ����� ���������
    /// </summary>
    /// <param name="first">������ �������</param>
    /// <param name="second">������ �������</param>
    friend void swap(Matrix& first, Matrix& second) {
        std::swap(first.data_, second.data_);
        std::swap(first.rows_, second.rows_);
        std::swap(first.cols_, second.cols_);
    }
#pragma endregion


   
};