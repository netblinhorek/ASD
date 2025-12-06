#include <gtest/gtest.h>
#include "../lib_Triangle/triangle.h"
#include <stdexcept>
#include <cmath>

TEST(TestTriangle, test_default_constructor) {
    Triangle<double> t;
    EXPECT_EQ(t.rows(), 0);
    EXPECT_EQ(t.cols(), 0);
    EXPECT_EQ(t.get_type(), TriangleType::Lower);
}

TEST(TestTriangle, test_size_constructor_lower) {
    Triangle<int> t(3, 0, TriangleType::Lower);
    EXPECT_EQ(t.rows(), 3);
    EXPECT_EQ(t.cols(), 3);
    EXPECT_EQ(t.get_type(), TriangleType::Lower);

    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            if (j > i) {
                EXPECT_THROW(t(i, j) = 1, std::invalid_argument);
            }
            else {
                EXPECT_NO_THROW(t(i, j) = i + j);
            }
        }
    }
}


TEST(TestTriangle, test_value_constructor_lower) {
    Triangle<double> t(3, 5.5, TriangleType::Lower);

    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            if (j <= i) {
                EXPECT_DOUBLE_EQ(t(i, j), 5.5);
            }
            else {
                EXPECT_THROW(t(i, j) = 1.0, std::invalid_argument);
            }
        }
    }
}

TEST(TestTriangle, test_from_matrix_lower) {
    Matrix<double> m(3, 3);
    m[0][0] = 1.0; m[0][1] = 0.0; m[0][2] = 0.0;  
    m[1][0] = 2.0; m[1][1] = 3.0; m[1][2] = 0.0;
    m[2][0] = 4.0; m[2][1] = 5.0; m[2][2] = 6.0;

    Triangle<double> t(m, TriangleType::Lower);

    EXPECT_DOUBLE_EQ(t(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(t(1, 0), 2.0);
    EXPECT_DOUBLE_EQ(t(1, 1), 3.0);
    EXPECT_DOUBLE_EQ(t(2, 0), 4.0);
    EXPECT_DOUBLE_EQ(t(2, 1), 5.0);
    EXPECT_DOUBLE_EQ(t(2, 2), 6.0);

    EXPECT_THROW(t(0, 1), std::invalid_argument);
    EXPECT_THROW(t(0, 2), std::invalid_argument);
    EXPECT_THROW(t(1, 2), std::invalid_argument);
}


TEST(TestTriangle, test_from_matrix_invalid) {
    Matrix<double> m(2, 3);
    EXPECT_THROW(Triangle<double> t(m, TriangleType::Lower), std::invalid_argument);
}


TEST(TestTriangle, test_addition_mismatch) {
    Triangle<int> t1(2, 0, TriangleType::Lower);
    Triangle<int> t2(3, 0, TriangleType::Lower);

    EXPECT_THROW(t1 + t2, std::invalid_argument);
}

TEST(TestTriangle, test_out_of_range_access) {
    Triangle<double> t(2, 0, TriangleType::Lower);

    EXPECT_THROW(t(2, 0), std::out_of_range);
    EXPECT_THROW(t(0, 2), std::out_of_range);
    EXPECT_THROW(t(5, 5), std::out_of_range);
}


TEST(TestTriangle, test_edge_cases) {
    Triangle<double> t1(1, 0, TriangleType::Lower);
    EXPECT_NO_THROW(t1(0, 0) = 5.0);
    EXPECT_DOUBLE_EQ(t1(0, 0), 5.0);

    EXPECT_THROW(t1(0, 1), std::out_of_range);
    EXPECT_THROW(t1(1, 0), std::out_of_range);
}

TEST(TestTriangle, test_subtraction_lower) {
    Triangle<double> t1(3, 0, TriangleType::Lower);
    Triangle<double> t2(3, 0, TriangleType::Lower);

    t1(0, 0) = 5.0;
    t1(1, 0) = 2.0; t1(1, 1) = 3.0;
    t1(2, 0) = 1.0; t1(2, 1) = 4.0; t1(2, 2) = 6.0;

    t2(0, 0) = 2.0;
    t2(1, 0) = 1.0; t2(1, 1) = 1.0;
    t2(2, 0) = 0.5; t2(2, 1) = 2.0; t2(2, 2) = 3.0;

    Triangle<double> result = t1 - t2;

    EXPECT_DOUBLE_EQ(result(0, 0), 3.0);  
    EXPECT_DOUBLE_EQ(result(1, 0), 1.0);  
    EXPECT_DOUBLE_EQ(result(1, 1), 2.0);  
    EXPECT_DOUBLE_EQ(result(2, 0), 0.5);  
    EXPECT_DOUBLE_EQ(result(2, 1), 2.0);  
    EXPECT_DOUBLE_EQ(result(2, 2), 3.0);  

    EXPECT_EQ(result.get_type(), TriangleType::Lower);

    EXPECT_THROW(result(0, 1) = 1.0, std::invalid_argument);
}

TEST(TestTriangle, test_subtraction_mismatch_sizes) {
    Triangle<float> t1(2, 0.0f, TriangleType::Lower);
    Triangle<float> t2(3, 0.0f, TriangleType::Lower);

    EXPECT_THROW(t1 - t2, std::invalid_argument);
}


TEST(TestTriangle, test_subtraction_identity) {
    Triangle<double> t(3, 0, TriangleType::Lower);

    t(0, 0) = 1.5;
    t(1, 0) = 2.3; t(1, 1) = 3.7;
    t(2, 0) = 4.1; t(2, 1) = 5.9; t(2, 2) = 6.8;

    Triangle<double> result = t - t;

    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j <= i; ++j) {
            EXPECT_DOUBLE_EQ(result(i, j), 0.0);
        }
    }
}
TEST(TestTriangle, test_scalar_multiplication_right) {
    Triangle<double> t(3, 0, TriangleType::Lower);

    t(0, 0) = 1.0;
    t(1, 0) = 2.0; t(1, 1) = 3.0;
    t(2, 0) = 4.0; t(2, 1) = 5.0; t(2, 2) = 6.0;

    Triangle<double> result = t * 2.5;

    EXPECT_DOUBLE_EQ(result(0, 0), 2.5);    
    EXPECT_DOUBLE_EQ(result(1, 0), 5.0);    
    EXPECT_DOUBLE_EQ(result(1, 1), 7.5);    
    EXPECT_DOUBLE_EQ(result(2, 0), 10.0);   
    EXPECT_DOUBLE_EQ(result(2, 1), 12.5);   
    EXPECT_DOUBLE_EQ(result(2, 2), 15.0);   

    EXPECT_DOUBLE_EQ(t(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(t(2, 2), 6.0);

    EXPECT_EQ(result.get_type(), TriangleType::Lower);
}

TEST(TestTriangle, test_scalar_multiplication_zero) {
    Triangle<double> t(3, 0, TriangleType::Lower);

    t(0, 0) = 1.5;
    t(1, 0) = 2.5; t(1, 1) = 3.5;
    t(2, 0) = 4.5; t(2, 1) = 5.5; t(2, 2) = 6.5;

    Triangle<double> result = t * 0.0;

    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j <= i; ++j) {
            EXPECT_DOUBLE_EQ(result(i, j), 0.0);
        }
    }
}

