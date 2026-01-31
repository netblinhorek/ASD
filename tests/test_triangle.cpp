#include <gtest/gtest.h>
#include "../lib_Triangle/triangle.h"
#include <stdexcept>
#include <cmath>

TEST(TestTriangle, test_default_constructor) {
    Triangle<double> t;
    EXPECT_EQ(t.size(), 0);  
    EXPECT_EQ(t.rows(), 0);
    EXPECT_EQ(t.cols(), 0);
}

TEST(TestTriangle, test_size_constructor) {
    Triangle<int> t(3);
    EXPECT_EQ(t.size(), 3);  
    EXPECT_EQ(t.rows(), 3);
    EXPECT_EQ(t.cols(), 3);

    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(t[i].size(), 3);
    }
}

TEST(TestTriangle, test_copy_constructor) {
    Triangle<int> t1(3);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3 - i; ++j) {
            t1[i][j] = i * 10 + j;
        }
    }

    Triangle<int> t2(t1);
    EXPECT_EQ(t2.size(), 3);
    EXPECT_EQ(t2.rows(), 3);
    EXPECT_EQ(t2.cols(), 3);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3 - i; ++j) {
            EXPECT_EQ(t2[i][j], i * 10 + j);
        }
    }
}

TEST(TestTriangle, test_assignment_operator) {
    Triangle<int> t1(3);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3 - i; ++j) {
            t1[i][j] = i * 10 + j;
        }
    }

    Triangle<int> t2(2);
    t2 = t1;

    EXPECT_EQ(t2.size(), 3);
    EXPECT_EQ(t2.rows(), 3);
    EXPECT_EQ(t2.cols(), 3);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3 - i; ++j) {
            EXPECT_EQ(t2[i][j], i * 10 + j);
        }
    }
}

TEST(TestTriangle, test_addition) {
    Triangle<int> t1(3);
    Triangle<int> t2(3);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3 - i; ++j) {
            t1[i][j] = i * 10 + j;
            t2[i][j] = (i * 10 + j) * 2;
        }
    }

    Triangle<int> result = t1 + t2;

    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 3);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3 - i; ++j) {
            EXPECT_EQ(result[i][j], (i * 10 + j) * 3);
        }
    }
}

TEST(TestTriangle, test_addition_mismatch_sizes) {
    Triangle<int> t1(2);
    Triangle<int> t2(3);

    EXPECT_THROW(t1 + t2, std::logic_error);
}

TEST(TestTriangle, test_subtraction) {
    Triangle<int> t1(3);
    Triangle<int> t2(3);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3 - i; ++j) {
            t1[i][j] = (i * 10 + j) * 3;
            t2[i][j] = i * 10 + j;
        }
    }

    Triangle<int> result = t1 - t2;

    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 3);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3 - i; ++j) {
            EXPECT_EQ(result[i][j], (i * 10 + j) * 2);
        }
    }
}

TEST(TestTriangle, test_subtraction_identity) {
    Triangle<double> t(3);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3 - i; ++j) {
            t[i][j] = i * 1.5 + j * 0.5;
        }
    }

    Triangle<double> result = t - t;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3 - i; ++j) {
            EXPECT_DOUBLE_EQ(result[i][j], 0.0);
        }
    }
}

TEST(TestTriangle, test_scalar_multiplication) {
    Triangle<double> t(3);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3 - i; ++j) {
            t[i][j] = i * 1.0 + j * 0.5;
        }
    }

    Triangle<double> result = t * 2.5;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3 - i; ++j) {
            EXPECT_DOUBLE_EQ(result[i][j], (i * 1.0 + j * 0.5) * 2.5);
        }
    }
}

TEST(TestTriangle, test_scalar_multiplication_zero) {
    Triangle<double> t(3);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3 - i; ++j) {
            t[i][j] = i * 2.0 + j * 3.0;
        }
    }

    Triangle<double> result = t * 0.0;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3 - i; ++j) {
            EXPECT_DOUBLE_EQ(result[i][j], 0.0);
        }
    }
}

TEST(TestTriangle, test_vector_multiplication_simple) {
    Triangle<double> t(2);
    MathVector<double> v(2);

    t[0][0] = 1.0;
    t[1][0] = 2.0;
    t[1][1] = 3.0;

    v[0] = 1.0;
    v[1] = 2.0;

    MathVector<double> result = t * v;

    EXPECT_EQ(result.size(), 2);
    EXPECT_DOUBLE_EQ(result[0], 1.0);
    EXPECT_DOUBLE_EQ(result[1], 8.0);
}

TEST(TestTriangle, test_vector_multiplication_wrong_size) {
    Triangle<double> t(3);
    MathVector<double> v(2);

    EXPECT_THROW(t * v, std::logic_error);
}

TEST(TestTriangle, test_equality_operator) {
    Triangle<int> t1(3);
    Triangle<int> t2(3);
    Triangle<int> t3(2);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3 - i; ++j) {
            t1[i][j] = i * 10 + j;
            t2[i][j] = i * 10 + j;
        }
    }

    EXPECT_TRUE(t1 == t2);
    EXPECT_FALSE(t1 == t3);
    EXPECT_TRUE(t1 == t1); 
}

TEST(TestTriangle, test_inequality_operator) {
    Triangle<int> t1(3);
    Triangle<int> t2(3);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3 - i; ++j) {
            t1[i][j] = i * 10 + j;
            t2[i][j] = i * 10 + j + 1;
        }
    }

    EXPECT_TRUE(t1 != t2);
    EXPECT_FALSE(t1 != t1);
}

TEST(TestTriangle, test_multiplication_assignment) {
    Triangle<double> t(3);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3 - i; ++j) {
            t[i][j] = i * 1.0 + j * 0.5;
        }
    }

    t *= 2.0;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3 - i; ++j) {
            EXPECT_DOUBLE_EQ(t[i][j], (i * 1.0 + j * 0.5) * 2.0);
        }
    }
}

TEST(TestTriangle, test_mixed_operations) {
    Triangle<double> A(2);
    Triangle<double> B(2);

    A[0][0] = 5.0; A[0][1] = 0.5; 
    A[1][0] = 2.0;                

    B[0][0] = 1.0; B[0][1] = 0.2;
    B[1][0] = 1.0;

    Triangle<double> result = (A * 2.0) - (B * 3.0);

    EXPECT_DOUBLE_EQ(result[0][0], 7.0);   
    EXPECT_DOUBLE_EQ(result[0][1], 0.4);   
    EXPECT_DOUBLE_EQ(result[1][0], 1.0);   
}