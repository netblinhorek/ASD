// Copyright 2024 Marina Usova
//#define EASY_EXAMPLE
#define PLAY_GAME

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
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
    }

    a = 1; b = 0;

    try {
        result = division(a, b);
        std::cout << a << " / " << b << " = "
            << std::setprecision(2) << result << std::endl;
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
    }

    return 0;
}
#endif  // EASY_EXAMPLE

#ifdef PLAY_GAME

#include <iostream>
#include "../lib_the_number_of_islands/the_number_of_islands.h" 

int main() {
    field_games();
    print_field(); 
    
    int num_islands = checking_for_islands();
    std::cout << "Number of islands: " << num_islands << std::endl;

    return 0;
}

#endif  // PLAY_GAME