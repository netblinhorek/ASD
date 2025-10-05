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
            if (j < i) {
                EXPECT_THROW(t(i, j) = 1, std::invalid_argument);
            }
            else {
                EXPECT_NO_THROW(t(i, j) = i + j);
            }
        }
    }
}

TEST(TestTriangle, test_size_constructor_upper) {
    Triangle<int> t(3, 0, TriangleType::Upper);
    EXPECT_EQ(t.rows(), 3);
    EXPECT_EQ(t.cols(), 3);
    EXPECT_EQ(t.get_type(), TriangleType::Upper);

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
            if (j >= i) {
                EXPECT_DOUBLE_EQ(t(i, j), 5.5);
            }
            else {
                EXPECT_THROW(t(i, j) = 1.0, std::invalid_argument);
            }
        }
    }
}

TEST(TestTriangle, test_value_constructor_upper) {
    Triangle<double> t(3, 7.2, TriangleType::Upper);

    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            if (j <= i) {
                EXPECT_DOUBLE_EQ(t(i, j), 7.2);
            }
            else {
                EXPECT_THROW(t(i, j) = 1.0, std::invalid_argument);
            }
        }
    }
}

TEST(TestTriangle, test_from_matrix_lower) {
    Matrix<double> m(3, 3);
    m[0][0] = 1.0; m[0][1] = 2.0; m[0][2] = 3.0;
    m[1][0] = 0.0; m[1][1] = 4.0; m[1][2] = 5.0;
    m[2][0] = 0.0; m[2][1] = 0.0; m[2][2] = 6.0;

    Triangle<double> t(m, TriangleType::Lower);

    EXPECT_DOUBLE_EQ(t(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(t(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(t(0, 2), 3.0);
    EXPECT_DOUBLE_EQ(t(1, 1), 4.0);
    EXPECT_DOUBLE_EQ(t(1, 2), 5.0);
    EXPECT_DOUBLE_EQ(t(2, 2), 6.0);

    EXPECT_THROW(t(1, 0), std::invalid_argument);
}

TEST(TestTriangle, test_from_matrix_upper) {
    Matrix<double> m(3, 3);
    m[0][0] = 1.0; m[0][1] = 0.0; m[0][2] = 0.0;
    m[1][0] = 2.0; m[1][1] = 3.0; m[1][2] = 0.0;
    m[2][0] = 4.0; m[2][1] = 5.0; m[2][2] = 6.0;

    Triangle<double> t(m, TriangleType::Upper);

    EXPECT_DOUBLE_EQ(t(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(t(1, 0), 2.0);
    EXPECT_DOUBLE_EQ(t(1, 1), 3.0);
    EXPECT_DOUBLE_EQ(t(2, 0), 4.0);
    EXPECT_DOUBLE_EQ(t(2, 1), 5.0);
    EXPECT_DOUBLE_EQ(t(2, 2), 6.0);

    EXPECT_THROW(t(0, 1), std::invalid_argument);
}

TEST(TestTriangle, test_from_matrix_invalid) {
    Matrix<double> m(2, 3);
    EXPECT_THROW(Triangle<double> t(m, TriangleType::Lower), std::invalid_argument);
}

TEST(TestTriangle, test_addition_lower) {
    Triangle<int> t1(2, 0, TriangleType::Lower);
    Triangle<int> t2(2, 0, TriangleType::Lower);

    t1(0, 0) = 1; t1(0, 1) = 2;
    t1(1, 1) = 3;

    t2(0, 0) = 4; t2(0, 1) = 5;
    t2(1, 1) = 6;

    Triangle<int> result = t1 + t2;

    EXPECT_EQ(result(0, 0), 5);
    EXPECT_EQ(result(0, 1), 7);
    EXPECT_EQ(result(1, 1), 9);
}

TEST(TestTriangle, test_addition_upper) {
    Triangle<int> t1(2, 0, TriangleType::Upper);
    Triangle<int> t2(2, 0, TriangleType::Upper);

    t1(0, 0) = 1;
    t1(1, 0) = 2; t1(1, 1) = 3;

    t2(0, 0) = 4;
    t2(1, 0) = 5; t2(1, 1) = 6;

    Triangle<int> result = t1 + t2;

    EXPECT_EQ(result(0, 0), 5);
    EXPECT_EQ(result(1, 0), 7);
    EXPECT_EQ(result(1, 1), 9);
}

TEST(TestTriangle, test_addition_mismatch) {
    Triangle<int> t1(2, 0, TriangleType::Lower);
    Triangle<int> t2(3, 0, TriangleType::Lower);
    Triangle<int> t3(2, 0, TriangleType::Upper);

    EXPECT_THROW(t1 + t2, std::invalid_argument);
    EXPECT_THROW(t1 + t3, std::invalid_argument);
}

TEST(TestTriangle, test_compact_storage_lower) {
    Triangle<int> t(3, 0, TriangleType::Lower);

    EXPECT_EQ(t[0].size(), 3);
    EXPECT_EQ(t[1].size(), 2);
    EXPECT_EQ(t[2].size(), 1);
}

TEST(TestTriangle, test_compact_storage_upper) {
    Triangle<int> t(3, 0, TriangleType::Upper);

    EXPECT_EQ(t[0].size(), 1);
    EXPECT_EQ(t[1].size(), 2);
    EXPECT_EQ(t[2].size(), 3);
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
