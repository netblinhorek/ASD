// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
 //#define CIRCLE_RELATION_EXAMPLE
 //#define SPHERE_RELATION_EXAMPLE

#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"

int main() {
    int a, b;
    float result;

    a = 1; b = 4;

    try {
        result = division(a, b);
        std::cout << a << " / " << b << " = "
            << std::setprecision(2) << result << std::endl;
    }
    catch (std::exception err) {
        std::cerr << err.what() << std::endl;
    }

    a = 1; b = 0;

    try {
        result = division(a, b);
        std::cout << a << " / " << b << " = "
            << std::setprecision(2) << result << std::endl;
    }
    catch (std::exception err) {
        std::cerr << err.what() << std::endl;
    }

    return 0;
}

#endif  // EASY_EXAMPLE
#ifdef CIRCLE_RELATION_EXAMPLE

#include <iostream>
#include <string>
#include "../lib_circle/circle.h"
#include "../lib_point/point.h"

int main() {

    Circle c1(0, 0, 5);
    Circle c2(0, 0, 3);
    std::string relation1 = get_circles_relation(c1, c2);
    std::cout << "Circle 1: center(" << c1.get_x() << ", " << c1.get_y()
        << "), radius " << c1.get_radius() << std::endl;
    std::cout << "Circle 2: center(" << c2.get_x() << ", " << c2.get_y()
        << "), radius " << c2.get_radius() << std::endl;
    std::cout << "Relation: " << relation1 << std::endl << std::endl;

    Circle c3(0, 0, 5);
    Circle c4(10, 0, 5);
    std::string relation2 = get_circles_relation(c3, c4);
    std::cout << "Circle 3: center(" << c3.get_x() << ", " << c3.get_y()
        << "), radius " << c3.get_radius() << std::endl;
    std::cout << "Circle 4: center(" << c4.get_x() << ", " << c4.get_y()
        << "), radius " << c4.get_radius() << std::endl;
    std::cout << "Relation: " << relation2 << std::endl << std::endl;

    Circle c5(0, 0, 5);
    Circle c6(7, 0, 4);
    std::string relation3 = get_circles_relation(c5, c6);
    std::cout << "Circle 5: center(" << c5.get_x() << ", " << c5.get_y()
        << "), radius " << c5.get_radius() << std::endl;
    std::cout << "Circle 6: center(" << c6.get_x() << ", " << c6.get_y()
        << "), radius " << c6.get_radius() << std::endl;
    std::cout << "Relation: " << relation3 << std::endl << std::endl;

    Circle c7(0, 0, 2);
    Circle c8(10, 10, 3);
    std::string relation4 = get_circles_relation(c7, c8);
    std::cout << "Circle 7: center(" << c7.get_x() << ", " << c7.get_y()
        << "), radius " << c7.get_radius() << std::endl;
    std::cout << "Circle 8: center(" << c8.get_x() << ", " << c8.get_y()
        << "), radius " << c8.get_radius() << std::endl;
    std::cout << "Relation: " << relation4 << std::endl;

    return 0;
}

#endif  // CIRCLE_RELATION_EXAMPLE
#ifdef SPHERE_RELATION_EXAMPLE

#include <iostream>
#include <string>
#include <cmath>
#include "../lib_sphere/sphere.h"
#include "../lib_point3d/point3d.h"


int main() {

    Sphere s1(0, 0, 0, 5);
    Sphere s2(0, 0, 0, 3);
    std::string relation1 = get_spheres_relation(s1, s2);
    std::cout << "Sphere 1: center(" << s1.get_x() << ", " << s1.get_y() << ", " << s1.get_z()
        << "), radius " << s1.get_radius() << std::endl;
    std::cout << "Sphere 2: center(" << s2.get_x() << ", " << s2.get_y() << ", " << s2.get_z()
        << "), radius " << s2.get_radius() << std::endl;
    std::cout << "Relation: " << relation1 << std::endl << std::endl;

    Sphere s3(0, 0, 0, 5);
    Sphere s4(10, 0, 0, 5);
    std::string relation2 = get_spheres_relation(s3, s4);
    std::cout << "Sphere 3: center(" << s3.get_x() << ", " << s3.get_y() << ", " << s3.get_z()
        << "), radius " << s3.get_radius() << std::endl;
    std::cout << "Sphere 4: center(" << s4.get_x() << ", " << s4.get_y() << ", " << s4.get_z()
        << "), radius " << s4.get_radius() << std::endl;
    std::cout << "Relation: " << relation2 << std::endl << std::endl;

    Sphere s5(0, 0, 0, 5);
    Sphere s6(7, 0, 0, 4);
    std::string relation3 = get_spheres_relation(s5, s6);
    std::cout << "Sphere 5: center(" << s5.get_x() << ", " << s5.get_y() << ", " << s5.get_z()
        << "), radius " << s5.get_radius() << std::endl;
    std::cout << "Sphere 6: center(" << s6.get_x() << ", " << s6.get_y() << ", " << s6.get_z()
        << "), radius " << s6.get_radius() << std::endl;
    std::cout << "Relation: " << relation3 << std::endl << std::endl;

    Sphere s7(0, 0, 0, 2);
    Sphere s8(10, 10, 10, 3);
    std::string relation4 = get_spheres_relation(s7, s8);
    std::cout << "Sphere 7: center(" << s7.get_x() << ", " << s7.get_y() << ", " << s7.get_z()
        << "), radius " << s7.get_radius() << std::endl;
    std::cout << "Sphere 8: center(" << s8.get_x() << ", " << s8.get_y() << ", " << s8.get_z()
        << "), radius " << s8.get_radius() << std::endl;
    std::cout << "Relation: " << relation4 << std::endl;

    return 0;
}

#endif  // SPHERE_RELATION_EXAMPLE