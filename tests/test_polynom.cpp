#include <gtest/gtest.h>
#include "../lib_Polynom/polynom.h"
#include "../lib_Monom/monom.h"

#define EPSILON 0.000001

TEST(TestPolynom, test_polynom_default_constructor) {
    Polynom polynom;
    ASSERT_EQ(polynom.begin(), polynom.end());
    ASSERT_EQ(polynom.get_size(), 0);
}

TEST(TestPolynom, test_polynom_default_constructor_with_data) {
    Polynom polynom;

    Monom monom1(2.5, 2, 3, 4);
    polynom += monom1;

    ASSERT_NE(polynom.begin(), polynom.end());

    auto it = polynom.begin();
    ASSERT_DOUBLE_EQ((*it).get_coeff(), 2.5);
    ASSERT_EQ((*it).get_power(0), 2);
    ASSERT_EQ((*it).get_power(1), 3);
    ASSERT_EQ((*it).get_power(2), 4);

    Monom monom2(1.5, 1, 1, 1);
    polynom += monom2;
    ASSERT_EQ(polynom.get_size(), 2);
}

TEST(TestPolynom, test_polynom_transformation_constructor) {
    Monom m1(3.5, 2, 1, 0);  

    Polynom p1(m1);
    ASSERT_EQ(p1.get_size(), 1);
    auto it = p1.begin();
    ASSERT_NE(it, p1.end());
    ASSERT_DOUBLE_EQ((*it).get_coeff(), 3.5);
    ASSERT_EQ((*it).get_power(0), 2);  
    ASSERT_EQ((*it).get_power(1), 1);  
    ASSERT_EQ((*it).get_power(2), 0);  
    ++it;
    ASSERT_EQ(it, p1.end());
}

TEST(TestPolynom, test_polynom_initialization_constructor) {
    List<Monom> my_list; 
    my_list.push_back(Monom(3.0, 2, 0, 0)); 
    my_list.push_back(Monom(1.0, 0, 1, 0)); 

    Polynom p(my_list);

    ASSERT_EQ(p.get_size(), 2);
    auto it = p.begin();
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 3.0);
    EXPECT_EQ((*it).get_power(0), 2);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 1.0);
    EXPECT_EQ((*it).get_power(1), 1);
}
TEST(TestPolynom, test_constructor_from_list_deep_copy) {
    List<Monom> my_list;
    my_list.push_back(Monom(3.0, 2, 0, 0));
    my_list.push_back(Monom(1.0, 0, 1, 0));
    Polynom p1(my_list);

    Polynom p2(my_list);

    EXPECT_EQ(p1, p2);
    my_list.clear();

    ASSERT_EQ(p1.get_size(), 2);
    EXPECT_EQ(p1, p2);
}

TEST(TestPolynom, test_polynom_operator_add_zero) {
    Polynom polynom1;
    Polynom polynom2;

    Polynom result = polynom1 + polynom2;
    ASSERT_EQ(result.get_size(), 0);
}
TEST(TestPolynom, test_polynom_operator_add_str_zero) {
    Polynom p1("x + y");
    Polynom p2("-x - y");
    Polynom res = p1 + p2;

    EXPECT_EQ(res.get_size(), 0);
}

TEST(TestPolynom, test_polynom_operator_add_list_monom) {
    List<Monom> list1, list2;
    list1.push_back(Monom(2.0, 1, 0, 0)); 
    list1.push_back(Monom(3.0, 0, 1, 0)); 

    list2.push_back(Monom(1.0, 1, 0, 0)); 
    list2.push_back(Monom(4.0, 0, 0, 1)); 
    Polynom poly1(list1);
    Polynom poly2(list2);

    Polynom res = poly1 + poly2;

    ASSERT_EQ(res.get_size(), 3);

    auto it = res.begin();

    EXPECT_DOUBLE_EQ((*it).get_coeff(), 3.0);
    EXPECT_EQ((*it).get_power(0), 1);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 3.0);
    EXPECT_EQ((*it).get_power(1), 1);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 4.0);
    EXPECT_EQ((*it).get_power(2), 1);
}
TEST(TestPolynom, test_polynom_operator_add_str) {

    Polynom p1("2x^2 + 5y - 3z");
    Polynom p2("x^2 - 5y + 10");
    Polynom res = p1 + p2;

    ASSERT_EQ(res.get_size(), 3);
    auto it = res.begin();
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 3.0);
    EXPECT_EQ((*it).get_power(0), 2);
    ++it; 
    EXPECT_DOUBLE_EQ((*it).get_coeff(), -3.0);
    EXPECT_EQ((*it).get_power(2), 1);
    ++it; 
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 10.0);
    EXPECT_EQ((*it).get_power(0), 0);
    EXPECT_EQ((*it).get_power(1), 0);
    EXPECT_EQ((*it).get_power(2), 0);
}

