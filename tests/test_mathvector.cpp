

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
TEST(TestMathVector, test_assignment_operator_add_val) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    MathVector<int> c;
    c = a + 2;
    ASSERT_EQ(c[0], 3);
    ASSERT_EQ(c[1], 4);
    ASSERT_EQ(c[2], 5);
}

TEST(TestMathVector, test_assignment_operator_sub) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    MathVector<int> b;
    b.push_back(4);
    b.push_back(5);
    b.push_back(6);

    MathVector<int> c;
    c = a - b;
    ASSERT_EQ(c[0], -3);
    ASSERT_EQ(c[1], -3);
    ASSERT_EQ(c[2], -3);
}
TEST(TestMathVector, test_assignment_operator_sub_val) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    MathVector<int> c;
    c = a - 1;
    ASSERT_EQ(c[0], 0);
    ASSERT_EQ(c[1], 1);
    ASSERT_EQ(c[2], 2);
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
TEST(TestMathVector, test_assignment_operator_int_div) {
    MathVector<int> a;
    a.push_back(3);
    a.push_back(6);
    a.push_back(9);

    MathVector<int> b;
    b.push_back(3);
    b.push_back(3);
    b.push_back(3);

    MathVector<int> c;
    c = a / b;
    ASSERT_EQ(c[0], 1);
    ASSERT_EQ(c[1], 2);
    ASSERT_EQ(c[2], 3);
}
TEST(TestMathVector, test_assignment_operator_float_div) {
    MathVector<float> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(4);

    MathVector<float> b;
    b.push_back(3);
    b.push_back(2);
    b.push_back(3);

    MathVector<float> c;
    c = a / b;
    ASSERT_EQ(c[0], 0.333333343f);
    ASSERT_EQ(c[1], 1);
    ASSERT_EQ(c[2], 1.333333343f);
}

TEST(TestMathVector, test_assignment_operator_div_zero) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(4);
    MathVector<int> b;
    b.push_back(0);
    b.push_back(0);
    b.push_back(0);

    ASSERT_THROW(a / b, std::invalid_argument);
    ASSERT_THROW(a / b, std::invalid_argument);
    ASSERT_THROW(a / b, std::invalid_argument);
}

TEST(TestMathVector, test_assignment_operator_int_div_value) {
    MathVector<int> a;
    a.push_back(3);
    a.push_back(6);
    a.push_back(9);

    MathVector<int> c;
    c = a / 3;
    ASSERT_EQ(c[0], 1);
    ASSERT_EQ(c[1], 2);
    ASSERT_EQ(c[2], 3);
}
TEST(TestMathVector, test_assignment_operator_float_div_value) {
    MathVector<float> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(4);

    MathVector<float> c;
    c = a / 3;
    ASSERT_EQ(c[0], 0.333333343f);
    ASSERT_EQ(c[1], 0.666666676f);
    ASSERT_EQ(c[2], 1.333333343f);
}
TEST(TestMathVector, test_assignment_operator_div_value_zero) {
    MathVector<float> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(4);

    ASSERT_THROW(a / 0, std::invalid_argument);
    ASSERT_THROW(a / 0, std::invalid_argument);
    ASSERT_THROW(a / 0, std::invalid_argument);
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

TEST(TestMathVector, test_plus_equals_scalar) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    a += 5;
    ASSERT_EQ(a[0], 6);
    ASSERT_EQ(a[1], 7);
    ASSERT_EQ(a[2], 8);
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

TEST(TestMathVector, test_minus_equals_scalar) {
    MathVector<int> a;
    a.push_back(5);
    a.push_back(10);
    a.push_back(15);

    a -= 2;
    ASSERT_EQ(a[0], 3);
    ASSERT_EQ(a[1], 8);
    ASSERT_EQ(a[2], 13);
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

TEST(TestMathVector, test_divide_equals_scalar) {
    MathVector<int> a;
    a.push_back(6);
    a.push_back(9);
    a.push_back(12);

    a /= 3;
    ASSERT_EQ(a[0], 2);
    ASSERT_EQ(a[1], 3);
    ASSERT_EQ(a[2], 4);
}

TEST(TestMathVector, test_divide_equals_scalar_float) {
    MathVector<float> a;
    a.push_back(1.0f);
    a.push_back(2.0f);
    a.push_back(4.0f);

    a /= 2.0f;
    ASSERT_NEAR(a[0], 0.5f, EPSILON);
    ASSERT_NEAR(a[1], 1.0f, EPSILON);
    ASSERT_NEAR(a[2], 2.0f, EPSILON);
}

TEST(TestMathVector, test_divide_equals_zero) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    ASSERT_THROW(a /= 0, std::invalid_argument);
}

TEST(TestMathVector, test_compound_operations) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    a += 5;
    ASSERT_EQ(a[0], 6);
    ASSERT_EQ(a[1], 7);
    ASSERT_EQ(a[2], 8);

    a *= 2;
    ASSERT_EQ(a[0], 12);
    ASSERT_EQ(a[1], 14);
    ASSERT_EQ(a[2], 16);

    a -= 4;
    ASSERT_EQ(a[0], 8);
    ASSERT_EQ(a[1], 10);
    ASSERT_EQ(a[2], 12);

    a /= 2;
    ASSERT_EQ(a[0], 4);
    ASSERT_EQ(a[1], 5);
    ASSERT_EQ(a[2], 6);
}

