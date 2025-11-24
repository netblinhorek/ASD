#include <Windows.h>
#include <chrono>
#include <fcntl.h>
#include <io.h>
#include <gtest/gtest.h>
#include "../lib_Algorithms_matrix/algorithms_matrix.cpp"

TEST(TestLocalMinimum, test_empty_matrix) {
    Matrix<int> matrix(0, 0);
    size_t row, col;
    ASSERT_FALSE(find_local_minimum(matrix, row, col));
}

TEST(TestLocalMinimum, test_1x1_matrix) {
    Matrix<int> matrix(1, 1);
    matrix[0][0] = 42;

    size_t row, col;
    ASSERT_TRUE(find_local_minimum(matrix, row, col));
    ASSERT_EQ(row, 0);
    ASSERT_EQ(col, 0);
    ASSERT_EQ(matrix[row][col], 42);
}

TEST(TestLocalMinimum, test_2x2_matrix) {
    Matrix<int> matrix(2, 2);
    matrix[0][0] = 3;
    matrix[0][1] = 1;  
    matrix[1][0] = 2;  
    matrix[1][1] = 4;

    size_t row, col;
    ASSERT_TRUE(find_local_minimum(matrix, row, col));
    ASSERT_TRUE(is_local_minimum(matrix, row, col));
    int value = matrix[row][col];
    ASSERT_TRUE(value == 1 || value == 2);  
}

TEST(TestLocalMinimum, test_3x3_example_from_task) {
    Matrix<int> matrix(3, 3);
    matrix[0][0] = 3;
    matrix[0][1] = 1;
    matrix[0][2] = 2;
    matrix[1][0] = 5;
    matrix[1][1] = 8;
    matrix[1][2] = 4;
    matrix[2][0] = 7;
    matrix[2][1] = 6;
    matrix[2][2] = 9;

    size_t row, col;
    ASSERT_TRUE(find_local_minimum(matrix, row, col));
    int found_value = matrix[row][col];
    ASSERT_TRUE(found_value == 1 || found_value == 6); 
}
TEST(TestLocalMinimum, test_minimum_in_corner) {
    Matrix<int> matrix(3, 3);
    matrix[0][0] = 0; 
    matrix[0][1] = 4;
    matrix[0][2] = 3;
    matrix[1][0] = 6;
    matrix[1][1] = 5;
    matrix[1][2] = 2;  
    matrix[2][0] = 7;
    matrix[2][1] = 8;
    matrix[2][2] = 9;

    size_t row, col;
    ASSERT_TRUE(find_local_minimum(matrix, row, col));
    ASSERT_TRUE(is_local_minimum(matrix, row, col)); 
    int value = matrix[row][col];
    ASSERT_TRUE(value == 0 || value == 2); 
}

TEST(TestLocalMinimum, test_minimum_in_center) {
    Matrix<int> matrix(3, 3);
    matrix[0][0] = 9;
    matrix[0][1] = 8;
    matrix[0][2] = 7;
    matrix[1][0] = 6;
    matrix[1][1] = 1;
    matrix[1][2] = 5;
    matrix[2][0] = 4;
    matrix[2][1] = 3;
    matrix[2][2] = 2;

    size_t row, col;
    ASSERT_TRUE(find_local_minimum(matrix, row, col));
    ASSERT_EQ(matrix[row][col], 1); 
}

TEST(TestLocalMinimum, test_large_matrix_10x10) {
    Matrix<int> matrix(10, 10);
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j++) {
            matrix[i][j] = i * 10 + j + 100; 
        }
    }
    matrix[5][5] = 1;  

    size_t row, col;
    ASSERT_TRUE(find_local_minimum(matrix, row, col));
    ASSERT_EQ(matrix[row][col], 1);
}

TEST(TestLocalMinimum, test_minimum_on_edge) {
    Matrix<int> matrix(3, 3);
    matrix[0][0] = 5;
    matrix[0][1] = 2;  
    matrix[0][2] = 6;
    matrix[1][0] = 3;    
    matrix[1][1] = 7;
    matrix[1][2] = 8;
    matrix[2][0] = 4;
    matrix[2][1] = 9;
    matrix[2][2] = 10;

    size_t row, col;
    ASSERT_TRUE(find_local_minimum(matrix, row, col));

    ASSERT_TRUE(is_local_minimum(matrix, row, col));

    int found_value = matrix[row][col];
    ASSERT_TRUE(found_value == 2 || found_value == 3);
}

