// Copyright 2024 Marina Usova

#include <gtest/gtest.h>
#include "../lib_point/point.h"

#define EPSILON 0.000001

TEST(TestPoint, test_default_constructor) {
    // Arrange & Act
    Point p;

    // Assert
    ASSERT_NEAR(p.get_x(), 0.0f, EPSILON);
    ASSERT_NEAR(p.get_y(), 0.0f, EPSILON);
}

TEST(TestPoint, test_parameterized_constructor) {
    // Arrange & Act
    Point p(3.0f, 4.0f);

    // Assert
    ASSERT_NEAR(p.get_x(), 3.0f, EPSILON);
    ASSERT_NEAR(p.get_y(), 4.0f, EPSILON);
}

TEST(TestPoint, test_negative_coordinates_no_exception) {
    // Arrange, Act & Assert
    ASSERT_NO_THROW(Point(-2.0f, -2.0f));     
}

TEST(TestPoint, test_zero_radius_no_exception) {
    // Arrange, Act & Assert
    ASSERT_NO_THROW(Point(0.0f, 0.0f));
}

TEST(TestPoint, test_setters) {
    // Arrange
    Point p;

    // Act
    p.set_x(10.5f);
    p.set_y(20.7f);

    // Assert
    ASSERT_NEAR(p.get_x(), 10.5f, EPSILON);
    ASSERT_NEAR(p.get_y(), 20.7f, EPSILON);
}

TEST(TestPoint, test_distance_to) {
    // Arrange
    Point p1(0.0f, 0.0f);
    Point p2(3.0f, 4.0f);

    // Act
    float distance = p1.distance_to(p2);

    // Assert
    ASSERT_NEAR(distance, 5.0f, EPSILON);
}

TEST(TestPoint, test_distance_to_same_point) {
    // Arrange
    Point p1(2.0f, 3.0f);
    Point p2(2.0f, 3.0f);

    // Act
    float distance = p1.distance_to(p2);

    // Assert
    ASSERT_NEAR(distance, 0.0f, EPSILON);
}

TEST(TestPoint, test_equality_operator) {
    // Arrange
    Point p1(1.0f, 2.0f);
    Point p2(1.0f, 2.0f);
    Point p3(1.1f, 2.0f);

    // Act & Assert
    ASSERT_TRUE(p1 == p2);
    ASSERT_FALSE(p1 == p3);
}

TEST(TestPoint, test_copy_constructor) {
    // Arrange
    Point original(1.0f, 2.0f);

    // Act
    Point copy(original);

    // Assert
    ASSERT_NEAR(copy.get_x(), 1.0f, EPSILON);
    ASSERT_NEAR(copy.get_y(), 2.0f, EPSILON);
    ASSERT_TRUE(original == copy);
}

TEST(TestPoint, test_assignment_operator) {
    // Arrange
    Point p1(5.0f, 6.0f);
    Point p2;

    // Act
    p2 = p1;

    // Assert
    ASSERT_NEAR(p2.get_x(), 5.0f, EPSILON);
    ASSERT_NEAR(p2.get_y(), 6.0f, EPSILON);
    ASSERT_TRUE(p1 == p2);
}
TEST(TestPoint, test_inequality_operator) {
    Point p1(1.0f, 2.0f);
    Point p2(1.1f, 2.0f);

    ASSERT_TRUE(p1 != p2);
    ASSERT_FALSE(p1 != p1); 
}
TEST(TestPoint, test_distance_precision) {
    Point p1(0.1f, 0.2f);
    Point p2(0.4f, 0.6f);

    ASSERT_NEAR(p1.distance_to(p2), 0.5f, EPSILON);
}
TEST(TestPoint, test_equality_with_epsilon_the_first) {
    Point p1(1.0000001f, 2.0000001f);
    Point p2(1.0000002f, 2.0000002f);

    ASSERT_TRUE(p1 == p2);
}
TEST(TestPoint, test_equality_with_epsilon_the_second) {
    Point p1(1.0000001f, 2.0000001f);
    Point p2(1.1f, 2.0f);

    ASSERT_FALSE(p1 == p2);
}

TEST(TestPoint, test_self_assignment) {
    // Arrange
    Point p(1.0f, 2.0f);

    // Act
    p = p;

    // Assert
    ASSERT_NEAR(p.get_x(), 1.0f, EPSILON);
    ASSERT_NEAR(p.get_y(), 2.0f, EPSILON);
}