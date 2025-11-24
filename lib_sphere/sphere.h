#pragma once
#include "../lib_point3d/point3d.h"
#include "string"
class Sphere {
private:
    Point3D center;
    float radius;

public:
    Sphere(float x = 0, float y = 0, float z = 0, float radius = 1);
    Sphere(const Point3D& center, float radius = 1);

    Point3D get_center() const;
    float get_x() const;
    float get_y() const;
    float get_z() const;
    float get_radius() const;

    void set_center(const Point3D& center);
    void set_x(float x);
    void set_y(float y);
    void set_z(float z);
    void set_radius(float radius);

    float calculate_distance_from_origin() const;
    float distance_to(const Sphere& other) const;
   

    bool operator==(const Sphere& other) const;
    bool operator!=(const Sphere& other) const;
};


