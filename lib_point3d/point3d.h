#pragma once

class Point3D {
private:
    float x;
    float y;
    float z;

public:
    Point3D(float x = 0.0f, float y = 0.0f, float z = 0.0f);

    float get_x() const;
    float get_y() const;
    float get_z() const;

    void set_x(float new_x);
    void set_y(float new_y);
    void set_z(float new_z);

    float distance_to(const Point3D& other) const;
    bool operator==(const Point3D& other) const;
    bool operator!=(const Point3D& other) const;
};