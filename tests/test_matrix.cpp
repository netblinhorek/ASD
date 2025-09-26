
#include <gtest/gtest.h>
#include <iostream>
#include <cassert>
#include <iostream>
#include <string>
#include <sstream>  
#include <stdexcept> 
#include <cstdio>
#include <Windows.h>
#include <chrono>
#include <fcntl.h>
#include <io.h>
#include "matrix.h"

#define EPSILON 0.000001

TEST(TestMatrix, test_constructor_rows_cols) {
    size_t rows = 3;
    size_t cols = 4;

    Matrix<int> matrix(rows, cols);

    ASSERT_EQ(matrix.size(), rows);

    for (size_t i = 0; i < rows; ++i) {
        ASSERT_EQ(matrix[i].size(), cols);
    }
}
TEST(TestMatrix, test_constructor_rows_cols_value) {
    size_t rows = 3;
    size_t cols = 4;
    int value = 5;

    Matrix<int> matrix(rows, cols, value);
    ASSERT_EQ(matrix.size(), 3);
    if (!matrix.is_empty()) {
        ASSERT_EQ(matrix[0].size(), 4);
    }
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[i].size(); j++) {
            ASSERT_EQ(matrix[i][j], 5);
        }
    }
}
TEST(TestMatrix, test_is_square_true) {
    Matrix<int> matrix(3, 3);
    ASSERT_TRUE(matrix.is_square());
}

TEST(TestMatrix, test_is_square_false_rows_greater) {
    Matrix<int> matrix(4, 2);
    ASSERT_FALSE(matrix.is_square());
}

TEST(TestMatrix, test_is_square_false_cols_greater) {
    Matrix<int> matrix(2, 5);
    ASSERT_FALSE(matrix.is_square());
}

TEST(TestMatrix, test_is_square_1x1) {
    Matrix<int> matrix(1, 1);
    ASSERT_TRUE(matrix.is_square());
}

TEST(TestMatrix, test_is_valid_true) {
    Matrix<int> matrix(3, 3);
    ASSERT_TRUE(matrix.is_valid());
}

TEST(TestMatrix, test_is_valid_false) {
    Matrix<int> matrix(2, 3);
    matrix[0].push_back(999);
    ASSERT_FALSE(matrix.is_valid());
}

TEST(TestMatrix, test_is_valid_empty) {
    Matrix<int> matrix(0, 0);
    ASSERT_TRUE(matrix.is_valid());
}

TEST(TestMatrix, test_is_valid_single_row) {
    Matrix<int> matrix(1, 5);
    ASSERT_TRUE(matrix.is_valid());
}

TEST(TestMatrix, test_transpose_square) {
    Matrix<int> matrix(2, 2);
    matrix[0][0] = 1; matrix[0][1] = 2;
    matrix[1][0] = 3; matrix[1][1] = 4;

    Matrix<int> transposed = matrix.transpose();

    ASSERT_EQ(transposed.rows(), 2);
    ASSERT_EQ(transposed.cols(), 2);
    ASSERT_EQ(transposed[0][0], 1);
    ASSERT_EQ(transposed[0][1], 3);
    ASSERT_EQ(transposed[1][0], 2);
    ASSERT_EQ(transposed[1][1], 4);
}

TEST(TestMatrix, test_transpose_rectangular) {
    Matrix<int> matrix(2, 3);
    matrix[0][0] = 1;
    matrix[0][1] = 2;
    matrix[0][2] = 3;
    matrix[1][0] = 4;
    matrix[1][1] = 5;
    matrix[1][2] = 6;

    Matrix<int> transposed = matrix.transpose();

    ASSERT_EQ(transposed.rows(), 3);
    ASSERT_EQ(transposed.cols(), 2);
    ASSERT_EQ(transposed[0][0], 1);
    ASSERT_EQ(transposed[0][1], 4);
    ASSERT_EQ(transposed[1][0], 2);
    ASSERT_EQ(transposed[1][1], 5);
    ASSERT_EQ(transposed[2][0], 3);
    ASSERT_EQ(transposed[2][1], 6);
}