TEST(TestTriangle, test_scalar_multiplication_negative) {
    Triangle<double> t(2, 0, TriangleType::Lower);

    t(0, 0) = 2.0;
    t(1, 0) = 3.0; t(1, 1) = 4.0;

    Triangle<double> result_1 = t * (-2.0);

    EXPECT_DOUBLE_EQ(result_1(0, 0), -4.0);   
    EXPECT_DOUBLE_EQ(result_1(1, 0), -6.0);   
    EXPECT_DOUBLE_EQ(result_1(1, 1), -8.0);  
}

TEST(TestTriangle, test_scalar_multiraction_chaining) {
    Triangle<double> t(2, 0, TriangleType::Lower);

    t(0, 0) = 1.0;
    t(1, 0) = 2.0; t(1, 1) = 3.0;

    Triangle<double> result1 = (t * 2.0) * 3.0;
    Triangle<double> result2 = t * 6.0;

    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j <= i; ++j) {
            EXPECT_DOUBLE_EQ(result1(i, j), result2(i, j));
        }
    }
}

TEST(TestTriangle, test_mixed_operations) {
    Triangle<double> A(2, 0, TriangleType::Lower);
    Triangle<double> B(2, 0, TriangleType::Lower);

    A(0, 0) = 5.0;
    A(1, 0) = 2.0; A(1, 1) = 3.0;

    B(0, 0) = 1.0;
    B(1, 0) = 1.0; B(1, 1) = 1.0;

    Triangle<double> result = (A * 2.0) - (B * 3.0);

    EXPECT_DOUBLE_EQ(result(0, 0), 7.0);  
    EXPECT_DOUBLE_EQ(result(1, 0), 1.0);  
    EXPECT_DOUBLE_EQ(result(1, 1), 3.0);  
}
TEST(TestTriangle, test_matrix_multiplication_lower_lower) {
    Triangle<double> t1(3, 0, TriangleType::Lower);
    Triangle<double> t2(3, 0, TriangleType::Lower);

    t1(0, 0) = 2.0;
    t1(1, 0) = 3.0; t1(1, 1) = 4.0;
    t1(2, 0) = 5.0; t1(2, 1) = 6.0; t1(2, 2) = 7.0;

    t2(0, 0) = 1.0;
    t2(1, 0) = 2.0; t2(1, 1) = 3.0;
    t2(2, 0) = 4.0; t2(2, 1) = 5.0; t2(2, 2) = 6.0;

    Triangle<double> result = t1 * t2;

    EXPECT_DOUBLE_EQ(result(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(result(1, 0), 11.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 12.0);
    EXPECT_DOUBLE_EQ(result(2, 0), 45.0);
    EXPECT_DOUBLE_EQ(result(2, 1), 53.0);
    EXPECT_DOUBLE_EQ(result(2, 2), 42.0);

    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 3);
}