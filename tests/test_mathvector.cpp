#include <gtest/gtest.h>
#include "mathvector.h"
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
#define EPSILON 0.000001


TEST(TestMathVector, test_copy_constructor) {
    // Arrange
    MathVector<int> original;
    original.push_back(10);
    original.push_back(20);
    original.push_back(30);

    // Act
    MathVector<int> copy(original);

    ASSERT_EQ(copy.size(), original.size());
    for (size_t i = 0; i < original.size(); ++i) {
        ASSERT_EQ(copy[i], original[i]);
    }

    original.set(0, 99);
    original.push_back(40);

    ASSERT_EQ(original.size(), 4);
    ASSERT_EQ(copy.size(), 3); 
    ASSERT_EQ(copy[0], 10);   
    ASSERT_EQ(original[0], 99);
}


TEST(TestMathVector, test_assignment_operator) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    MathVector<int> b;
    b.push_back(4);
    b.push_back(5);
    b.push_back(6);

    a = b;

    ASSERT_EQ(a.size(), b.size());
    for (size_t i = 0; i < a.size(); ++i) {
        ASSERT_EQ(a[i], b[i]);
    }
    ASSERT_EQ(a[0], 4);
    ASSERT_EQ(a[1], 5);
    ASSERT_EQ(a[2], 6);
}

TEST(TestMathVector, test_assignment_operator_add_vec) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    MathVector<int> b;
    b.push_back(4);
    b.push_back(5);
    b.push_back(6);

    MathVector<int> c;
    c = a + b;
    ASSERT_EQ(c[0], 5);
    ASSERT_EQ(c[1], 7);
    ASSERT_EQ(c[2], 9);
}




TEST(TestMathVector, test_assignment_operator_mult) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    MathVector<int> b;
    b.push_back(4);
    b.push_back(5);
    b.push_back(6);

    MathVector<int> c;
    c = a * b;
    ASSERT_EQ(c[0], 4);
    ASSERT_EQ(c[1], 10);
    ASSERT_EQ(c[2], 18);
}
TEST(TestMathVector, test_assignment_operator_mult_value) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    MathVector<int> c;
    c = a * 3;
    ASSERT_EQ(c[0], 3);
    ASSERT_EQ(c[1], 6);
    ASSERT_EQ(c[2], 9);
}


TEST(TestMathVector, test_plus_equals_vector) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    MathVector<int> b;
    b.push_back(4);
    b.push_back(5);
    b.push_back(6);

    a += b;
    ASSERT_EQ(a[0], 5);
    ASSERT_EQ(a[1], 7);
    ASSERT_EQ(a[2], 9);
}



TEST(TestMathVector, test_minus_equals_vector) {
    MathVector<int> a;
    a.push_back(10);
    a.push_back(20);
    a.push_back(30);

    MathVector<int> b;
    b.push_back(1);
    b.push_back(2);
    b.push_back(3);

    a -= b;
    ASSERT_EQ(a[0], 9);
    ASSERT_EQ(a[1], 18);
    ASSERT_EQ(a[2], 27);
}


TEST(TestMathVector, test_multiply_equals_scalar) {
    MathVector<int> a;
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);

    a *= 3;
    ASSERT_EQ(a[0], 6);
    ASSERT_EQ(a[1], 9);
    ASSERT_EQ(a[2], 12);
}

TEST(TestMathVector, test_multiply_equals_scalar_float) {
    MathVector<float> a;
    a.push_back(1.5f);
    a.push_back(2.5f);
    a.push_back(3.5f);

    a *= 2.0f;
    ASSERT_NEAR(a[0], 3.0f, EPSILON);
    ASSERT_NEAR(a[1], 5.0f, EPSILON);
    ASSERT_NEAR(a[2], 7.0f, EPSILON);
}


TEST(TestMathVector, test_plus_equals_empty) {
    MathVector<int> a;
    MathVector<int> b;

    a += b; 
    ASSERT_EQ(a.size(), 0);
    a -= b;
    ASSERT_EQ(a.size(), 0);
    a *= 5;
    ASSERT_EQ(a.size(), 0);

}


TEST(TestMathVector, test_friend_operator_mult_scalar_left) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    MathVector<int> c;
    c = 3 * a;
    ASSERT_EQ(c[0], 3);
    ASSERT_EQ(c[1], 6);
    ASSERT_EQ(c[2], 9);
}

TEST(TestMathVector, test_friend_operator_mult_scalar_left_float) {
    MathVector<float> a;
    a.push_back(1.5f);
    a.push_back(2.0f);
    a.push_back(2.5f);

    MathVector<float> c;
    c = 2.0f * a;
    ASSERT_NEAR(c[0], 3.0f, EPSILON);
    ASSERT_NEAR(c[1], 4.0f, EPSILON);
    ASSERT_NEAR(c[2], 5.0f, EPSILON);
}


