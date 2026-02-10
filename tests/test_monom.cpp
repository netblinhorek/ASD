#include <gtest/gtest.h>
#include "../lib_Monom/monom.h"

#define EPSILON 0.000001

TEST(TestMonom, test_monom_default_constructor_empty) {
    Monom monom;

    ASSERT_DOUBLE_EQ(monom.get_coeff(), 0.0); 
    for (int i = 0; i < VARS_COUNT; ++i) {
        ASSERT_EQ(monom.get_power(i), 0);  
    }
}

TEST(TestMonom, test_monom_default_constructor_with_data) {
    Monom monom;

    monom.set_power(0, 2);
    monom.set_power(1, 3);
    monom.set_power(2, 4);

    ASSERT_EQ(monom.get_power(0), 2);
    ASSERT_EQ(monom.get_power(1), 3);
    ASSERT_EQ(monom.get_power(2), 4);
}
TEST(TestMonom, test_monom_copy_constructor) {

    Monom monom_original(5.0);
    monom_original.set_power(0, 1);
    monom_original.set_power(1, 2);
    
    Monom monom_copy = monom_original;

    ASSERT_DOUBLE_EQ(monom_copy.get_coeff(), 5.0);
    ASSERT_EQ(monom_copy.get_power(0), 1);
    ASSERT_EQ(monom_copy.get_power(1), 2);
    ASSERT_EQ(monom_copy.get_power(2), 0);

    monom_original.set_power(0, 99);
    ASSERT_EQ(monom_original.get_power(0), 99);
    ASSERT_EQ(monom_copy.get_power(0), 1);
}

TEST(TestMonom, test_get_coeff) {
    Monom monom;
    ASSERT_DOUBLE_EQ(monom.get_coeff(), 0.0);
}

TEST(TestMonom, test_set_coeff) {
    Monom monom;
    monom.set_coeff(0.4);
    ASSERT_DOUBLE_EQ(monom.get_coeff(), 0.4);
}

TEST(TestMonom, test_get_power) {
    Monom monom;
    ASSERT_EQ(monom.get_power(0), 0);
}

TEST(TestMonom, test_set_power) {
    Monom monom;
    monom.set_power(0, 2);
    ASSERT_EQ(monom.get_power(0), 2);
}

TEST(TestMonom, test_monom_get_variables) {
    Monom m1(2.0, 3, 4, 5);  
    EXPECT_EQ("x^3y^4z^5", m1.get_variables());
}

TEST(TestMonom, test_monom_assignment_operator) {
    Monom a(5.0), b;
    a.set_power(0, 1);
    a.set_power(1, 2);
    b = a;

    ASSERT_DOUBLE_EQ(b.get_coeff(), 5.0);
    ASSERT_EQ(b.get_power(0), 1);
    ASSERT_EQ(b.get_power(1), 2);
    ASSERT_EQ(b.get_power(2), 0);

    a.set_power(0, 99);
    ASSERT_EQ(b.get_power(0), 1);
}

TEST(TestMonom, test_monom_bool_is_like_true) {
    Monom a(5.0), b;
    a.set_power(0, 1);
    a.set_power(1, 2);
    b.set_power(0, 1);
    b.set_power(1, 2);
    bool tmp = a.is_like(b);
    ASSERT_TRUE(tmp);
}

TEST(TestMonom, test_monom_bool_is_like_false) {
    Monom a(5.0), b;
    a.set_power(0, 1);
    a.set_power(1, 2);
    b.set_power(0, 2);
    b.set_power(1, 1);
    bool tmp = a.is_like(b);
    ASSERT_FALSE(tmp);
}

TEST(TestMonom, test_monom_operator_equal_not_equal) {
    Monom a(2.0), b(2.0), c(3.0);
    a.set_power(0, 1);
    b.set_power(0, 1);
    c.set_power(0, 1);
 
    ASSERT_TRUE(a == b);
    ASSERT_FALSE(a != b);
    ASSERT_TRUE(a != c);
}