TEST(TestMatrix, test_transpose_double_transpose) {
    Matrix<int> original(3, 2);
    original[0][0] = 1; original[0][1] = 2;
    original[1][0] = 3; original[1][1] = 4;
    original[2][0] = 5; original[2][1] = 6;

    Matrix<int> double_transposed = original.transpose().transpose();

    ASSERT_EQ(double_transposed.rows(), original.rows());
    ASSERT_EQ(double_transposed.cols(), original.cols());
    for (size_t i = 0; i < original.rows(); ++i) {
        for (size_t j = 0; j < original.cols(); ++j) {
            ASSERT_EQ(double_transposed[i][j], original[i][j]);
        }
    }
}

TEST(TestMatrix, test_matrix_mult) {
    Matrix<int> a(2, 3);
    a[0][0] = 1; a[0][1] = 2; a[0][2] = 3;
    a[1][0] = 4; a[1][1] = 5; a[1][2] = 6;

    Matrix<int> b(3, 2);
    b[0][0] = 7; b[0][1] = 8;
    b[1][0] = 9; b[1][1] = 10;
    b[2][0] = 11; b[2][1] = 12;

    Matrix<int> result = a * b;

    ASSERT_EQ(result.rows(), 2);
    ASSERT_EQ(result.cols(), 2);
    ASSERT_EQ(result[0][0], 58);
    ASSERT_EQ(result[0][1], 64);
    ASSERT_EQ(result[1][0], 139);
    ASSERT_EQ(result[1][1], 154);
}

TEST(TestMatrix, test_matrix_mult_identity) {
    Matrix<int> identity(2, 2);
    identity[0][0] = 1; identity[0][1] = 0;
    identity[1][0] = 0; identity[1][1] = 1;

    Matrix<int> matrix(2, 2);
    matrix[0][0] = 5; matrix[0][1] = 6;
    matrix[1][0] = 7; matrix[1][1] = 8;

    Matrix<int> result = matrix * identity;

    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            ASSERT_EQ(result[i][j], matrix[i][j]);
        }
    }
}

TEST(TestMatrix, test_matrix_mult_invalid_dimensions) {
    Matrix<int> a(2, 3);
    Matrix<int> b(2, 3);

    ASSERT_THROW(a * b, std::invalid_argument);
}