TEST(TestMathVector, test_friend_operator_mult_scalar_left_empty) {
    MathVector<int> a;
    MathVector<int> c;
    c = 3 * a;
    ASSERT_EQ(c.size(), 0);
}


TEST(TestMathVector, test_friend_operator_mult_scalar_left_single_element) {
    MathVector<int> a;
    a.push_back(7);

    MathVector<int> c;
    c = 2 * a;
    ASSERT_EQ(c.size(), 1);
    ASSERT_EQ(c[0], 14);
}


TEST(TestMathVector, test_friend_operator_mult_scalar_left_zero) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    MathVector<int> c;
    c = 0 * a;
    ASSERT_EQ(c[0], 0);
    ASSERT_EQ(c[1], 0);
    ASSERT_EQ(c[2], 0);
}

TEST(TestMathVector, test_friend_operator_mult_scalar_left_negative) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(-2);
    a.push_back(3);

    MathVector<int> c;
    c = -2 * a;
    ASSERT_EQ(c[0], -2);
    ASSERT_EQ(c[1], 4);
    ASSERT_EQ(c[2], -6);
}

TEST(TestMathVector, test_differentiation_mathvectors_add) {
    MathVector<float> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(4);
    MathVector<float> b;
    b.push_back(4);
    b.push_back(6);

    ASSERT_THROW(a + b, std::invalid_argument);
    ASSERT_THROW(a + b, std::invalid_argument);
    ASSERT_THROW(a + b, std::invalid_argument);
}

TEST(TestMathVector, test_differentiation_mathvectors_sub) {
    MathVector<float> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(4);
    MathVector<float> b;
    b.push_back(4);
    b.push_back(6);

    ASSERT_THROW(a - b, std::invalid_argument);
   
}
TEST(TestMathVector, test_differentiation_mathvectors_mult) {
    MathVector<float> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(4);
    MathVector<float> b;
    b.push_back(4);
    b.push_back(6);

    ASSERT_THROW(a * b, std::invalid_argument);
    
}


TEST(TestMathVector, test_the_scalar_product_product_basic) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    MathVector<int> b;
    b.push_back(4);
    b.push_back(5);
    b.push_back(6);

    int result = a.the_scalar_product(b);
    ASSERT_EQ(result, 32);
}

TEST(TestMathVector, test_the_scalar_product_product_zeros) {
    MathVector<int> a;
    a.push_back(0);
    a.push_back(0);
    a.push_back(0);

    MathVector<int> b;
    b.push_back(1);
    b.push_back(2);
    b.push_back(3);

    int result = a.the_scalar_product(b);
    ASSERT_EQ(result, 0); 
}

TEST(TestMathVector, test_the_scalar_product_product_negative) {
    MathVector<int> a;
    a.push_back(-1);
    a.push_back(-2);
    a.push_back(-3);

    MathVector<int> b;
    b.push_back(4);
    b.push_back(5);
    b.push_back(6);

    int result = a.the_scalar_product(b);
    ASSERT_EQ(result, -32); 
}

TEST(TestMathVector, test_the_scalar_product_product_float) {
    MathVector<float> a;
    a.push_back(1.5f);
    a.push_back(2.5f);
    a.push_back(3.5f);

    MathVector<float> b;
    b.push_back(2.0f);
    b.push_back(3.0f);
    b.push_back(4.0f);

    float result = a.the_scalar_product(b);
    ASSERT_NEAR(result, 24.5f, EPSILON); 
}

TEST(TestMathVector, test_the_scalar_product_product_single_element) {
    MathVector<int> a;
    a.push_back(5);

    MathVector<int> b;
    b.push_back(7);

    int result = a.the_scalar_product(b);
    ASSERT_EQ(result, 35); 
}

TEST(TestMathVector, test_the_scalar_product_product_empty) {
    MathVector<int> a;
    MathVector<int> b;

    int result = a.the_scalar_product(b);
    ASSERT_EQ(result, 0); 
}

TEST(TestMathVector, test_the_scalar_product_product_different_sizes) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(2);

    MathVector<int> b;
    b.push_back(3);
    b.push_back(4);
    b.push_back(5);

    ASSERT_THROW(a.the_scalar_product(b), std::invalid_argument);
}

TEST(TestMathVector, test_the_scalar_product_product_commutative) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    MathVector<int> b;
    b.push_back(4);
    b.push_back(5);
    b.push_back(6);

    ASSERT_EQ(a.the_scalar_product(b), b.the_scalar_product(a));
}

TEST(TestMathVector, test_the_scalar_product_product_orthogonal) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(0);

    MathVector<int> b;
    b.push_back(0);
    b.push_back(1);

    int result = a.the_scalar_product(b);
    ASSERT_EQ(result, 0); 
}

