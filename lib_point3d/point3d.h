#pragma once
#include "../lib_point/point.h"

class Point3D : public Point {
private:
    float z;

public:
    Point3D(float x = 0.0f, float y = 0.0f, float z = 0.0f);

    float get_z() const;

    void set_z(float new_z);

    float distance_to(const Point3D& other) const;
    bool operator==(const Point3D& other) const;
    bool operator!=(const Point3D& other) const;
};