TEST(TestMathVector, test_plus_equals_empty) {
    MathVector<int> a;
    MathVector<int> b;

    a += b; 
    ASSERT_EQ(a.size(), 0);

    a += 5; 
    ASSERT_EQ(a.size(), 0);
}

TEST(TestMathVector, test_minus_equals_empty) {
    MathVector<int> a;
    MathVector<int> b;

    a -= b; 
    ASSERT_EQ(a.size(), 0);

    a -= 5; 
    ASSERT_EQ(a.size(), 0);
}

TEST(TestMathVector, test_multiply_equals_empty) {
    MathVector<int> a;

    a *= 5; 
    ASSERT_EQ(a.size(), 0);
}

TEST(TestMathVector, test_divide_equals_empty) {
    MathVector<int> a;

    a /= 5; 
    ASSERT_EQ(a.size(), 0);
}



TEST(TestMathVector, test_friend_operator_add_scalar_left) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    MathVector<int> c = 5 + a;
    ASSERT_EQ(c[0], 6);
    ASSERT_EQ(c[1], 7);
    ASSERT_EQ(c[2], 8);
}

TEST(TestMathVector, test_friend_operator_add_scalar_left_float) {
    MathVector<float> a;
    a.push_back(1.5f);
    a.push_back(2.5f);
    a.push_back(3.5f);

    MathVector<float> c = 2.5f + a;
    ASSERT_NEAR(c[0], 4.0f, EPSILON);
    ASSERT_NEAR(c[1], 5.0f, EPSILON);
    ASSERT_NEAR(c[2], 6.0f, EPSILON);
}

TEST(TestMathVector, test_friend_operator_mult_scalar_left) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    MathVector<int> c = 3 * a;
    ASSERT_EQ(c[0], 3);
    ASSERT_EQ(c[1], 6);
    ASSERT_EQ(c[2], 9);
}

TEST(TestMathVector, test_friend_operator_mult_scalar_left_float) {
    MathVector<float> a;
    a.push_back(1.5f);
    a.push_back(2.0f);
    a.push_back(2.5f);

    MathVector<float> c = 2.0f * a;
    ASSERT_NEAR(c[0], 3.0f, EPSILON);
    ASSERT_NEAR(c[1], 4.0f, EPSILON);
    ASSERT_NEAR(c[2], 5.0f, EPSILON);
}

TEST(TestMathVector, test_friend_operator_add_scalar_left_empty) {
    MathVector<int> a;
    MathVector<int> c = 5 + a;
    ASSERT_EQ(c.size(), 0);
}

TEST(TestMathVector, test_friend_operator_mult_scalar_left_empty) {
    MathVector<int> a;
    MathVector<int> c = 3 * a;
    ASSERT_EQ(c.size(), 0);
}

TEST(TestMathVector, test_friend_operator_add_scalar_left_single_element) {
    MathVector<int> a;
    a.push_back(10);

    MathVector<int> c = 5 + a;
    ASSERT_EQ(c.size(), 1);
    ASSERT_EQ(c[0], 15);
}

TEST(TestMathVector, test_friend_operator_mult_scalar_left_single_element) {
    MathVector<int> a;
    a.push_back(7);

    MathVector<int> c = 2 * a;
    ASSERT_EQ(c.size(), 1);
    ASSERT_EQ(c[0], 14);
}

TEST(TestMathVector, test_friend_operator_add_scalar_left_zero) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    MathVector<int> c = 0 + a;
    ASSERT_EQ(c[0], 1);
    ASSERT_EQ(c[1], 2);
    ASSERT_EQ(c[2], 3);
}

TEST(TestMathVector, test_friend_operator_mult_scalar_left_zero) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    MathVector<int> c = 0 * a;
    ASSERT_EQ(c[0], 0);
    ASSERT_EQ(c[1], 0);
    ASSERT_EQ(c[2], 0);
}

TEST(TestMathVector, test_friend_operator_mult_scalar_left_negative) {
    MathVector<int> a;
    a.push_back(1);
    a.push_back(-2);
    a.push_back(3);

    MathVector<int> c = -2 * a;
    ASSERT_EQ(c[0], -2);
    ASSERT_EQ(c[1], 4);
    ASSERT_EQ(c[2], -6);
}