TEST(TestMonom, test_monom_operator_add_operator) {
    Monom a(3.0), b(2.0);
    a.set_power(0, 2); a.set_power(1, 1);
    b.set_power(0, 2); b.set_power(1, 1);
    a += b;
    ASSERT_NO_THROW(a += b, std::invalid_argument);

    a.set_power(0, 3);
    ASSERT_THROW(a += b, std::invalid_argument);
}

TEST(TestMonom, test_monom_operator_add) {
    Monom a(3.0), b(2.0);
    a.set_power(0, 2); a.set_power(1, 1);
    b.set_power(0, 2); b.set_power(1, 1);
    ASSERT_NO_THROW(a + b, std::invalid_argument);

    a.set_power(0, 3);  
    ASSERT_THROW(a + b, std::invalid_argument);
}

TEST(TestMonom, test_monom_operator_sub_operator) {
    Monom a(5.0), b(2.0);
    a.set_power(0, 1); a.set_power(1, 2);
    b.set_power(0, 1); b.set_power(1, 2);
    a -= b;
    ASSERT_NO_THROW(a -= b, std::invalid_argument);

    a.set_power(0, 3);
    ASSERT_THROW(a -= b, std::invalid_argument);
}

TEST(TestMonom, test_monom_operator_sub) {
    Monom a(5.0), b(2.0);
    a.set_power(0, 1); a.set_power(1, 2);
    b.set_power(0, 1); b.set_power(1, 2);

    Monom c = a - b;
    ASSERT_NO_THROW(a - b, std::invalid_argument);

    a.set_power(0, 3);
    ASSERT_THROW(a - b, std::invalid_argument);
}

TEST(TestMonom, test_monom_operator_mult_operator) {
    Monom a(2.0), b(3.0);
    a.set_power(0, 1); a.set_power(1, 2);
    b.set_power(0, 2); b.set_power(1, 3);

    a *= b;
    ASSERT_DOUBLE_EQ(a.get_coeff(), 6.0);
    ASSERT_EQ(a.get_power(0), 3);
    ASSERT_EQ(a.get_power(1), 5);
    ASSERT_EQ(a.get_power(2), 0);
}

TEST(TestMonom, test_monom_operator_mult) {
    Monom a(2.0), b(3.0);
    a.set_power(0, 1); a.set_power(1, 2);
    b.set_power(0, 2); b.set_power(1, 3);

    Monom c = a * b;
    ASSERT_DOUBLE_EQ(c.get_coeff(), 6.0);
    ASSERT_EQ(c.get_power(0), 3);
    ASSERT_EQ(c.get_power(1), 5);
    ASSERT_EQ(c.get_power(2), 0);
}

TEST(TestMonom, test_monom_operator_div_with_throw_negative) {
    Monom a(1.0, 0, 0, 1);
    Monom b(1.0, 1, 0, 0);
    ASSERT_THROW(a /= b, std::invalid_argument);
}

TEST(TestMonom, test_monom_operator_div_operator) {
    Monom a(4.0, 3, 1, 0);
    Monom b(2.0, 1, 0, 0);
    a /= b;
    ASSERT_DOUBLE_EQ(a.get_coeff(), 2.0);
    ASSERT_EQ(a.get_power(0), 2);
    ASSERT_EQ(a.get_power(1), 1);
    ASSERT_EQ(a.get_power(2), 0);
}

TEST(TestMonom, test_monom_operator_div_with_throw_by_zero) {
    Monom a(1.0, 0, 0, 1);
    Monom b(0.0, 1, 0, 0);
    ASSERT_THROW(a /= b, std::logic_error);
}

