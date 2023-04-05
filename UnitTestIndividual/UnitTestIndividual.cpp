#include "pch.h"
#include "CppUnitTest.h"
#include "../Individual/matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestIndividual
{
	TEST_CLASS(UnitTestIndividualInt)
	{
	protected: 
		Matrix<int> create_fill_matrix(int rows, int cols) {
			Matrix<int> matrix = Matrix<int>(rows, cols);
			for (size_t i = 0; i < matrix.rows_count(); i++)
			{
				for (size_t j = 0; j < matrix.cols_count(); j++)
				{
					matrix(i, j) = (int)(i * matrix.cols_count()) + (int)j;
				}
			}
			return matrix;
			/* 
			* пример для 3x3:
			* 0 1 2
			* 3 4 5
			* 6 7 8
			*/
		}
	public:
		TEST_METHOD(TestColNumber) {
			Matrix<int> matrix = create_fill_matrix(3, 4);
			Assert::AreEqual(4, (int)matrix.cols_count());
		}

		TEST_METHOD(TestRowNumber) {
			Matrix<int> matrix = create_fill_matrix(3, 4);
			Assert::AreEqual(3, (int)matrix.rows_count());
		}
		
		TEST_METHOD(TestIndexGetter) {
			Matrix<int> matrix = Matrix<int>(3, 3, 0);
			Assert::AreEqual(0, matrix(1, 1));
		}

		TEST_METHOD(TestIndexSetter) {
			Matrix<int> matrix = Matrix<int>(3, 3, 0);
			matrix(1, 1) = 5;
			Assert::AreEqual(5, matrix(1, 1));
		}

		TEST_METHOD(TestRowAdd) {
			Matrix<int> matrix = Matrix<int>(3, 3, 0);
			int* new_row = new int[3] { 10, 10, 10 };
			matrix.insert_row(1, new_row);
			new_row[0] = 0;
			new_row[1] = 0;
			new_row[2] = 0;
			Assert::AreEqual(10, matrix(1, 1));
		}

		TEST_METHOD(TestRowDelete) {
			Matrix<int> matrix = create_fill_matrix(3, 3);
			matrix.remove_row(1);
			Assert::AreEqual(7, matrix(1, 1));
		}

		TEST_METHOD(TestColAdd) {
			Matrix<int> matrix = Matrix<int>(3, 3, 0);
			int* new_row = new int[3] { 10, 10, 10 };
			matrix.insert_col(1, new_row);
			new_row[0] = 0;
			new_row[1] = 0;
			new_row[2] = 0;
			Assert::AreEqual(10, matrix(1, 1));
		}

		TEST_METHOD(TestColDelete) {
			Matrix<int> matrix = create_fill_matrix(3, 3);
			matrix.remove_col(1);
			Assert::AreEqual(5, matrix(1, 1));
		}

		TEST_METHOD(TestResizeIncrease) {
			Matrix<int> matrix = create_fill_matrix(3, 3);
			matrix.resize(4, 3);
			Assert::AreEqual(4, (int)matrix.rows_count());
			Assert::AreEqual(INT_MIN, matrix(3, 2));
		}

		TEST_METHOD(TestResizeDecrease) {
			Matrix<int> matrix = create_fill_matrix(3, 3);
			matrix.resize(2, 2);
			Assert::AreEqual(2, (int)matrix.rows_count());
			Assert::AreEqual(4, matrix(1, 1));
		}

		TEST_METHOD(TestSwapMatrix) {
			Matrix<int> matrix1 = Matrix<int>(3, 3, 0);
			Matrix<int> matrix2 = create_fill_matrix(3, 3);
			swap(matrix1, matrix2);
			Assert::AreEqual(4, matrix1(1, 1));
			Assert::AreEqual(0, matrix2(1, 1));
		}

		TEST_METHOD(TestSwapUnequalMatrix) {
			Matrix<int> matrix1 = Matrix<int>(4, 3, 0);
			Matrix<int> matrix2 = create_fill_matrix(3, 2);
			swap(matrix1, matrix2);
			Assert::AreEqual(5, matrix1(2, 1));
			Assert::AreEqual(0, matrix2(3, 2));
		}

		TEST_METHOD(TestIerators) {
			Matrix<int> matrix = create_fill_matrix(3, 3);
			int sum = 0;
			for (int number : matrix) {
				sum += number;
			}
			Assert::AreEqual(36, sum);
		}
	};
	TEST_CLASS(UnitTestIndividualFloat)
	{
	protected:
		Matrix<float> create_fill_matrix(int rows, int cols) {
			Matrix<float> matrix = Matrix<float>(rows, cols);
			for (size_t i = 0; i < matrix.rows_count(); i++)
			{
				for (size_t j = 0; j < matrix.cols_count(); j++)
				{
					matrix(i, j) = (float)(i) + (float)(j + i * matrix.cols_count())/10;
				}
			}
			return matrix;
			/*
			* пример для 3x3:
			* 0.0 0.1 0.2
			* 1.3 1.4 1.5
			* 2.6 2.7 2.8
			*/
		}
	public:
		TEST_METHOD(TestColNumber) {
			Matrix<float> matrix = create_fill_matrix(3, 4);
			Assert::AreEqual(4, (int)matrix.cols_count());
		}

		TEST_METHOD(TestRowNumber) {
			Matrix<float> matrix = create_fill_matrix(3, 4);
			Assert::AreEqual(3, (int)matrix.rows_count());
		}

		TEST_METHOD(TestIndexGetter) {
			Matrix<float> matrix = Matrix<float>(3, 3, 0.0F);
			Assert::AreEqual(0.0F, matrix(1, 1));
		}

		TEST_METHOD(TestIndexSetter) {
			Matrix<float> matrix = Matrix<float>(3, 3, 0.0F);
			matrix(1, 1) = 5.0F;
			Assert::AreEqual(5.0F, matrix(1, 1));
		}

		TEST_METHOD(TestRowAdd) {
			Matrix<float> matrix = Matrix<float>(3, 3, 0.0F);
			float* new_row = new float[3] { 10.0F, 10.0F, 10.0F };
			matrix.insert_row(1, new_row);
			new_row[0] = 0.0F;
			new_row[1] = 0.0F;
			new_row[2] = 0.0F;
			Assert::AreEqual(10.0F, matrix(1, 1));
		}

		TEST_METHOD(TestRowDelete) {
			Matrix<float> matrix = create_fill_matrix(3, 3);
			matrix.remove_row(1);
			Assert::AreEqual(2.7F, matrix(1, 1));
		}

		TEST_METHOD(TestColAdd) {
			Matrix<float> matrix = Matrix<float>(3, 3, 0.0F);
			float* new_row = new float[3] { 10.0F, 10.0F, 10.0F };
			matrix.insert_col(1, new_row);
			new_row[0] = 0.0F;
			new_row[1] = 0.0F;
			new_row[2] = 0.0F;
			Assert::AreEqual(10.0F, matrix(1, 1));
		}

		TEST_METHOD(TestColDelete) {
			Matrix<float> matrix = create_fill_matrix(3, 3);
			matrix.remove_col(1);
			Assert::AreEqual(1.5F, matrix(1, 1));
		}

		TEST_METHOD(TestResizeIncrease) {
			Matrix<float> matrix = create_fill_matrix(3, 3);
			matrix.resize(4, 3);
			Assert::AreEqual(4, (int)matrix.rows_count());
			Assert::AreEqual((float)INT_MIN, matrix(3, 2));
		}

		TEST_METHOD(TestResizeDecrease) {
			Matrix<float> matrix = create_fill_matrix(3, 3);
			matrix.resize(2, 2);
			Assert::AreEqual(2, (int)matrix.rows_count());
			Assert::AreEqual(1.4F, matrix(1, 1));
		}

		TEST_METHOD(TestSwapMatrix) {
			Matrix<float> matrix1 = Matrix<float>(3, 3, 0);
			Matrix<float> matrix2 = create_fill_matrix(3, 3);
			swap(matrix1, matrix2);
			Assert::AreEqual(1.4F, matrix1(1, 1));
			Assert::AreEqual(0.0F, matrix2(1, 1));
		}

		TEST_METHOD(TestSwapUnequalMatrix) {
			Matrix<float> matrix1 = Matrix<float>(4, 3, 0.0F);
			/* Вид массива:
			*   0		0.1
			*	1.2		1.3
			*	2.4		2.5
			*/
			Matrix<float> matrix2 = create_fill_matrix(3, 2);
			swap(matrix1, matrix2);
			Assert::AreEqual(2.5F, matrix1(2, 1));
			Assert::AreEqual(0.0F, matrix2(3, 2));
		}


		TEST_METHOD(TestIerators) {
			Matrix<float> matrix = create_fill_matrix(3, 3);
			float sum = 0;
			for (float number : matrix) {
				sum += number;
			}
			Assert::AreEqual(12.6F, sum);
		}
	};
}
