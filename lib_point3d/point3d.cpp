#include "point3d.h"
#include <stdexcept>
#include <cmath>
#include <random>

Point3D::Point3D(const float _x, const float _y, const float _z) {
    x = _x;
    y = _y;
    z = _z;
}

float Point3D::get_x() const {
    return x;
}

float Point3D::get_y() const {
    return y;
}

float Point3D::get_z() const {
    return z;
}

void Point3D::set_x(float new_x) {
    x = new_x;
}

void Point3D::set_y(float new_y) {
    y = new_y;
}

void Point3D::set_z(float new_z) {
    z = new_z;
}

float Point3D::distance_to(const Point3D& other) const {
    float dx = x - other.x;
    float dy = y - other.y;
    float dz = z - other.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

bool Point3D::operator==(const Point3D& other) const {
    return x == other.x && y == other.y &&
        z == other.z;
}
