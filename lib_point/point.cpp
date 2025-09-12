#include "point.h"
#include <stdexcept>
#include <cmath>
#include <random>

Point::Point(float x, float y) : x(x), y(y) {}

float Point::get_x() const {
    return x;
}

float Point::get_y() const {
    return y;
}

void Point::set_x(float new_x) {
    x = new_x;
}

void Point::set_y(float new_y) {
    y = new_y;
}

float Point::distance_to(const Point& other) const {
    float dx = x - other.x;
    float dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}

bool Point::operator==(const Point& other) const {
    const float EPSILON = 0.000001f;
    return (std::abs(x - other.x) < EPSILON) &&
        (std::abs(y - other.y) < EPSILON);
}

bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}