TEST(TestMatrix, test_matrix_mult_zero) {
    Matrix<int> a(2, 3, 5);
    Matrix<int> b(3, 2, 0);

    Matrix<int> result = a * b;

    for (size_t i = 0; i < result.rows(); ++i) {
        for (size_t j = 0; j < result.cols(); ++j) {
            ASSERT_EQ(result[i][j], 0);
        }
    }
}
TEST(TestMatrix, test_operator_add) {
    Matrix<int> m1(2, 2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    Matrix<int> m2(2, 2);
    m2[0][0] = 5; m2[0][1] = 6;
    m2[1][0] = 7; m2[1][1] = 8;

    Matrix<int> result = m1 + m2;

    ASSERT_EQ(result[0][0], 6);
    ASSERT_EQ(result[0][1], 8);
    ASSERT_EQ(result[1][0], 10);
    ASSERT_EQ(result[1][1], 12);
}

TEST(TestMatrix, test_operator_add_dimension_mismatch) {
    Matrix<int> m1(2, 2);
    Matrix<int> m2(3, 3);

    EXPECT_THROW(m1 + m2, std::invalid_argument);
}

TEST(TestMatrix, test_operator_minus) {
    Matrix<int> m1(2, 2);
    m1[0][0] = 10; m1[0][1] = 8;
    m1[1][0] = 6; m1[1][1] = 4;

    Matrix<int> m2(2, 2);
    m2[0][0] = 5; m2[0][1] = 3;
    m2[1][0] = 2; m2[1][1] = 1;

    Matrix<int> result = m1 - m2;

    ASSERT_EQ(result[0][0], 5);
    ASSERT_EQ(result[0][1], 5);
    ASSERT_EQ(result[1][0], 4);
    ASSERT_EQ(result[1][1], 3);
}

TEST(TestMatrix, test_operator_sub_dimension_mismatch) {
    Matrix<int> m1(2, 2);
    Matrix<int> m2(2, 3);

    EXPECT_THROW(m1 - m2, std::invalid_argument);
}

TEST(TestMatrix, test_operator_mult) {
    Matrix<int> m1(2, 3);
    m1[0][0] = 1; m1[0][1] = 2; m1[0][2] = 3;
    m1[1][0] = 4; m1[1][1] = 5; m1[1][2] = 6;

    Matrix<int> m2(3, 2);
    m2[0][0] = 7; m2[0][1] = 8;
    m2[1][0] = 9; m2[1][1] = 10;
    m2[2][0] = 11; m2[2][1] = 12;

    Matrix<int> result = m1 * m2;

    ASSERT_EQ(result.rows(), 2);
    ASSERT_EQ(result.cols(), 2);
    ASSERT_EQ(result[0][0], 58);
    ASSERT_EQ(result[0][1], 64);
    ASSERT_EQ(result[1][0], 139);
    ASSERT_EQ(result[1][1], 154);
}

TEST(TestMatrix, test_operator_mult_dimension_mismatch) {
    Matrix<int> m1(2, 3);
    Matrix<int> m2(2, 3);

    EXPECT_THROW(m1 * m2, std::invalid_argument);
}

TEST(TestMatrix, test_operator_div) {
    Matrix<double> m1(2, 2);
    m1[0][0] = 10.0; m1[0][1] = 8.0;
    m1[1][0] = 6.0; m1[1][1] = 4.0;

    Matrix<double> m2(2, 2);
    m2[0][0] = 2.0; m2[0][1] = 4.0;
    m2[1][0] = 3.0; m2[1][1] = 2.0;

    Matrix<double> result = m1 / m2;

    ASSERT_DOUBLE_EQ(result[0][0], 5.0);
    ASSERT_DOUBLE_EQ(result[0][1], 2.0);
    ASSERT_DOUBLE_EQ(result[1][0], 2.0);
    ASSERT_DOUBLE_EQ(result[1][1], 2.0);
}

TEST(TestMatrix, test_operator_divide_by_zero) {
    Matrix<double> m1(2, 2);
    Matrix<double> m2(2, 2);
    m2[0][0] = 1.0; m2[0][1] = 0.0;

    EXPECT_THROW(m1 / m2, std::invalid_argument);
}

TEST(TestMatrix, test_operator_div_dimension_mismatch) {
    Matrix<double> m1(2, 2);
    Matrix<double> m2(3, 3);

    EXPECT_THROW(m1 / m2, std::invalid_argument);
}

TEST(TestMatrix, test_operator_add_scalar) {
    Matrix<int> m1(2, 2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    Matrix<int> result = m1 + 5;

    ASSERT_EQ(result[0][0], 6);
    ASSERT_EQ(result[0][1], 7);
    ASSERT_EQ(result[1][0], 8);
    ASSERT_EQ(result[1][1], 9);
}

TEST(TestMatrix, test_operator_sub_scalar) {
    Matrix<int> m1(2, 2);
    m1[0][0] = 10; m1[0][1] = 8;
    m1[1][0] = 6; m1[1][1] = 4;

    Matrix<int> result = m1 - 3;

    ASSERT_EQ(result[0][0], 7);
    ASSERT_EQ(result[0][1], 5);
    ASSERT_EQ(result[1][0], 3);
    ASSERT_EQ(result[1][1], 1);
}

TEST(TestMatrix, test_operator_mult_scalar) {
    Matrix<int> m(2, 2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    Matrix<int> result = m * 3;

    ASSERT_EQ(result[0][0], 3);
    ASSERT_EQ(result[0][1], 6);
    ASSERT_EQ(result[1][0], 9);
    ASSERT_EQ(result[1][1], 12);
}

TEST(TestMatrix, test_operator_div_scalar) {
    Matrix<double> m(2, 2);
    m[0][0] = 6.0; m[0][1] = 9.0;
    m[1][0] = 12.0; m[1][1] = 15.0;

    Matrix<double> result = m / 3.0;

    ASSERT_DOUBLE_EQ(result[0][0], 2.0);
    ASSERT_DOUBLE_EQ(result[0][1], 3.0);
    ASSERT_DOUBLE_EQ(result[1][0], 4.0);
    ASSERT_DOUBLE_EQ(result[1][1], 5.0);
}

TEST(TestMatrix, test_operator_div_scalar_by_zero) {
    Matrix<double> m(2, 2);

    EXPECT_THROW(m / 0.0, std::invalid_argument);
}

TEST(TestMatrix, test_operator_add_equals_matrix) {
    Matrix<int> m1(2, 2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    Matrix<int> m2(2, 2);
    m2[0][0] = 5; m2[0][1] = 6;
    m2[1][0] = 7; m2[1][1] = 8;

    m1 += m2;

    ASSERT_EQ(m1[0][0], 6);
    ASSERT_EQ(m1[0][1], 8);
    ASSERT_EQ(m1[1][0], 10);
    ASSERT_EQ(m1[1][1], 12);
}

TEST(TestMatrix, test_operator_add_equals_matrix_dimension_mismatch) {
    Matrix<int> m1(2, 2);
    Matrix<int> m2(3, 3);

    EXPECT_THROW(m1 += m2, std::invalid_argument);
}

TEST(TestMatrix, test_operator_sub_equals_matrix) {
    Matrix<int> m1(2, 2);
    m1[0][0] = 10; m1[0][1] = 8;
    m1[1][0] = 6; m1[1][1] = 4;

    Matrix<int> m2(2, 2);
    m2[0][0] = 5; m2[0][1] = 3;
    m2[1][0] = 2; m2[1][1] = 1;

    m1 -= m2;

    ASSERT_EQ(m1[0][0], 5);
    ASSERT_EQ(m1[0][1], 5);
    ASSERT_EQ(m1[1][0], 4);
    ASSERT_EQ(m1[1][1], 3);
}

TEST(TestMatrix, test_operator_mult_equals_matrix) {
    Matrix<int> m1(2, 2);
    m1[0][0] = 2; m1[0][1] = 3;
    m1[1][0] = 4; m1[1][1] = 5;

    Matrix<int> m2(2, 2);
    m2[0][0] = 1; m2[0][1] = 2;
    m2[1][0] = 3; m2[1][1] = 4;

    m1 *= m2;

    ASSERT_EQ(m1[0][0], 2);
    ASSERT_EQ(m1[0][1], 6);
    ASSERT_EQ(m1[1][0], 12);
    ASSERT_EQ(m1[1][1], 20);
}

TEST(TestMatrix, test_operator_divide_equals_matrix) {
    Matrix<double> m1(2, 2);
    m1[0][0] = 10.0; m1[0][1] = 8.0;
    m1[1][0] = 6.0; m1[1][1] = 4.0;

    Matrix<double> m2(2, 2);
    m2[0][0] = 2.0; m2[0][1] = 4.0;
    m2[1][0] = 3.0; m2[1][1] = 2.0;

    m1 /= m2;

    ASSERT_DOUBLE_EQ(m1[0][0], 5.0);
    ASSERT_DOUBLE_EQ(m1[0][1], 2.0);
    ASSERT_DOUBLE_EQ(m1[1][0], 2.0);
    ASSERT_DOUBLE_EQ(m1[1][1], 2.0);
}

TEST(TestMatrix, test_operator_divide_equals_matrix_by_zero) {
    Matrix<double> m1(2, 2);
    Matrix<double> m2(2, 2);
    m2[0][0] = 1.0; m2[0][1] = 0.0;

    EXPECT_THROW(m1 /= m2, std::invalid_argument);
}

TEST(TestMatrix, test_operator_plus_equals_scalar) {
    Matrix<int> m(2, 2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    m += 5;

    ASSERT_EQ(m[0][0], 6);
    ASSERT_EQ(m[0][1], 7);
    ASSERT_EQ(m[1][0], 8);
    ASSERT_EQ(m[1][1], 9);
}

TEST(TestMatrix, test_operator_minus_equals_scalar) {
    Matrix<int> m(2, 2);
    m[0][0] = 10; m[0][1] = 8;
    m[1][0] = 6; m[1][1] = 4;

    m -= 3;

    ASSERT_EQ(m[0][0], 7);
    ASSERT_EQ(m[0][1], 5);
    ASSERT_EQ(m[1][0], 3);
    ASSERT_EQ(m[1][1], 1);
}

TEST(TestMatrix, test_operator_multiply_equals_scalar) {
    Matrix<int> m(2, 2);
    m[0][0] = 2; m[0][1] = 3;
    m[1][0] = 4; m[1][1] = 5;

    m *= 3;

    ASSERT_EQ(m[0][0], 6);
    ASSERT_EQ(m[0][1], 9);
    ASSERT_EQ(m[1][0], 12);
    ASSERT_EQ(m[1][1], 15);
}

TEST(TestMatrix, test_operator_div_equals_scalar) {
    Matrix<double> m(2, 2);
    m[0][0] = 6.0; m[0][1] = 9.0;
    m[1][0] = 12.0; m[1][1] = 15.0;

    m /= 3.0;

    ASSERT_DOUBLE_EQ(m[0][0], 2.0);
    ASSERT_DOUBLE_EQ(m[0][1], 3.0);
    ASSERT_DOUBLE_EQ(m[1][0], 4.0);
    ASSERT_DOUBLE_EQ(m[1][1], 5.0);
}

TEST(TestMatrix, test_operator_div_equals_scalar_by_zero) {
    Matrix<double> m(2, 2);

    EXPECT_THROW(m /= 0.0, std::invalid_argument);
}

TEST(TestMatrix, test_add_scalar_left) {
    Matrix<double> mat(2, 2);
    mat[0][0] = 6; mat[0][1] = 2;
    mat[1][0] = 3; mat[1][1] = 7;
    int a = 7;
    Matrix<double> result = a + mat;
    ASSERT_EQ(result[0][0], 13);
    ASSERT_EQ(result[0][1], 9);
    ASSERT_EQ(result[1][0], 10);
    ASSERT_EQ(result[1][1], 14);

}

TEST(TestMatrix, test_mult_scalar_right) {
    Matrix<double> mat(2, 2);
    mat[0][0] = 6; mat[0][1] = 2;
    mat[1][0] = 3; mat[1][1] = 7;
    int a = 7;
    Matrix<double> result = a * mat;
    ASSERT_EQ(result[0][0], 42);
    ASSERT_EQ(result[0][1], 14);
    ASSERT_EQ(result[1][0], 21);
    ASSERT_EQ(result[1][1], 49);
}
TEST(TestMatrix, test_div_scalar_right) {

}
TEST(TestMatrix, test_add_scalar_right_unar) {
    Matrix<double> mat(2, 2);
    mat[0][0] = 6; mat[0][1] = 2;
    mat[1][0] = 3; mat[1][1] = 7;
    int a = 7;
    Matrix<double> result = mat + -a;
    ASSERT_EQ(result[0][0], -1);
    ASSERT_EQ(result[0][1], -5);
    ASSERT_EQ(result[1][0], -4);
    ASSERT_EQ(result[1][1], 0);

}
TEST(TestMatrix, test_sub_scalar_right_unar) {

}
TEST(TestMatrix, test_mult_scalar_right_unar) {
    Matrix<double> mat(2, 2);
    mat[0][0] = 6; mat[0][1] = 2;
    mat[1][0] = 3; mat[1][1] = 7;
    int a = 7;
    Matrix<double> result = mat * -a;
    ASSERT_EQ(result[0][0], -42);
    ASSERT_EQ(result[0][1], -14);
    ASSERT_EQ(result[1][0], -21);
    ASSERT_EQ(result[1][1], -49);
}
TEST(TestMatrix, test_div_scalar_right_unar) {

}
TEST(TestMatrix, test_add_scalar_left_unar) {
    Matrix<double> mat(2, 2);

}
TEST(TestMatrix, test_sub_scalar_left_unar) {

}
TEST(TestMatrix, test_mult_scalar_left_unar) {

}
TEST(TestMatrix, test_div_scalar_left_unar) {

}