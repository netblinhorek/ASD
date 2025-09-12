#pragma once
#include "../lib_point/point.h"
#include "string"
class Circle {
private:
    Point center;
    float radius;

public:
    Circle(float x = 0, float y = 0, float radius = 1);

    Point get_center() const;
    float get_x() const;
    float get_y() const;
    float get_radius() const;

    void set_center(const Point& center);
    void set_x(float x);
    void set_y(float y);
    void set_radius(float radius);
};

template<typename CircleT>
std::string get_circles_relation(const CircleT& c1, const CircleT& c2);
