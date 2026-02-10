#include <gtest/gtest.h>
#include "../lib_Polynom/polynom.h"
#include "../lib_Monom/monom.h"

#define EPSILON 0.000001

TEST(TestPolynom, test_polynom_default_constructor) {
    Polynom polynom;

    auto it = polynom.begin();  
    
    Monom first_monom = *it;
    ASSERT_DOUBLE_EQ(first_monom.get_coeff(), 0.0);
    for (int i = 0; i < VARS_COUNT; ++i) {
        ASSERT_EQ(first_monom.get_power(i), 0);
    }
}
TEST(TestPolynom, test_polynom_copy_constructor) {
    Polynom polynom;

    auto it = polynom.begin();

    Monom first_monom = *it;
    ASSERT_DOUBLE_EQ(first_monom.get_coeff(), 0.0);
    for (int i = 0; i < VARS_COUNT; ++i) {
        ASSERT_EQ(first_monom.get_power(i), 0);
    }
}
//TEST(TestPolynom, test_polynom_parsing) {
//
//}

TEST(TestPolynom, test_polynom_operator_add) {
    Polynom p1("x^2 + 2y");
    Polynom p2("3x^2 - y + 5");
    Polynom expected_result("4x^2 + y + 5"); 
    Polynom actual_result = p1 + p2;

    ASSERT_EQ(actual_result, expected_result); 
}
TEST(TestPolynom, test_polynom_operator_sub) {
    Polynom p1("x^2 + 2y^3 + 4z^2");
    Polynom p2("2x^2 + 3y^3 - z^2");
    Polynom expected_result("-x^2 - y^3 + 5z^2");
    Polynom actual_result = p1 - p2;

    ASSERT_EQ(actual_result, expected_result);

}
////TEST(TestPolynom, test_polynom_operator_mult) {
////
////    Polynom p1("x^2 + 2y^3");
////
////    Polynom p2("2x^2 + 3y^3 - z^2");
////
////    Polynom expected_result("2x^4 + 7x^2y^3 + 6y^6 - x^2z^2 - 2y^3z^2");
////
////    Polynom actual_result = p1 * p2;
////
////
////
////}
//TEST(TestPolynom, test_polynom_operator_div) {
//    Polynom p1("4x^3y^2 + 6x^2y^4");
//    Monom m("2xy^2");
//    Polynom expected_result("2x^2 + 3xy^2");
//    Polynom actual_result = p1 / m;
//
//    ASSERT_EQ(actual_result, expected_result);
//
//    Polynom p2("x + y");
//    Polynom p3("x + 1");
//    ASSERT_THROW(p2 / p3, std::invalid_argument);
//
//    Polynom p4("x");
//    Monom zero_monom(0.0);
//    Polynom p5(zero_monom);
//    ASSERT_THROW(p4 / p5, std::invalid_argument);
//}