TEST(TestMathVector, test_the_scalar_product_product_self) {
    MathVector<int> a;
    a.push_back(3);
    a.push_back(4);

    int result = a.the_scalar_product(a);
    ASSERT_EQ(result, 25);
}

TEST(TestMathVector, test_norm_basic) {
    MathVector<int> a;
    a.push_back(3);
    a.push_back(4);

    double result = a.norm();
    ASSERT_NEAR(result, 5.0, EPSILON); 
}

TEST(TestMathVector, test_norm_zeros) {
    MathVector<int> a;
    a.push_back(0);
    a.push_back(0);
    a.push_back(0);

    double result = a.norm();
    ASSERT_NEAR(result, 0.0, EPSILON); 
}

TEST(TestMathVector, test_norm_single_element) {
    MathVector<int> a;
    a.push_back(5);

    double result = a.norm();
    ASSERT_NEAR(result, 5.0, EPSILON); 
}

TEST(TestMathVector, test_norm_negative) {
    MathVector<int> a;
    a.push_back(-3);
    a.push_back(-4);

    double result = a.norm();
    ASSERT_NEAR(result, 5.0, EPSILON); 
}

TEST(TestMathVector, test_norm_float) {
    MathVector<float> a;
    a.push_back(1.0f);
    a.push_back(1.0f);

    float result = a.norm();
    ASSERT_NEAR(result, sqrt(2.0f), EPSILON); 
}

TEST(TestMathVector, test_norm_3d) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(2);

    double result = a.norm();
    ASSERT_NEAR(result, 3.0, EPSILON); 
}

TEST(TestMathVector, test_norm_empty) {
    MathVector<int> a;

    double result = a.norm();
    ASSERT_NEAR(result, 0.0, EPSILON);
}

TEST(TestMathVector, test_norm_large_numbers) {
    MathVector<double> a;
    a.push_back(1000.0);
    a.push_back(2000.0);

    double result = a.norm();
    ASSERT_NEAR(result, sqrt(1000000.0 + 4000000.0), EPSILON);
}

TEST(TestMathVector, test_norm_unit_vector) {
    MathVector<double> a;
    a.push_back(1.0 / sqrt(2.0));
    a.push_back(1.0 / sqrt(2.0));

    double result = a.norm();
    ASSERT_NEAR(result, 1.0, EPSILON); 
}
TEST(TestMathVector, test_normalized_basic) {
    MathVector<double> a;
    a.push_back(3.0);
    a.push_back(4.0);

    MathVector<double> result = a.normalized();

    ASSERT_NEAR(result[0], 0.6, EPSILON);
    ASSERT_NEAR(result[1], 0.8, EPSILON);

    ASSERT_NEAR(result.norm(), 1.0, EPSILON);
}

TEST(TestMathVector, test_normalized_float) {
    MathVector<float> a;
    a.push_back(2.0f);
    a.push_back(0.0f);

    MathVector<float> result = a.normalized();

    ASSERT_NEAR(result[0], 1.0f, EPSILON);
    ASSERT_NEAR(result[1], 0.0f, EPSILON);
    ASSERT_NEAR(result.norm(), 1.0f, EPSILON);
}

TEST(TestMathVector, test_normalized_3d) {
    MathVector<double> a;
    a.push_back(1.0);
    a.push_back(2.0);
    a.push_back(2.0);

    MathVector<double> result = a.normalized();
    double length = sqrt(1.0 + 4.0 + 4.0); 

    ASSERT_NEAR(result[0], 1.0 / 3.0, EPSILON);
    ASSERT_NEAR(result[1], 2.0 / 3.0, EPSILON);
    ASSERT_NEAR(result[2], 2.0 / 3.0, EPSILON);
    ASSERT_NEAR(result.norm(), 1.0, EPSILON);
}

TEST(TestMathVector, test_normalized_already_unit) {
    MathVector<double> a;
    a.push_back(1.0 / sqrt(2.0));
    a.push_back(1.0 / sqrt(2.0));

    MathVector<double> result = a.normalized();

    ASSERT_NEAR(result[0], 1.0 / sqrt(2.0), EPSILON);
    ASSERT_NEAR(result[1], 1.0 / sqrt(2.0), EPSILON);
    ASSERT_NEAR(result.norm(), 1.0, EPSILON);
}

TEST(TestMathVector, test_normalized_negative) {
    MathVector<double> a;
    a.push_back(-3.0);
    a.push_back(-4.0);

    MathVector<double> result = a.normalized();

    ASSERT_NEAR(result[0], -0.6, EPSILON);
    ASSERT_NEAR(result[1], -0.8, EPSILON);
    ASSERT_NEAR(result.norm(), 1.0, EPSILON);
}

