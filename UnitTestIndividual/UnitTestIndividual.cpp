#include "pch.h"
#include "CppUnitTest.h"
#include "../Individual/matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestIndividual
{
	TEST_CLASS(UnitTestIndividualInt)
	{
	protected:
		/*
			* пример для 3x3:
			* 0 1 2
			* 3 4 5
			* 6 7 8
			*/
		void fill_matrix(Matrix<int>& array) {
			for (size_t i = 0; i < array.rows_count(); i++)
			{
				for (size_t j = 0; j < array.cols_count(); j++)
				{
					array(i, j) = (int)(i * array.cols_count() + j);
				}
			}
		}
	public:
		TEST_METHOD(TestColNumber) {
			Matrix<int> matrix = Matrix<int>(3, 4);
			Assert::AreEqual(4, (int)matrix.cols_count());
		}

		TEST_METHOD(TestRowNumber) {
			Matrix<int> matrix = Matrix<int>(3, 4);
			Assert::AreEqual(3, (int)matrix.rows_count());
		}
		
		TEST_METHOD(TestIndexGetter) {
			Matrix<int> matrix = Matrix<int>(3, 3);
			Assert::AreEqual(0, matrix(1, 1));
		}

		TEST_METHOD(TestIndexSetter) {
			Matrix<int> matrix = Matrix<int>(3, 3);
			matrix(1, 1) = 5;
			Assert::AreEqual(5, matrix(1, 1));
		}

		TEST_METHOD(TestRowAdd) {
			Matrix<int> matrix = Matrix<int>(3, 3);
			int* new_row = new int[3] { 10, 10, 10 };
			matrix.insert_row(1, new_row, 3);
			new_row[0] = 0;
			new_row[1] = 0;
			new_row[2] = 0;
			Assert::AreEqual(10, matrix(1, 1));
		}

		TEST_METHOD(TestRowDelete) {
			Matrix<int> matrix = Matrix<int>(3, 3); 
			fill_matrix(matrix);
			matrix.remove_row(1);
			Assert::AreEqual(7, matrix(1, 1));
		}

		TEST_METHOD(TestColAdd) {
			Matrix<int> matrix = Matrix<int>(3, 3);
			int* new_row = new int[3] { 10, 10, 10 };
			matrix.insert_col(1, new_row, 3);
			new_row[0] = 0;
			new_row[1] = 0;
			new_row[2] = 0;
			Assert::AreEqual(10, matrix(1, 1));
		}

		TEST_METHOD(TestColDelete) {
			Matrix<int> matrix = Matrix<int>(3, 3);
			fill_matrix(matrix);
			matrix.remove_col(1);
			Assert::AreEqual(5, matrix(1, 1));
		}

		TEST_METHOD(TestResizeIncrease) {
			Matrix<int> matrix = Matrix<int>(3, 3);
			fill_matrix(matrix);
			matrix.resize(4, 3);
			Assert::AreEqual(4, (int)matrix.rows_count());
			Assert::AreEqual(0, matrix(3, 2));
		}

		TEST_METHOD(TestResizeDecrease) {
			Matrix<int> matrix = Matrix<int>(3, 3);
			fill_matrix(matrix);
			matrix.resize(2, 2);
			Assert::AreEqual(2, (int)matrix.rows_count());
			Assert::AreEqual(4, matrix(1, 1));
		}

		TEST_METHOD(TestSwapMatrix) {
			Matrix<int> matrix1 = Matrix<int>(3, 3);
			Matrix<int> matrix2 = Matrix<int>(3, 3);
			fill_matrix(matrix2);
			swap(matrix1, matrix2);
			Assert::AreEqual(4, matrix1(1, 1));
			Assert::AreEqual(0, matrix2(1, 1));
		}

		TEST_METHOD(TestSwapUnequalMatrix) {
			Matrix<int> matrix1 = Matrix<int>(4, 3);
			Matrix<int> matrix2 = Matrix<int>(3, 3);
			fill_matrix(matrix2);
			swap(matrix1, matrix2);
			Assert::AreEqual(7, matrix1(2, 1));
			Assert::AreEqual(0, matrix2(3, 2));
		}

		TEST_METHOD(TestIerators) {
			Matrix<int> matrix = Matrix<int>(3, 3);
			fill_matrix(matrix);
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
		/*
			* пример для 3x3:
			* 0.0 0.1 0.2
			* 1.3 1.4 1.5
			* 2.6 2.7 2.8
			*/
		void fill_matrix(Matrix<float>& matrix) {
			for (size_t i = 0; i < matrix.rows_count(); i++)
			{
				for (size_t j = 0; j < matrix.cols_count(); j++)
				{
					matrix(i, j) = (float)i + (float)(j + i * matrix.cols_count()) / 10;
				}
			}
		}
	public:
		TEST_METHOD(TestColNumber) {
			Matrix<float> matrix = Matrix<float>(3, 4);
			Assert::AreEqual(4, (int)matrix.cols_count());
		}

		TEST_METHOD(TestRowNumber) {
			Matrix<float> matrix = Matrix<float>(3, 4);
			Assert::AreEqual(3, (int)matrix.rows_count());
		}

		TEST_METHOD(TestIndexGetter) {
			Matrix<float> matrix = Matrix<float>(3, 3);
			Assert::AreEqual(0.0F, matrix(1, 1));
		}

		TEST_METHOD(TestIndexSetter) {
			Matrix<float> matrix = Matrix<float>(3, 3);
			matrix(1, 1) = 5.0F;
			Assert::AreEqual(5.0F, matrix(1, 1));
		}

		TEST_METHOD(TestRowAdd) {
			Matrix<float> matrix = Matrix<float>(3, 3);
			float* new_row = new float[3] { 10.0F, 10.0F, 10.0F };
			matrix.insert_row(1, new_row, 3);
			new_row[0] = 0.0F;
			new_row[1] = 0.0F;
			new_row[2] = 0.0F;
			Assert::AreEqual(10.0F, matrix(1, 1));
		}

		TEST_METHOD(TestRowDelete) {
			Matrix<float> matrix = Matrix<float>(3, 3);
			fill_matrix(matrix);
			matrix.remove_row(1);
			Assert::AreEqual(2.7F, matrix(1, 1));
		}

		TEST_METHOD(TestColAdd) {
			Matrix<float> matrix = Matrix<float>(3, 3, 0.0F);
			float* new_row = new float[3] { 10.0F, 10.0F, 10.0F };
			matrix.insert_col(1, new_row, 3);
			new_row[0] = 0.0F;
			new_row[1] = 0.0F;
			new_row[2] = 0.0F;
			Assert::AreEqual(10.0F, matrix(1, 1));
		}

		TEST_METHOD(TestColDelete) {
			Matrix<float> matrix = Matrix<float>(3, 3);
			fill_matrix(matrix);
			matrix.remove_col(1);
			Assert::AreEqual(1.5F, matrix(1, 1));
		}

		TEST_METHOD(TestResizeIncrease) {
			Matrix<float> matrix = Matrix<float>(3, 3);
			fill_matrix(matrix);
			matrix.resize(4, 3);
			Assert::AreEqual(4, (int)matrix.rows_count());
			Assert::AreEqual((float)0, matrix(3, 2));
		}

		TEST_METHOD(TestResizeDecrease) {
			Matrix<float> matrix = Matrix<float>(3, 3);
			fill_matrix(matrix);
			matrix.resize(2, 2);
			Assert::AreEqual(2, (int)matrix.rows_count());
			Assert::AreEqual(1.4F, matrix(1, 1));
		}

		TEST_METHOD(TestSwapMatrix) {
			Matrix<float> matrix1 = Matrix<float>(3, 3, 0);
			Matrix<float> matrix2 = Matrix<float>(3, 3);
			fill_matrix(matrix2);
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
			Matrix<float> matrix2 = Matrix<float>(3, 2);
			fill_matrix(matrix2);
			swap(matrix1, matrix2);
			Assert::AreEqual(2.5F, matrix1(2, 1));
			Assert::AreEqual(0.0F, matrix2(3, 2));
		}


		TEST_METHOD(TestIerators) {
			Matrix<float> matrix = Matrix<float>(3, 3);
			fill_matrix(matrix);
			float sum = 0;
			for (float number : matrix) {
				sum += number;
			}
			Assert::AreEqual(12.6F, sum);
		}
	};
}
