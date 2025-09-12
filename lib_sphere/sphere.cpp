#include "sphere.h"
#include <stdexcept>
#include <cmath>
#include "../lib_point3d/point3d.h"


template<typename SphereT>
std::string get_spheres_relation(const SphereT& s1, const SphereT& s2) {
    float dx = s1.get_x() - s2.get_x();
    float dy = s1.get_y() - s2.get_y();
    float dz = s1.get_z() - s2.get_z();
    float d = std::sqrt(dx * dx + dy * dy + dz * dz);
    float r1 = s1.get_radius();
    float r2 = s2.get_radius();
    if (d == 0 && r1 == r2)
    {
        return "Coincide";
    }

    if (d == r1 + r2) {
        return "External touch";
    }
    if (d == std::abs(r1 - r2) && d != 0) {
        return "Inner touch";
    }
    if (std::abs(r1 - r2) < d && d < r1 + r2) {
        return "Intersect";
    }
    if (d < std::abs(r1 - r2)) {
        return "One inside the other";
    }
    return "Not intersected";
}


Sphere::Sphere(float x, float y, float z, float radius)
    : center(x, y, z), radius(radius) {
    if (radius < 0) {
        throw std::invalid_argument("Radius cannot be negative");
    }
}

Sphere::Sphere(const Point3D& center, float radius)
    : center(center), radius(radius) {
    if (radius < 0) {
        throw std::invalid_argument("Radius cannot be negative");
    }
}

Point3D Sphere::get_center() const {
    return center;
}

float Sphere::get_x() const {
    return center.get_x();
}

float Sphere::get_y() const {
    return center.get_y();
}

float Sphere::get_z() const {
    return center.get_z();
}

float Sphere::get_radius() const {
    return radius;
}

void Sphere::set_center(const Point3D& new_center) {
    center = new_center;
}

void Sphere::set_x(float x) {
    center.set_x(x);
}

void Sphere::set_y(float y) {
    center.set_y(y);
}

void Sphere::set_z(float z) {
    center.set_z(z);
}

void Sphere::set_radius(float new_radius) {
    if (new_radius < 0) {
        throw std::invalid_argument("Radius cannot be negative");
    }
    radius = new_radius;
}

float Sphere::calculate_distance_from_origin() const {
    return std::sqrt(center.get_x() * center.get_x() +
        center.get_y() * center.get_y() +
        center.get_z() * center.get_z());
}

bool Sphere::operator==(const Sphere& other) const {
    const float EPSILON = 0.000001f;
    return (center == other.center) &&
        (std::abs(radius - other.radius) < EPSILON);
}

bool Sphere::operator!=(const Sphere& other) const {
    return !(*this == other);
}