#pragma once
#include "circle.h"
#include <stdexcept>
#include <cmath>

Circle::Circle(float x, float y, float radius)
    : center(x, y), radius(radius)
{
    if (radius < 0) {
        throw std::invalid_argument("Radius cannot be negative");
    }
}

Circle::Circle(const Circle& other) : center(other.center), radius(other.radius) {}

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
    this->center.set_x(x);
}
void Circle::set_y(float y) {
    this->center.set_y(y);
}

void Circle::set_radius(float radius) {
    if (radius < 0) {
        throw std::invalid_argument("Radius cannot be negative");
    }
    this->radius = radius;
}

float Circle::distance_to(const Circle& other) const {
    return center.distance_to(other.center);
}
