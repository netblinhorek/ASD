#pragma once
#include "circle.h"
#include <stdexcept>
#include <cmath>

Circle::Circle(float x, float y, float radius)
    : center(x, y), radius(radius)
{
    if (radius <= 0) {
        throw std::invalid_argument("Radius must be positive");
    }
}
Point Circle::get_center() const {
    return center;
}

float Circle::get_x() const {
    return center.get_x();
}

float Circle::get_y() const {
    return center.get_y();
}

float Circle::get_radius() const {
    return radius;
}

void Circle::set_center(const Point& new_center) {
    center = new_center;
}

void Circle::set_x(float x) {
    center.set_x(x);
}

void Circle::set_y(float y) {
    center.set_y(y);
}

void Circle::set_radius(float new_radius) {
    if (new_radius < 0) {
        throw std::invalid_argument("Radius cannot be negative");
    }
    radius = new_radius;
}

template<typename CircleT>
std::string get_circles_relation(const CircleT& c1, const CircleT& c2) {
    float dx = c1.get_x() - c2.get_x();
    float dy = c1.get_y() - c2.get_y();
    float d = std::sqrt(dx * dx + dy * dy);
    float r1 = c1.get_radius();
    float r2 = c2.get_radius();

    const float EPSILON = 0.000001f;

    if (std::abs(d) < EPSILON && std::abs(r1 - r2) < EPSILON) {
        return "Coincide";
    }
    if (std::abs(d - (r1 + r2)) < EPSILON) {
        return "External touch";
    }
    if (std::abs(d - std::abs(r1 - r2)) < EPSILON && d > EPSILON) {
        return "Inner touch";
    }
    if (std::abs(r1 - r2) < d && d < (r1 + r2)) {
        return "Intersect";
    }
    if (d < std::abs(r1 - r2)) {
        return "One inside the other";
    }
    return "Not intersected";
}
template std::string get_circles_relation<Circle>(const Circle&, const Circle&);
