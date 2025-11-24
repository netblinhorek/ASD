#pragma once
#include "../lib_point/point.h"
#include "string"
class Circle {
private:
    Point center;
    float radius;

public:
    Circle(float x = 0, float y = 0, float radius = 1);
    Circle(const Circle& other);

    Point get_center() const;
    float get_x() const;
    float get_y() const;
    float get_radius() const;

    void set_center(const Point& center);
    void set_x(float x);
    void set_y(float y);
    void set_radius(float radius);
    float distance_to(const Circle& other) const;
};

template<typename CircleT>
std::string get_circles_relation(const CircleT& c1, const CircleT& c2) {
    float d = c1.distance_to(c2); 
    float r1 = c1.get_radius();
    float r2 = c2.get_radius();
    float sum_r = r1 + r2;
    float diff_r = std::abs(r1 - r2);

    if (d == 0 && r1 == r2) return "Coincide";
    if (d == sum_r) return "External touch";
    if (d == diff_r && d > 0) return "Inner touch";
    if (diff_r < d && d < sum_r) return "Intersect";
    if (d < diff_r) return "One inside the other";
    return "Not intersected";
}
