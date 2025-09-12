#pragma once
#include <cmath>

class Point {
private:
    float x;
    float y;

public:
    Point(float x = 0.0f, float y = 0.0f);

    float get_x() const;
    float get_y() const;

    void set_x(float new_x);
    void set_y(float new_y);

    float distance_to(const Point& other) const;
    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
};