TEST(TestPolynom, test_polynom_operator_add) {
    Polynom p1("x^2 + 2y");
    Polynom p2("3x^2 - y + 5");
    Polynom expected_result("4x^2 + y + 5"); 
    Polynom actual_result = p1 + p2;

    ASSERT_EQ(actual_result, expected_result); 
}

TEST(TestPolynom, test_polynom_operator_sub_str_zero) {
    Polynom p1("x + y + z");
    Polynom p2("x + y + z");
    Polynom res = p1 - p2;

    EXPECT_EQ(res.get_size(), 0);
}

TEST(TestPolynom, test_polynom_operator_sub_negative_result) {
    Polynom p1("x + 2y");
    Polynom p2("2x + 3y");
    Polynom res = p1 - p2;

    ASSERT_EQ(res.get_size(), 2);

    auto it = res.begin();
    EXPECT_DOUBLE_EQ((*it).get_coeff(), -1.0);  
    EXPECT_EQ((*it).get_power(0), 1);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), -1.0);  
    EXPECT_EQ((*it).get_power(1), 1);
}

TEST(TestPolynom, test_polynom_operator_sub_list_monom) {
    List<Monom> list1, list2;
    list1.push_back(Monom(5.0, 2, 0, 0));   
    list1.push_back(Monom(3.0, 0, 1, 0));   

    list2.push_back(Monom(2.0, 2, 0, 0));   
    list2.push_back(Monom(1.0, 0, 1, 0));   
    list2.push_back(Monom(4.0, 0, 0, 1));   

    Polynom poly1(list1);
    Polynom poly2(list2);

    Polynom res = poly1 - poly2;

    ASSERT_EQ(res.get_size(), 3);

    auto it = res.begin();
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 3.0);   
    EXPECT_EQ((*it).get_power(0), 2);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 2.0);   
    EXPECT_EQ((*it).get_power(1), 1);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), -4.0);  
    EXPECT_EQ((*it).get_power(2), 1);
}

TEST(TestPolynom, test_polynom_operator_sub_str) {
    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("x^2 - y + 3z + 2");
    Polynom res = p1 - p2;

    ASSERT_EQ(res.get_size(), 4);

    auto it = res.begin();
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 2.0);   
    EXPECT_EQ((*it).get_power(0), 2);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 3.0);   
    EXPECT_EQ((*it).get_power(1), 1);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), -8.0);  
    EXPECT_EQ((*it).get_power(2), 1);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 5.0);   
    EXPECT_EQ((*it).get_power(0), 0);
    EXPECT_EQ((*it).get_power(1), 0);
    EXPECT_EQ((*it).get_power(2), 0);
}

TEST(TestPolynom, test_polynom_operator_sub_with_elimination) {
    Polynom p1("2x^2 + 3xy + 4y^2");
    Polynom p2("x^2 + 3xy + 2y^2");
    Polynom res = p1 - p2;

    ASSERT_EQ(res.get_size(), 2);

    auto it = res.begin();
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 1.0);  
    EXPECT_EQ((*it).get_power(0), 2);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 2.0);  
    EXPECT_EQ((*it).get_power(1), 2);
}
TEST(TestPolynom, test_polynom_operator_mult_by_zero) {
    Polynom p1("x + y + z");
    Polynom p2("0");
    Polynom res = p1 * p2;

    EXPECT_EQ(res.get_size(), 0);
}
TEST(TestPolynom, test_polynom_operator_mult_by_one) {
    Polynom p1("2x + 3y - 4z");
    Polynom p2("1");
    Polynom res = p1 * p2;

    ASSERT_EQ(res.get_size(), 3);

    auto it = res.begin();
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 2.0);   
    EXPECT_EQ((*it).get_power(0), 1);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 3.0);   
    EXPECT_EQ((*it).get_power(1), 1);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), -4.0);  
    EXPECT_EQ((*it).get_power(2), 1);
}

