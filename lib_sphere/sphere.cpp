#include "sphere.h"
#include <stdexcept>
#include <cmath>
#include "../lib_point3d/point3d.h"


Sphere::Sphere(float x, float y, float z, float radius) : center(x, y, z) {
    if (radius <= 0) {
        throw std::invalid_argument("Radius cannot be zero or negative");
    }
    this->radius = radius;
}

Sphere::Sphere(const Point3D& center, float radius) : center(center) {
    if (radius <= 0) {
        throw std::invalid_argument("Radius cannot be zero or negative");
    }
    this->radius = radius;
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

float Sphere::distance_to(const Sphere& other) const {
    return center.distance_to(other.center);
}

bool Sphere::operator==(const Sphere& other) const {
    return center == other.center && radius == other.radius;
}
bool Sphere::operator!=(const Sphere& other) const {
    return !(*this == other);
}

template<typename SphereT>
std::string get_spheres_relation(const SphereT& s1, const SphereT& s2) {
    float d = s1.distance_to(s2);
    float r1 = s1.get_radius();
    float r2 = s2.get_radius();

    if (d == 0 && r1 == r2) return "Coincide";
    if (d == r1 + r2) return "External touch";
    if (d == std::abs(r1 - r2)) return "Inner touch";
    if (d < std::abs(r1 - r2)) return "One inside the other";
    if (d < r1 + r2) return "Intersect";
    return "Not intersected";
}