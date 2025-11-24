// Copyright 2024 Marina Usova

#include <gtest/gtest.h>
#include "../lib_point3d/point3d.h"
#include <cmath>
#include <cfloat>

#define EPSILON 0.000001f

TEST(TestPoint3D, test_default_constructor) {
    // Arrange & Act
    Point3D p;

    // Assert
    ASSERT_NEAR(p.get_x(), 0.0f, EPSILON);
    ASSERT_NEAR(p.get_y(), 0.0f, EPSILON);
    ASSERT_NEAR(p.get_z(), 0.0f, EPSILON);
}

TEST(TestPoint3D, test_parameterized_constructor) {
    // Arrange & Act
    Point3D p(3.0f, 4.0f, 5.0f);

    // Assert
    ASSERT_NEAR(p.get_x(), 3.0f, EPSILON);
    ASSERT_NEAR(p.get_y(), 4.0f, EPSILON);
    ASSERT_NEAR(p.get_z(), 5.0f, EPSILON);
}

TEST(TestPoint3D, test_negative_coordinates_no_exception) {
    // Arrange, Act & Assert
    ASSERT_NO_THROW(Point3D(-2.0f, -2.0f, -9.0f));
}

TEST(TestPoint3D, test_setters) {
    // Arrange
    Point3D p;

    // Act
    p.set_x(10.5f);
    p.set_y(20.7f);
    p.set_z(9.7f);

    // Assert
    ASSERT_NEAR(p.get_x(), 10.5f, EPSILON);
    ASSERT_NEAR(p.get_y(), 20.7f, EPSILON);
    ASSERT_NEAR(p.get_z(), 9.7f, EPSILON);
}

TEST(TestPoint3D, test_distance_to_2d) {
    // Arrange 
    Point3D p1(0.0f, 0.0f, 0.0f);
    Point3D p2(3.0f, 4.0f, 0.0f);

    // Act
    float distance = p1.distance_to(p2);

    // Assert
    ASSERT_NEAR(distance, 5.0f, EPSILON);
}

TEST(TestPoint3D, test_distance_to_3d) {
    // Arrange 
    Point3D p1(1.0f, 2.0f, 3.0f);
    Point3D p2(4.0f, 6.0f, 8.0f);

    // Act
    float distance = p1.distance_to(p2);

    ASSERT_NEAR(distance, 7.071067f, EPSILON);
}

TEST(TestPoint3D, test_distance_to_same_point) {
    // Arrange
    Point3D p1(2.0f, 3.0f, 4.0f);
    Point3D p2(2.0f, 3.0f, 4.0f);

    // Act
    float distance = p1.distance_to(p2);

    // Assert
    ASSERT_NEAR(distance, 0.0f, EPSILON);
}

TEST(TestPoint3D, test_equality_operator) {
    // Arrange
    Point3D p1(1.0f, 2.0f, 3.0f);
    Point3D p2(1.0f, 2.0f, 3.0f);
    Point3D p3(1.1f, 2.0f, 3.0f);
    
    // Act & Assert
    ASSERT_TRUE(p1 == p2);
    ASSERT_FALSE(p1 == p3);  
    
}

TEST(TestPoint3D, test_copy_constructor) {
    // Arrange
    Point3D original(1.0f, 2.0f, 3.0f);

    // Act
    Point3D copy(original);

    // Assert
    ASSERT_NEAR(copy.get_x(), 1.0f, EPSILON);
    ASSERT_NEAR(copy.get_y(), 2.0f, EPSILON);
    ASSERT_NEAR(copy.get_z(), 3.0f, EPSILON);
    ASSERT_TRUE(original == copy);
}

TEST(TestPoint3D, test_assignment_operator) {
    // Arrange
    Point3D p1(5.0f, 6.0f, 7.0f);
    Point3D p2;

    // Act
    p2 = p1;

    // Assert
    ASSERT_NEAR(p2.get_x(), 5.0f, EPSILON);
    ASSERT_NEAR(p2.get_y(), 6.0f, EPSILON);
    ASSERT_NEAR(p2.get_z(), 7.0f, EPSILON);
    ASSERT_TRUE(p1 == p2);
}

TEST(TestPoint3D, test_distance_positive_and_negative) {
    Point3D p1(1.0f, 2.0f, 3.0f);
    Point3D p2(-1.0f, -2.0f, -3.0f);

    ASSERT_NEAR(p1.distance_to(p2), 7.483314f, EPSILON);
}