TEST(TestMathVector, test_normalized_single_element) {
    MathVector<double> a;
    a.push_back(5.0);

    MathVector<double> result = a.normalized();

    ASSERT_NEAR(result[0], 1.0, EPSILON);
    ASSERT_NEAR(result.norm(), 1.0, EPSILON);
}

TEST(TestMathVector, test_normalized_zero_vector) {
    MathVector<double> a;
    a.push_back(0.0);
    a.push_back(0.0);
    a.push_back(0.0);

    ASSERT_THROW(a.normalized(), std::invalid_argument); 
}

TEST(TestMathVector, test_normalized_empty) {
    MathVector<double> a;

    ASSERT_THROW(a.normalized(), std::invalid_argument); 
}

TEST(TestMathVector, test_normalized_preserves_direction) {
    MathVector<double> a;
    a.push_back(6.0);
    a.push_back(8.0);

    MathVector<double> normalized = a.normalized();

    double ratio_original = a[0] / a[1];
    double ratio_normalized = normalized[0] / normalized[1];

    ASSERT_NEAR(ratio_original, ratio_normalized, EPSILON);
}

TEST(TestMathVector, test_friend_operator_output_stream) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    std::stringstream ss;
    ss << a;
    ASSERT_EQ(ss.str(), "[1, 2, 3]");
}

TEST(TestMathVector, test_friend_operator_output_stream_single_element) {
    MathVector<int> a;
    a.push_back(42);

    std::stringstream ss;
    ss << a;
    ASSERT_EQ(ss.str(), "[42]");
}

TEST(TestMathVector, test_friend_operator_output_stream_float) {
    MathVector<float> a;
    a.push_back(1.5f);
    a.push_back(2.7f);
    a.push_back(3.1f);

    std::stringstream ss;
    ss << a;
    ASSERT_EQ(ss.str(), "[1.5, 2.7, 3.1]");
}

TEST(TestMathVector, test_friend_operator_output_stream_double) {
    MathVector<double> a;
    a.push_back(1.23);
    a.push_back(4.56);
    a.push_back(7.89);

    std::stringstream ss;
    ss << a;
    ASSERT_EQ(ss.str(), "[1.23, 4.56, 7.89]");
}

TEST(TestMathVector, test_friend_operator_output_stream_string) {
    MathVector<std::string> a;
    a.push_back("hello");
    a.push_back("world");
    a.push_back("test");

    std::stringstream ss;
    ss << a;
    ASSERT_EQ(ss.str(), "[hello, world, test]");
}

TEST(TestMathVector, test_friend_operator_output_stream_negative_numbers) {
    MathVector<int> a;
    a.push_back(-1);
    a.push_back(-2);
    a.push_back(-3);

    std::stringstream ss;
    ss << a;
    ASSERT_EQ(ss.str(), "[-1, -2, -3]");
}

TEST(TestMathVector, test_friend_operator_output_stream_large_vector) {
    MathVector<int> a;
    for (int i = 1; i <= 5; i++) {
        a.push_back(i * 10);
    }

    std::stringstream ss;
    ss << a;
    ASSERT_EQ(ss.str(), "[10, 20, 30, 40, 50]");
}

TEST(TestMathVector, test_unary_minus) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(-2);
    a.push_back(3);

    MathVector<int> b = -a;

    ASSERT_EQ(b.size(), 3);
    ASSERT_EQ(b[0], -1);   
    ASSERT_EQ(b[1], 2);    
    ASSERT_EQ(b[2], -3);   
}
TEST(TestMathVector, test_twice_unary_minus) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(-2);
    a.push_back(3);

    MathVector<int> b;
    b = -a;
    MathVector<int> c;
    c = -b;

    ASSERT_EQ(c.size(), 3);
    ASSERT_EQ(c[0], 1);
    ASSERT_EQ(c[1], -2);
    ASSERT_EQ(c[2], 3);
}
TEST(TestMathVector, test_twice_unary_plus) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(-2);
    a.push_back(3);

    MathVector<int> b;
    b = +a;
    

    ASSERT_EQ(b.size(), 3);
    ASSERT_EQ(b[0], 1);
    ASSERT_EQ(b[1], -2);
    ASSERT_EQ(b[2], 3);
}

TEST(TestMathVector, test_start_index_without_zeros) {
    MathVector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);
    EXPECT_EQ(vec1.start_index(), 0);
}

TEST(TestMathVector, test_start_index_with_zeros) {
    MathVector<int> vec1;
    vec1.push_back(0);
    vec1.push_back(0);
    vec1.push_back(5);
    vec1.push_back(6);
    vec1.push_back(7);
    EXPECT_EQ(vec1.start_index(), 2);
}