TEST(TestLocalMinimum, test_strictly_increasing) {
    Matrix<int> matrix(3, 3);
    matrix[0][0] = 1;
    matrix[0][1] = 2;
    matrix[0][2] = 3;
    matrix[1][0] = 4;
    matrix[1][1] = 5;
    matrix[1][2] = 6;
    matrix[2][0] = 7;
    matrix[2][1] = 8;
    matrix[2][2] = 9;

    size_t row, col;
    ASSERT_TRUE(find_local_minimum(matrix, row, col));
    ASSERT_EQ(matrix[row][col], 1);
}

TEST(TestLocalMinimum, test_strictly_decreasing) {
    Matrix<int> matrix(3, 3);
    matrix[0][0] = 9;
    matrix[0][1] = 8;
    matrix[0][2] = 7;
    matrix[1][0] = 6;
    matrix[1][1] = 5;
    matrix[1][2] = 4;
    matrix[2][0] = 3;
    matrix[2][1] = 2;
    matrix[2][2] = 1;

    size_t row, col;
    ASSERT_TRUE(find_local_minimum(matrix, row, col));
    ASSERT_EQ(matrix[row][col], 1); 
}

TEST(TestLocalMinimum, test_multiple_local_minima) {
    Matrix<int> matrix(3, 3);
    matrix[0][0] = 5;
    matrix[0][1] = 1;
    matrix[0][2] = 6;
    matrix[1][0] = 2;
    matrix[1][1] = 7;
    matrix[1][2] = 3;
    matrix[2][0] = 8;
    matrix[2][1] = 4;
    matrix[2][2] = 9;

    size_t row, col;
    ASSERT_TRUE(find_local_minimum(matrix, row, col));
    int found_value = matrix[row][col];
    ASSERT_TRUE(found_value == 1 || found_value == 2 || found_value == 3 || found_value == 4);
}

TEST(TestLocalMinimum, test_is_local_minimum_function) {
    Matrix<int> matrix(3, 3);
    matrix[0][0] = 3;
    matrix[0][1] = 1;
    matrix[0][2] = 2;
    matrix[1][0] = 5;
    matrix[1][1] = 8;
    matrix[1][2] = 4;
    matrix[2][0] = 7;
    matrix[2][1] = 6;
    matrix[2][2] = 9;

    ASSERT_TRUE(is_local_minimum(matrix, 0, 1));  
    ASSERT_TRUE(is_local_minimum(matrix, 2, 1));  

    ASSERT_FALSE(is_local_minimum(matrix, 0, 0)); 
    ASSERT_FALSE(is_local_minimum(matrix, 1, 1)); 
    ASSERT_FALSE(is_local_minimum(matrix, 2, 2)); 
}

TEST(TestLocalMinimum, test_find_smallest_neighbor_function) {
    Matrix<int> matrix(3, 3);
    matrix[0][0] = 3;
    matrix[0][1] = 1;
    matrix[0][2] = 2;
    matrix[1][0] = 5;
    matrix[1][1] = 8;
    matrix[1][2] = 4;
    matrix[2][0] = 7;
    matrix[2][1] = 6;
    matrix[2][2] = 9;

    size_t row = 1, col = 1;
    find_small_neighbor(matrix, row, col);
    ASSERT_EQ(matrix[row][col], 1); 


    row = 0; col = 0;
    find_small_neighbor(matrix, row, col);
    ASSERT_EQ(matrix[row][col], 1); 
}
TEST(TestLocalMinimum, test_find_two_min_local) {
    Matrix<int> matrix(4, 4);
    matrix[0][0] = 11;
    matrix[0][1] = 15;
    matrix[0][2] = 10;
    matrix[0][3] = 9;
    matrix[1][0] = 6;
    matrix[1][1] = 16;
    matrix[1][2] = 3;
    matrix[1][3] = 8;
    matrix[2][0] = 7;
    matrix[2][1] = 4;
    matrix[2][2] = 2;
    matrix[2][3] = 13;
    matrix[3][0] = 14;
    matrix[3][1] = 12;
    matrix[3][2] = 1;
    matrix[3][3] = 5;

    size_t row, col;
    ASSERT_TRUE(find_local_minimum(matrix, row, col));

    ASSERT_TRUE(is_local_minimum(matrix, row, col));

    int found_value = matrix[row][col];
    ASSERT_TRUE(found_value == 6 || found_value == 1);

    if (found_value == 6) {
        ASSERT_EQ(row, 1);
        ASSERT_EQ(col, 0);
    }
    else if (found_value == 1) {
        ASSERT_EQ(row, 3);
        ASSERT_EQ(col, 2);
    }
}