TEST(TestPolynom, test_polynom_operator_mult_simple) {
    Polynom p1("2x + 1");
    Polynom p2("x - 1");
    Polynom res = p1 * p2;

    ASSERT_EQ(res.get_size(), 3);

    auto it = res.begin();
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 2.0);   
    EXPECT_EQ((*it).get_power(0), 2);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), -1.0);  
    EXPECT_EQ((*it).get_power(0), 1);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), -1.0); 
    EXPECT_EQ((*it).get_power(0), 0);
}

TEST(TestPolynom, test_polynom_operator_mult_two_vars) {
    Polynom p1("x + y");
    Polynom p2("x - y");
    Polynom res = p1 * p2;

    ASSERT_EQ(res.get_size(), 2);

    auto it = res.begin();
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 1.0);  
    EXPECT_EQ((*it).get_power(0), 2);
    EXPECT_EQ((*it).get_power(1), 0);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), -1.0);  
    EXPECT_EQ((*it).get_power(0), 0);
    EXPECT_EQ((*it).get_power(1), 2);
}

TEST(TestPolynom, test_polynom_operator_mult_complex) {
    Polynom p1("2x + 3y");
    Polynom p2("x - 2y + z");
    Polynom res = p1 * p2;

    ASSERT_EQ(res.get_size(), 5);

    auto it = res.begin();

    EXPECT_DOUBLE_EQ((*it).get_coeff(), 2.0);
    EXPECT_EQ((*it).get_power(0), 2);
    EXPECT_EQ((*it).get_power(1), 0);
    EXPECT_EQ((*it).get_power(2), 0);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), -1.0);
    EXPECT_EQ((*it).get_power(0), 1);
    EXPECT_EQ((*it).get_power(1), 1);
    EXPECT_EQ((*it).get_power(2), 0);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 2.0);
    EXPECT_EQ((*it).get_power(0), 1);
    EXPECT_EQ((*it).get_power(1), 0);
    EXPECT_EQ((*it).get_power(2), 1);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), -6.0);
    EXPECT_EQ((*it).get_power(0), 0);
    EXPECT_EQ((*it).get_power(1), 2);
    EXPECT_EQ((*it).get_power(2), 0);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 3.0);
    EXPECT_EQ((*it).get_power(0), 0);
    EXPECT_EQ((*it).get_power(1), 1);
    EXPECT_EQ((*it).get_power(2), 1);
}

TEST(TestPolynom, test_polynom_operator_mult_with_constant) {
    Polynom p1("3x^2 - 2xy + y^2");
    
    Polynom res = p1 * 2;

    ASSERT_EQ(res.get_size(), 3);

    auto it = res.begin();
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 6.0);   
    EXPECT_EQ((*it).get_power(0), 2);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), -4.0);  
    EXPECT_EQ((*it).get_power(0), 1);
    EXPECT_EQ((*it).get_power(1), 1);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 2.0);   
    EXPECT_EQ((*it).get_power(1), 2);
}
TEST(TestPolynom, test_polynom_operator_div_scalar_int) {
    Polynom p1("4x^2 + 6x - 8");
    Polynom res = p1 / 2;

    ASSERT_EQ(res.get_size(), 3);

    auto it = res.begin();
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 2.0);  
    EXPECT_EQ((*it).get_power(0), 2);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 3.0);  
    EXPECT_EQ((*it).get_power(0), 1);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), -4.0); 
    EXPECT_EQ((*it).get_power(0), 0);
}

