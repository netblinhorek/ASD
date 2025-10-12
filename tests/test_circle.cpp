// Copyright 2024 Marina Usova

#include <gtest/gtest.h>
#include "../lib_circle/circle.h"
#include "../lib_circle/circle.cpp"

#define EPSILON 0.000001
 


TEST(TestCircle, test_circles_coincide) {
    Circle c1(0, 0, 5), c2(0, 0, 5);
    
    // Act & Assert
    ASSERT_EQ(std::string("Coincide"), get_circles_relation(c1, c2));
}
TEST(TestCircle, test_circles_externally_touch) {
    Circle c1(0, 0, 5), c2(10, 0, 5);

    // Act & Assert
    ASSERT_EQ(std::string("External touch"), get_circles_relation(c1, c2));
}
TEST(TestCircle, test_circles_internally_touch) {
    Circle c1(0, 0, 5), c2(3, 0, 2);

    // Act & Assert
    ASSERT_EQ(std::string("Inner touch"), get_circles_relation(c1, c2));
}
TEST(TestCircle, test_circles_intersect) {
    Circle c1(0, 0, 5), c2(6, 0, 5);

    // Act & Assert
    ASSERT_EQ(std::string("Intersect"), get_circles_relation(c1, c2));
}
TEST(TestCircle, test_circles_one_inside_another) {
    Circle c1(0, 0, 5), c2(1, 0, 2);

    // Act & Assert
    ASSERT_EQ(std::string("One inside the other"), get_circles_relation(c1, c2));
}
TEST(TestCircle, test_circles_separate) {
    Circle c1(0, 0, 5), c2(20, 0, 5);

    // Act & Assert
    ASSERT_EQ(std::string("Not intersected"), get_circles_relation(c1, c2));
}


// на выброс исключений
TEST(TestCircle, test_zero_radius_throws_in_constructor) {
    ASSERT_THROW(Circle(1, 0, 0), std::invalid_argument);
}
TEST(TestCircle, test_circles_externally_touch_exceptions) {
    Circle c1(0, 0, 3), c2(10, 0, 5);

    // Act & Assert
    ASSERT_NO_THROW(std::string("Wrong expectation"), get_circles_relation(c1, c2));
}
TEST(TestCircle, test_circles_internally_touch_exceptions) {
    Circle c1(3, 0, 5), c2(3, 0, 2);

    // Act & Assert
    ASSERT_NO_THROW(std::string("Inner touch"), get_circles_relation(c1, c2));
}
TEST(TestCircle, test_circles_intersect_exceptions) {
    Circle c1(0, 13, 5), c2(6, 0, 5);

    // Act & Assert
    ASSERT_NO_THROW(std::string("Intersect"), get_circles_relation(c1, c2));
}
TEST(TestCircle, test_circles_one_inside_another_exceptions) {
    Circle c1(1, 0, 2), c2(1, 0, 2);

    // Act & Assert
    ASSERT_NO_THROW(std::string("One inside the other"), get_circles_relation(c1, c2));
}
TEST(TestCircle, test_circles_separate_exceptions) {
    Circle c1(20, 0, 5), c2(20, 0, 5);

    // Act & Assert
    ASSERT_NO_THROW(std::string("Not intersected"), get_circles_relation(c1, c2));
}

TEST(TestCircle, test_very_large_radius) {
    Circle c1(0, 0, 1000), c2(1, 1, 1000);
    // Act & Assert
    ASSERT_EQ(std::string("Intersect"), get_circles_relation(c1, c2));
}
TEST(TestCircle, test_negative_coordinates) {
    Circle c1(-5, -5, 3), c2(-2, -2, 2);
    // Act & Assert
    ASSERT_EQ(std::string("Intersect"), get_circles_relation(c1, c2));
}

TEST(TestCircle, test_negative_coordinates_touch) {
    Circle c1(-10, 0, 5), c2(0, 0, 5);
    // Act & Assert
    ASSERT_EQ(std::string("External touch"), get_circles_relation(c1, c2));
}
TEST(TestCircle, test_negative_radius_exception) {
    // Act & Assert
    ASSERT_THROW(Circle(-5, -5, -3), std::invalid_argument);
}

TEST(TestCircle, test_default_constructor) {
    Circle c;

    // Act & Assert

    ASSERT_EQ(c.get_x(), 0);
    ASSERT_EQ(c.get_y(), 0);
    ASSERT_EQ(c.get_radius(), 1);
}
TEST(TestCircle, test_circle_methods) {
    Circle c(6, 0, 5);
    
    // Act & Assert

    ASSERT_EQ(c.get_x(), 6);
    ASSERT_EQ(c.get_y(), 0);
    ASSERT_EQ(c.get_radius(), 5);
}
TEST(TestCircle, test_copy_constructor) {
    Circle original(1, 2, 3);
    Circle copy(original);
    
    // Act & Assert

    ASSERT_EQ(copy.get_x(), 1);
    ASSERT_EQ(copy.get_y(), 2);
    ASSERT_EQ(copy.get_radius(), 3);
}

TEST(TestCircle, test_assignment_operator) {
    Circle c1(5, 6, 7);
    Circle c2;
    c2 = c1;
    
    // Act & Assert

    ASSERT_EQ(c2.get_x(), 5);
    ASSERT_EQ(c2.get_y(), 6);
    ASSERT_EQ(c2.get_radius(), 7);
}
TEST(TestCircle, test_setters) {
    Circle c;
    c.set_x(10);
    c.set_y(20);
    c.set_radius(15);

    // Act & Assert

    ASSERT_EQ(c.get_x(), 10);
    ASSERT_EQ(c.get_y(), 20);
    ASSERT_EQ(c.get_radius(), 15);
}
TEST(TestCircle, test_set_negative_radius_exception) {
    Circle c;
    ASSERT_THROW(c.set_radius(-5), std::invalid_argument);
}

TEST(TestCircle, test_floating_point_precision) {
    Circle c1(0.1f + 0.2f, 0.0f, 1.0f);
    Circle c2(0.3f, 0.0f, 1.0f);

    std::string relation = get_circles_relation(c1, c2);

    ASSERT_TRUE(relation == "Coincide");
}

