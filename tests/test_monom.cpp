#include <gtest/gtest.h>
#include "../lib_Monom/monom.h"

#define EPSILON 0.000001

TEST(TestMonom, test_monom_default_constructor) {
    
    Monom monom;

    ASSERT_DOUBLE_EQ(monom.get_coeff(), 0.0); 
    for (int i = 0; i < VARS_COUNT; ++i) {
        ASSERT_EQ(monom.get_power(i), 0);  
    }
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
    ASSERT_NE(monom_copy.get_power(0), 99);
}

TEST(TestMonom, test_monom_operator_add) {

    Monom a(3.0), b(2.0);
    a.set_power(0, 2); a.set_power(1, 1);  
    b.set_power(0, 2); b.set_power(1, 1);  

    Monom c = a + b;  
    ASSERT_DOUBLE_EQ(c.get_coeff(), 5.0);
    ASSERT_EQ(c.get_power(0), 2);
    ASSERT_EQ(c.get_power(1), 1);

    Monom d(1.0);
    d.set_power(0, 3);
    ASSERT_THROW(a + d, std::invalid_argument);

}


TEST(TestMonom, test_monom_operator_add_operator) {

    Monom a(3.0), b(2.0);
    a.set_power(0, 2); a.set_power(1, 1);
    b.set_power(0, 2); b.set_power(1, 1);

    a += b;
    
    ASSERT_DOUBLE_EQ(a.get_coeff(), 5.0);
    ASSERT_EQ(a.get_power(0), 2);
    ASSERT_EQ(a.get_power(1), 1);

    Monom d(1.0);
    d.set_power(0, 3);
    ASSERT_THROW(a += d, std::invalid_argument);

}
TEST(TestMonom, test_monom_operator_sub) {

    Monom a(5.0), b(2.0);
    a.set_power(0, 1); a.set_power(1, 2);
    b.set_power(0, 1); b.set_power(1, 2);

    Monom c = a - b;
    ASSERT_DOUBLE_EQ(c.get_coeff(), 3.0);
    ASSERT_EQ(c.get_power(0), 1);
    ASSERT_EQ(c.get_power(1), 2);

    Monom d(1.0);
    d.set_power(0, 3);
    ASSERT_THROW(a - d, std::invalid_argument);
}
TEST(TestMonom, test_monom_operator_sub_operator) {

    Monom a(5.0), b(2.0);
    a.set_power(0, 1); a.set_power(1, 2);
    b.set_power(0, 1); b.set_power(1, 2);

    a -= b;
    ASSERT_DOUBLE_EQ(a.get_coeff(), 3.0);
    ASSERT_EQ(a.get_power(0), 1);
    ASSERT_EQ(a.get_power(1), 2);

    Monom d(1.0);
    d.set_power(0, 3);
    ASSERT_THROW(a -= d, std::invalid_argument);
}
TEST(TestMonom, test_monom_operator_mult) {

    Monom a(2.0);
    a.set_power(0, 1); a.set_power(1, 2);

    Monom b(3.0);
    b.set_power(0, 2); b.set_power(1, 3);

    Monom c = a * b;
    ASSERT_DOUBLE_EQ(c.get_coeff(), 6.0);
    ASSERT_EQ(c.get_power(0), 3);
    ASSERT_EQ(c.get_power(1), 5);
    ASSERT_EQ(c.get_power(2), 0);
}
TEST(TestMonom, test_monom_operator_mult_operator) {

    Monom a(2.0);
    a.set_power(0, 1); a.set_power(1, 2);

    Monom b(3.0);
    b.set_power(0, 2); b.set_power(1, 3);

    a *= b;
    ASSERT_DOUBLE_EQ(a.get_coeff(), 6.0);
    ASSERT_EQ(a.get_power(0), 3);
    ASSERT_EQ(a.get_power(1), 5);
    ASSERT_EQ(a.get_power(2), 0);
}


TEST(TestMonom, test_monom_operator_div) {
    Monom a(4.0, 3, 2, 1);
    Monom b(2.0, 1, 1, 1);
    Monom c = a / b;
    ASSERT_DOUBLE_EQ(c.get_coeff(), 2.0);
    ASSERT_EQ(c.get_power(0), 2);
    ASSERT_EQ(c.get_power(1), 1);
    ASSERT_EQ(c.get_power(2), 0);

    Monom d(1.0, 0, 0, 1); 
    Monom e(1.0, 1, 0, 0); 
    ASSERT_THROW(d / e, std::invalid_argument);

    Monom zero_monom(0.0);
    ASSERT_THROW(a / zero_monom, std::invalid_argument);
}

TEST(TestMonom, test_monom_operator_div_operator) {
    Monom a(4.0, 3, 2, 1);
    Monom b(2.0, 1, 1, 1);
    a /= b;
    ASSERT_DOUBLE_EQ(a.get_coeff(), 2.0);
    ASSERT_EQ(a.get_power(0), 2);
    ASSERT_EQ(a.get_power(1), 1);
    ASSERT_EQ(a.get_power(2), 0);

    Monom d(1.0, 0, 0, 1); 
    Monom e(1.0, 1, 0, 0); 
    ASSERT_THROW(d /= e, std::invalid_argument); 

    Monom zero_monom(0.0);
    Monom c(5.0);
    ASSERT_THROW(c /= zero_monom, std::invalid_argument);
}

TEST(TestMonom, test_monom_operator_equal_not_equal) {
	Monom a(2.0);
	a.set_power(0, 1);
	Monom b(2.0);
	b.set_power(0, 1);
	Monom c(3.0);
	c.set_power(0, 1);
	Monom d(2.0);
	d.set_power(0, 2);

	ASSERT_TRUE(a == b);
	ASSERT_FALSE(a != b);
	ASSERT_TRUE(a != c);
	ASSERT_FALSE(a == c);
	ASSERT_TRUE(a != d);
}

TEST(TestMonom, test_monom_operator_greater_less) {
	Monom a(2.0);
	a.set_power(0, 2);
	a.set_power(1, 1);

	Monom b(2.0);
	b.set_power(0, 2);
	b.set_power(1, 1);

	Monom c(3.0);
	c.set_power(0, 2);
	c.set_power(1, 1);

	Monom d(2.0);
	d.set_power(0, 3);
	d.set_power(1, 0);

	ASSERT_FALSE(a > b);
	ASSERT_FALSE(a < b);

	ASSERT_TRUE(c > a); 
	ASSERT_FALSE(a > c);

	ASSERT_TRUE(d > a); 
	ASSERT_FALSE(a > d);

	Monom e(2.0);
	e.set_power(0, 2);
	e.set_power(1, 2);

	ASSERT_TRUE(e > a); 
	ASSERT_FALSE(a > e);
}

TEST(TestMonom, test_monom_assignment_operator) {
	Monom a(5.0);
	a.set_power(0, 1);
	a.set_power(1, 2);

	Monom b;
	b = a; 

	ASSERT_DOUBLE_EQ(b.get_coeff(), 5.0);
	ASSERT_EQ(b.get_power(0), 1);
	ASSERT_EQ(b.get_power(1), 2);
	ASSERT_EQ(b.get_power(2), 0);

	a.set_power(0, 99);
	ASSERT_NE(b.get_power(0), 99);

	Monom c(10.0);
	c.set_power(0, 5);
	c = c;
	ASSERT_DOUBLE_EQ(c.get_coeff(), 10.0);
	ASSERT_EQ(c.get_power(0), 5);
}