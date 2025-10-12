// Copyright 2024 Marina Usova

#include <gtest/gtest.h>
#include "../lib_sphere/sphere.h"
#include "../lib_sphere/sphere.cpp"

#define EPSILON 0.000001

TEST(TestSphere, test_sphere_coincide) {
    Sphere s1(0, 0, 0, 5), s2(0, 0, 0, 5);

    // Act & Assert
    ASSERT_EQ(std::string("Coincide"), get_spheres_relation(s1, s2));
}
TEST(TestSphere, test_sphere_externally_touch) {
    Sphere s1(0, 0, 0, 5), s2(10, 0, 0, 5);

    // Act & Assert
    ASSERT_EQ(std::string("External touch"), get_spheres_relation(s1, s2));
}
TEST(TestSphere, test_sphere_internally_touch) {
    Sphere s1(0, 0, 0, 5), s2(3, 0, 0, 2);

    // Act & Assert
    ASSERT_EQ(std::string("Inner touch"), get_spheres_relation(s1, s2));
}

TEST(TestSphere, test_sphere_intersect) {
    Sphere s1(0, 0, 0, 5), s2(6, 0, 0, 5);

    // Act & Assert
    ASSERT_EQ(std::string("Intersect"), get_spheres_relation(s1, s2));  
}
  
TEST(TestSphere, test_sphere_one_inside_another) {
    Sphere s1(0, 0, 0, 5), s2(1, 0, 0, 2);

    // Act & Assert
    ASSERT_EQ(std::string("One inside the other"), get_spheres_relation(s1, s2));
}

TEST(TestSphere, test_sphere_separate) {
    Sphere s1(0, 0, 0, 5), s2(20, 0, 0, 2);

    // Act & Assert
    ASSERT_EQ(std::string("Not intersected"), get_spheres_relation(s1, s2));
}


// на выброс исключений
TEST(TestSphere, test_sphere_coincide_exceptions) {
    Sphere s1(1, 0, 0, 5), s2(0, 0, 0, 5);

    // Act & Assert
    ASSERT_NO_THROW(std::string("Wrong expectation"), get_spheres_relation(s1, s2));
}
TEST(TestSphere, test_sphere_internally_touch_exceptions) {
    Sphere s1(0, 0, 0, 5), s2(0, 0, 0, 5);

    // Act & Assert
    ASSERT_NO_THROW(std::string("Inner touch"), get_spheres_relation(s1, s2));
}
TEST(TestSphere, test_sphere_intersect_exceptions) {
    Sphere s1(0, 0, 0, 5), s2(0, 0, 0, 5);

    // Act & Assert
    ASSERT_NO_THROW(std::string("Intersect"), get_spheres_relation(s1, s2));
}
TEST(TestSphere, test_sphere_one_inside_another_exceptions) {
    Sphere s1(0, 0, 0, 5), s2(0, 0, 0, 5);

    // Act & Assert
    ASSERT_NO_THROW(std::string("One inside the other"), get_spheres_relation(s1, s2));
}
TEST(TestSphere, test_sphere_separate_exceptions) {
    Sphere s1(0, 0, 0, 5), s2(0, 0, 0, 5);

    // Act & Assert
    ASSERT_NO_THROW(std::string("Not intersected"), get_spheres_relation(s1, s2));
}
TEST(TestSphere, test_zero_radius_sphere) {
    Sphere s1(0, 0, 0, 5), s2(0, 0, 0, 5);

    ASSERT_EQ(std::string("Coincide"), get_spheres_relation(s1, s2));
}

TEST(TestSphere, test_zero_radius_separate_sphere) {

    ASSERT_THROW(Sphere(1, 0, 0, 0), std::invalid_argument);
}

TEST(TestSphere, test_very_large_radius_sphere) {
    Sphere s1(0, 0, 0, 10000), s2(0, 0, 0, 100034);

    ASSERT_EQ(std::string("One inside the other"), get_spheres_relation(s1, s2));
}
TEST(TestSphere, test_negative_coordinates_sphere) {
    Sphere s1(-2, -4, -6, 5), s2(-3, -1, -5, 5);

    ASSERT_EQ(std::string("Intersect"), get_spheres_relation(s1, s2));
}

TEST(TestSphere, test_negative_coordinates_touch_sphere) {
    Sphere s1(-5, 0, 0, 5), s2(5, 0, 0, 5);

    ASSERT_EQ(std::string("External touch"), get_spheres_relation(s1, s2));
}
TEST(TestSphere, test_negative_radius_exception_sphere) {

    ASSERT_THROW(Sphere(-5, -5, -3, -4), std::invalid_argument);
}

TEST(TestSphere, test_floating_point_precision_internal_touch) {
    Sphere s1(0, 0, 0, 5), s2(2.999999f, 0, 0, 2);
    ASSERT_EQ(std::string("One inside the other"), get_spheres_relation(s1, s2));
}
TEST(TestSphere, test_default_constructor) {
    Sphere s;

    // Act & Assert

    ASSERT_EQ(s.get_x(), 0);
    ASSERT_EQ(s.get_y(), 0);
    ASSERT_EQ(s.get_z(), 0);
    ASSERT_EQ(s.get_radius(), 1);
}
TEST(TestSphere, test_sphere_methods) {
    Sphere s(6, 0, 5, 6);

    // Act & Assert

    ASSERT_EQ(s.get_x(), 6);
    ASSERT_EQ(s.get_y(), 0);
    ASSERT_EQ(s.get_z(), 5);
    ASSERT_EQ(s.get_radius(), 6);
}
TEST(TestSphere, test_copy_constructor) {
    Sphere original(1, 2, 3, 5);
    Sphere copy(original);

    // Act & Assert

    ASSERT_EQ(copy.get_x(), 1);
    ASSERT_EQ(copy.get_y(), 2);
    ASSERT_EQ(copy.get_z(), 3);
    ASSERT_EQ(copy.get_radius(), 5);
}

TEST(TestSphere, test_assignment_operator) {
    Sphere s1(5, 6, 7, 5);
    Sphere s2;
    s2 = s1;

    // Act & Assert

    ASSERT_EQ(s2.get_x(), 5);
    ASSERT_EQ(s2.get_y(), 6);
    ASSERT_EQ(s2.get_z(), 7);
    ASSERT_EQ(s2.get_radius(), 5);
}
TEST(TestSphere, test_setters) {
    Sphere s;
    s.set_x(10);
    s.set_y(20);
    s.set_z(56);
    s.set_radius(15);

    // Act & Assert

    ASSERT_EQ(s.get_x(), 10);
    ASSERT_EQ(s.get_y(), 20);
    ASSERT_EQ(s.get_z(), 56);
    ASSERT_EQ(s.get_radius(), 15);
}

TEST(TestSphere, test_set_negative_radius_exception) {
    Sphere s;

    // Act & Assert
    ASSERT_THROW(s.set_radius(-5), std::invalid_argument);
}