TEST(TestPolynom, test_polynom_operator_div_scalar_by_zero) {
    Polynom p1("5x^2 + 3x - 7");

    EXPECT_THROW(p1 / 0, std::invalid_argument);
    EXPECT_THROW(p1 / 0.0, std::invalid_argument);
}
TEST(TestPolynom, test_polynom_operator_div_scalar_fractional_result) {
    Polynom p1("x^2 + x + 1");
    Polynom res = p1 / 3;

    ASSERT_EQ(res.get_size(), 3);

    auto it = res.begin();
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 1.0 / 3.0);  
    EXPECT_EQ((*it).get_power(0), 2);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 1.0 / 3.0);  
    EXPECT_EQ((*it).get_power(0), 1);

    ++it;
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 1.0 / 3.0);  
    EXPECT_EQ((*it).get_power(0), 0);
}

TEST(TestPolynom, test_polynom_operator_div_str) {
    Polynom p1("5x");
    Polynom p2("5"); 
    Polynom expected_result("x");
    Polynom actual_result = p1 / p2;

    ASSERT_EQ(actual_result, expected_result);
}

TEST(TestPolynom, test_polynom_operator_div_on_zero) {
    Polynom p1("5x + 3");
    Polynom p2("0"); 

    EXPECT_THROW(p1 / p2, std::invalid_argument);
}
TEST(TestPolynom, test_polynom_operator_div_hard_polynom) {
    Polynom p1("-3x^5 + 6x^4 - 9x^3 + 12x^2 - 15x + 18");
    Polynom p2("x^2 - 2x + 3");
    Polynom expected_result("-3x^3 + 12");
    Polynom actual_result = p1 / p2;

    ASSERT_EQ(actual_result, expected_result);
}


TEST(TestPolynom, test_polynom_operator_inplace_add) {
    Polynom p("x^2 + y");
    p += Monom(2.0, 2, 0, 0);

    ASSERT_EQ(p.get_size(), 2);
    auto it = p.begin();
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 3.0);
    EXPECT_EQ((*it).get_power(0), 2);

    p += Monom(-3.0, 2, 0, 0);
    ASSERT_EQ(p.get_size(), 1);
    EXPECT_EQ((*p.begin()).get_variables(), "y");
}

TEST(TestPolynom, test_polynom_operator_inplace_sub) {
    Polynom p("5x - 3y");
    p -= Monom(2.0, 1, 0, 0); 

    ASSERT_EQ(p.get_size(), 2);
    EXPECT_DOUBLE_EQ((*p.begin()).get_coeff(), 3.0);

    p -= Monom(-3.0, 0, 1, 0); 
    ASSERT_EQ(p.get_size(), 1);
}

TEST(TestPolynom, test_polynom_operator_inplace_mult_scalar) {
    Polynom p("2x^2 + 4y - 6");
    p *= 0.5; 

    ASSERT_EQ(p.get_size(), 3);
    auto it = p.begin();
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 1.0);
    EXPECT_DOUBLE_EQ((*++it).get_coeff(), 2.0);
    EXPECT_DOUBLE_EQ((*++it).get_coeff(), -3.0);

    p *= 0.0; 
    ASSERT_EQ(p.get_size(), 0);
}

TEST(TestMonom, test_polynom_operator_inplace_mult_monom) {
    Polynom p("x + y");
    p *= Monom(2.0, 1, 0, 0); 

    ASSERT_EQ(p.get_size(), 2);
    EXPECT_EQ((*p.begin()).get_variables(), "x^2");
    EXPECT_DOUBLE_EQ((*p.begin()).get_coeff(), 2.0);
}

TEST(TestPolynom, test_polynom_operator_inplace_div_scalar) {
    Polynom p("10x^3 - 5");
    p /= 5.0; 

    EXPECT_DOUBLE_EQ((*p.begin()).get_coeff(), 2.0);
    ASSERT_THROW(p /= 0.0, std::invalid_argument);
}

TEST(TestPolynom, test_polynom_operator_inplace_div_monom) {
    Polynom p("4x^2y + 2xy");
    p /= Monom(2.0, 1, 1, 0); 

    ASSERT_EQ(p.get_size(), 2);
    auto it = p.begin();
    EXPECT_EQ((*it).get_variables(), "x");
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 2.0);
    EXPECT_EQ((*++it).get_variables(), ""); 
    EXPECT_DOUBLE_EQ((*it).get_coeff(), 1.0);
}

