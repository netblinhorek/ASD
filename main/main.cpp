// Copyright 2024 Marina Usova
//#define EASY_EXAMPLE
//#define PLAY_GAME
#define  LABIRINT

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

#ifdef LABIRINT
#include <iostream>
#include "../lib_DSU/DSU.h"
#include <ctime>
#include "../lib_Matrix/matrix.h"




bool check_path(size_t M, size_t N, DSU& logic, size_t X, size_t Y) {
    int start_cell = X - 1;  
    int end_cell = (N - 1) * M + (Y - 1); 

    return logic.find(start_cell) == logic.find(end_cell);
}

void print(Matrix<bool> labirint, DSU& logic, size_t N, size_t M, size_t X, size_t Y) {
    std::cout << "\nЋабиринт:\n";

    for (int p = 1; p <= M; p++) {
        if (p == X) {
            std::cout << "   X    ";
        }
        else {
            std::cout << "        ";
        }
    }
    std::cout << "\n";

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i == 0) {
                if (j + 1 == X) {
                    std::cout << "---  ---";
                }
                else {
                    std::cout << "--------";
                }
            }
            else {
                int curr = i * M + j;
                if (logic.find(curr) != logic.find(curr - M)) {
                    std::cout << "--------"; 
                }
                else {
                    std::cout << "        "; 
                }
            }
        }
        std::cout << "\n";

        for (int j = 0; j < M; j++) {
            if (j == 0) {
                std::cout << "|";
            }
            int curr = i * M + j;
            if (curr < 10) {
                std::cout << "   " << curr << "   ";
            }
            else if (curr < 100) {
                std::cout << "   " << curr << "  ";
            }
            else if(curr < 1000) {
                std::cout << "   " << curr << " ";
            }
            else {
                std::cout << "  " << curr << " ";
         
            }
            if (j < M - 1) {
                if (logic.find(curr) != logic.find(curr + 1)) std::cout << "|";
                else std::cout << " ";
            }
            else {
                std::cout << "|"; 
            }
        }
        std::cout << "\n";
    }

    for (int j = 0; j < M; j++) {
        if (j + 1 == Y) {
            std::cout << "---  ---";
        }
        else {
            std::cout << "--------";
        }
    }
    std::cout << "\n";

    for (int p = 1; p <= M; p++) {
        if (p == Y) {
            std::cout << "   Y    ";
        }
        else {
            std::cout << "        ";
        }
    }
    std::cout << "\n";
}
void generate(size_t N, size_t M, size_t X, size_t Y) {
    Matrix<bool> labirint(N, M, false);

    do {
        DSU logic(M * N);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                int curr = i * M + j;


                if (j < M - 1) {
                    if (rand() % 10 == 0) {
                        logic.union_set(curr, curr + 1);
                        labirint[i][j] = true;
                    }
                }
                if (i < N - 1) {
                    if (rand() % 10 == 0)
                        logic.union_set(curr, curr + M);
                }
            }
        }
        
        if (check_path(M, N, logic, X, Y)) {
            print(labirint, logic, N, M, X, Y);
            break;
        }

    } while (true);

}

void user_input(size_t& M, size_t& N, size_t& X, size_t& Y) {
    std::cout << "¬ведите ширину M и высоту N: ";
    std::cin >> M >> N;
    std::cout << "¬ведите точку входа X и выхода Y (от 1 до " << M << "): ";
    std::cin >> X >> Y;
    if (X < 1 || X > M) {
        throw std::logic_error("Going beyond borders");
    }
    if (Y < 1 || Y > M) {
        throw std::logic_error("Going beyond borders");
    }
}

int main() {
    size_t M, N, X, Y;
    
    setlocale(LC_ALL, "rus");
    srand(time(0));
    user_input(M, N, X, Y);
    DSU logic(M * N);
    
    generate(N, M, X, Y);


}
#endif