TEST(TestMonom, test_monom_operator_div) {
    Monom a(4.0, 3, 2, 1);
    Monom b(2.0, 1, 1, 1);
    Monom c = a / b;

    ASSERT_DOUBLE_EQ(c.get_coeff(), 2.0);
    ASSERT_EQ(c.get_power(0), 2);
    ASSERT_EQ(c.get_power(1), 1);
    ASSERT_EQ(c.get_power(2), 0);
}

TEST(TestMonom, test_monom_operator_div_throw_negative) {
    Monom d(1.0, 0, 0, 1);      
    Monom e(1.0, 1, 0, 0);      

    ASSERT_THROW(d / e, std::invalid_argument);
}

TEST(TestMonom, test_monom_operator_div_throw_by_zero) {
    Monom a(4.0, 3, 2, 1);    
    Monom b(0.0, 1, 0, 0);

    ASSERT_THROW(a / b, std::logic_error);
}

TEST(TestMonom, test_monom_unary_operator) {
    Monom a(1.2, 1, 2, 3), c;
    c = -a;
    ASSERT_DOUBLE_EQ(c.get_coeff(), -1.2);
    ASSERT_EQ(c.get_power(0), 1);
    ASSERT_EQ(c.get_power(1), 2);
    ASSERT_EQ(c.get_power(2), 3);
}

TEST(TestMonom, test_monom_evaluate_at_point) {
    Monom a(1.2, 1, 2, 3);
    double tmp = a.evaluate_at_point(2, 3, 4);
    ASSERT_DOUBLE_EQ(tmp, 1382.4);  
}

TEST(TestMonom, test_monom_friend_function_mult_monom_on_value) {
    Monom a(1.2, 1, 2, 3);
    int value = 12;
    Monom tmp = a.operator*(value);
    ASSERT_DOUBLE_EQ(tmp.get_coeff(), 14.4);
    ASSERT_EQ(tmp.get_power(0), 1);
    ASSERT_EQ(tmp.get_power(1), 2);
    ASSERT_EQ(tmp.get_power(2), 3);
}

TEST(TestMonom, test_monom_friend_function_div_monom_on_value) {
    Monom a(1.2, 1, 2, 3);
    double value = 8.9;
    Monom tmp = a.operator/(value);
    ASSERT_NEAR(tmp.get_coeff(), 0.13483146067, EPSILON);
    ASSERT_EQ(tmp.get_power(0), 1);
    ASSERT_EQ(tmp.get_power(1), 2);
    ASSERT_EQ(tmp.get_power(2), 3);
}

TEST(TestMonom, test_monom_friend_function_div_monom_on_value_with_throw) {
    Monom a(1.2, 1, 2, 3);
    double value = 0.0;
    ASSERT_THROW(a.operator/(value), std::logic_error);
}

TEST(TestMonom, test_output_operator_positive) {
    Monom m1(3.0, 2, 1, 0); 
    std::ostringstream oss;
    oss << m1;
    ASSERT_EQ("3x^2y", oss.str());
}

TEST(TestMonom, test_output_operator_negative_coeff) {
    Monom m1(-2.0, 1, 2, 0); 
    std::ostringstream oss;
    oss << m1;
    ASSERT_EQ("-2xy^2", oss.str());
}

TEST(TestMonom, tetst_input_operator_positive) {
    std::istringstream iss("3.0 2 1 0"); 
    Monom m;
    iss >> m;

    ASSERT_DOUBLE_EQ(3.0, m.get_coeff());
    ASSERT_EQ(2, m.get_power(0));
    ASSERT_EQ(1, m.get_power(1));
    ASSERT_EQ(0, m.get_power(2));
}

TEST(TestMonom, test_input_operator_negative_coeff) {
    std::istringstream iss("-2.5 1 3 0"); 
    Monom m;
    iss >> m;

    ASSERT_DOUBLE_EQ(-2.5, m.get_coeff());
    ASSERT_EQ(1, m.get_power(0));
    ASSERT_EQ(3, m.get_power(1));
    ASSERT_EQ(0, m.get_power(2));
}