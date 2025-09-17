// Copyright 2024 Marina Usova

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>

//#define EASY_EXAMPLE
//#define MATHVECTOR
// #define MATRIX
//#define TRIANGLE

#define MENU
#ifdef MENU
#include "../lib_Triangle/triangle.h"
#endif

#ifdef EASY_EXAMPLE
#include "../lib_easy_example/easy_example.h"
#endif

#ifdef MATHVECTOR
#include "../lib_MathVector/mathvector.h"
#endif

#ifdef MATRIX
#include "../lib_Matrix/matrix.h"
#endif

#ifdef TRIANGLE
#include "../lib_Triangle/triangle.h"
#endif

//int main() {
#ifdef EASY_EXAMPLE
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
#endif  // EASY_EXAMPLE

#ifdef MATHVECTOR
MathVector<double> vec1;
vec1.push_back(1);
vec1.push_back(2);
vec1.push_back(3);

MathVector<double> vec2;
vec2.push_back(4);
vec2.push_back(2);
vec2.push_back(6);

MathVector<double> vec3;
vec3.push_back(7);
vec3.push_back(0);
vec3.push_back(6);

MathVector<double> vec4;
vec4.push_back(7);
vec4.push_back(0);

try {
    MathVector<double> result = vec1 + vec2;
    std::cout << "Vector sum: " << result << std::endl;
}
catch (std::exception err) {
    std::cerr << err.what() << std::endl;
}
try {
    MathVector<double> result = vec1 - vec2;
    std::cout << "Vector sub: " << result << std::endl;
}
catch (std::exception err) {
    std::cerr << err.what() << std::endl;
}
try {
    MathVector<double> result = vec1 * vec2;
    std::cout << "Vector mult: " << result << std::endl;
}
catch (std::exception err) {
    std::cerr << err.what() << std::endl;
}
try {
    MathVector<double> result = vec1 / vec2;
    std::cout << "Vector div: " << result << std::endl;
}
catch (std::exception err) {
    std::cerr << err.what() << std::endl;
}
try {
    MathVector<double> result = vec1 / vec3;
    std::cout << "Vector div: " << result << std::endl;
}
catch (std::exception err) {
    std::cerr << err.what() << std::endl;
}
try {
    MathVector<double> result = vec3 / vec2;
    std::cout << "Vector div: " << result << std::endl;
}
catch (std::exception err) {
    std::cerr << err.what() << std::endl;
}
try {
    MathVector<double> result = vec3 + vec4;
    std::cout << "Vector div: " << result << std::endl;
}
catch (std::exception err) {
    std::cerr << err.what() << std::endl;
}
#endif  // MATHVECTOR

#ifdef MATRIX
Matrix<double> mat1(2, 2);
mat1[0][0] = 1; mat1[0][1] = 2;
mat1[1][0] = 3; mat1[1][1] = 4;

Matrix<double> mat2(2, 2);
mat2[0][0] = 5; mat2[0][1] = 6;
mat2[1][0] = 7; mat2[1][1] = 8;

Matrix<double> mat3(2, 2);
mat3[0][0] = 0; mat3[0][1] = 6;
mat3[1][0] = 7; mat3[1][1] = 1;

Matrix<double> mat4(1, 2);
mat4[0][0] = 0; mat4[0][1] = 6;

Matrix<double> mat5(2, 1);
mat5[0][0] = 0;
mat5[1][0] = 7;

double a = 2;
try {
    Matrix<double> result = mat1 + mat2;
    std::cout << "Matrix sum:\n" << result << std::endl;
}
catch (std::exception err) {
    std::cerr << err.what() << std::endl;
}
try {
    Matrix<double> result = mat1 - mat2;
    std::cout << "\nMatrix sub:\n" << result << std::endl;
}
catch (std::exception err) {
    std::cerr << err.what() << std::endl;
}
try {
    Matrix<double> result = mat1 * mat2;
    std::cout << "\nMatrix mult:\n" << result << std::endl;
}
catch (std::exception err) {
    std::cerr << err.what() << std::endl;
}
try {
    Matrix<double> result = mat1 / mat2;
    std::cout << "\nMatrix div:\n" << result << std::endl;
}
catch (std::exception err) {
    std::cerr << err.what() << std::endl;
}
try {
    Matrix<double> result = mat1 / mat3;
    std::cout << "\nMatrix div:\n" << result << std::endl;
}
catch (std::exception err) {
    std::cerr << "\n" << err.what() << std::endl;
}
try {
    Matrix<double> result = mat1 + a;
    std::cout << "\nMatrix sum_scalar_right:\n" << result << std::endl;
}
catch (std::exception err) {
    std::cerr << err.what() << std::endl;
}
try {
    Matrix<double> result = a + mat2;
    std::cout << "\nMatrix sum_scalar_left:\n" << result << std::endl;
}
catch (std::exception err) {
    std::cerr << err.what() << std::endl;
}
try {
    Matrix<double> result = -a + mat1;
    std::cout << "\nMatrix sum_unar:\n" << result << std::endl;
}
catch (std::exception err) {
    std::cerr << err.what() << std::endl;
}
try {
    Matrix<double> result = -a * mat3;
    std::cout << "\nMatrix sum_unar:\n" << result << std::endl;
}
catch (std::exception err) {
    std::cerr << err.what() << std::endl;
}
try {
    Matrix<double> result = mat3 * mat4;
    std::cout << "\nMatrix sum_unar:\n" << result << std::endl;
}
catch (std::exception err) {
    std::cerr << "\n" << err.what() << std::endl;
}
try {
    Matrix<double> result = mat3 * mat5;
    std::cout << "\nMatrix mult:\n" << result << std::endl;
}
catch (std::exception err) {
    std::cerr << err.what() << std::endl;
}
#endif  // MATRIX

#ifdef TRIANGLE


#endif TRIANGLE



#ifdef MENU

void create_regular_matrix(Matrix<double>& matrix, const std::string& name);
void create_triangle_matrix(Triangle<double>& matrix, const std::string& name);
void add_matrices();
void subtract_matrices();
void multiply_matrices();
void scalar_multiply();
void transpose_matrix();
int show_main_menu();


void create_regular_matrix(Matrix<double>& matrix, const std::string& name) {
    int rows, cols;
    std::cout << "\nСоздание матрицы " << name << std::endl;
    std::cout << "Введите количество строк: ";
    std::cin >> rows;
    std::cout << "Введите количество столбцов: ";
    std::cin >> cols;

    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Размеры матрицы должны быть положительными");
    }

    matrix = Matrix<double>(rows, cols);
    std::cout << "Матрица " << name << " создана размером " << rows << "x" << cols << std::endl;

    std::cout << "Заполните матрицу значениями:" << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << "Элемент [" << i << "][" << j << "]: ";
            std::cin >> matrix[i][j];
        }
    }
}

void create_triangle_matrix(Triangle<double>& matrix, const std::string& name, int size, TriangleType type) {
    matrix = Triangle<double>(size, type);
    std::cout << "Треугольная матрица " << name << " создана размером " << size << "x" << size << std::endl;
    std::cout << "Заполните значимые элементы матрицы:" << std::endl;
    if (type == TriangleType::Lower) {
        for (int i = 0; i < size; ++i)
            for (int j = i; j < size; ++j) {
                std::cout << name << "[" << i << "][" << j << "]: ";
                std::cin >> matrix(i, j);
            }
    }
    else {
        for (int i = 0; i < size; ++i)
            for (int j = 0; j <= i; ++j) {
                std::cout << name << "[" << i << "][" << j << "]: ";
                std::cin >> matrix(i, j);
            }
    }
}
void create_triangle_matrix(Triangle<double>& matrix, const std::string& name) {
    int size;
    int type_choice;

    std::cout << "\nСоздание треугольной матрицы " << name << std::endl;
    std::cout << "Введите размер матрицы (N x N): ";
    std::cin >> size;

    if (size <= 0) {
        throw std::invalid_argument("Размер матрицы должен быть положительным");
    }

    std::cout << "Выберите тип треугольной матрицы:" << std::endl;
    std::cout << "1. Нижняя треугольная" << std::endl;
    std::cout << "2. Верхняя треугольная" << std::endl;
    std::cout << "Выбор: ";
    std::cin >> type_choice;

    TriangleType type;
    if (type_choice == 1) {
        type = TriangleType::Lower;
    }
    else if (type_choice == 2) {
        type = TriangleType::Upper;
    }
    else {
        throw std::invalid_argument("Неверный выбор типа матрицы");
    }

    create_triangle_matrix(matrix, name, size, type);
}
void add_matrices() {
    int choice;
    std::cout << "\n=== СЛОЖЕНИЕ МАТРИЦ ===" << std::endl;
    std::cout << "1. Обычные матрицы" << std::endl;
    std::cout << "2. Треугольные матрицы" << std::endl;
    std::cout << "Выбор: ";
    std::cin >> choice;

    if (choice == 1) {
        int rows, cols;
        std::cout << "Введите количество строк: ";
        std::cin >> rows;
        std::cout << "Введите количество столбцов: ";
        std::cin >> cols;
        if (rows <= 0 || cols <= 0) {
            std::cout << "Ошибка: Размеры матрицы должны быть положительными" << std::endl;
            return;
        }
        Matrix<double> m1(rows, cols), m2(rows, cols);
        std::cout << "Заполните матрицу A:" << std::endl;
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j) {
                std::cout << "A[" << i << "][" << j << "]: ";
                std::cin >> m1[i][j];
            }
        std::cout << "Заполните матрицу B:" << std::endl;
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j) {
                std::cout << "B[" << i << "][" << j << "]: ";
                std::cin >> m2[i][j];
            }
        try {
            std::cout << "\nРезультат сложения:" << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    }
    else {
        Triangle<double> t1, t2;
        create_triangle_matrix(t1, "A");
        create_triangle_matrix(t2, "B", t1.rows(), t1.get_type());
        try {
            if (t1.get_type() != t2.get_type()) {
                throw std::invalid_argument("Типы треугольных матриц должны совпадать");
            }
            std::cout << "\nРезультат сложения:" << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    }
}

void subtract_matrices() {
    int choice;
    std::cout << "\n=== ВЫЧИТАНИЕ МАТРИЦ ===" << std::endl;
    std::cout << "1. Обычные матрицы" << std::endl;
    std::cout << "2. Треугольные матрицы" << std::endl;
    std::cout << "Выбор: ";
    std::cin >> choice;

    if (choice == 1) {
        int rows, cols;
        std::cout << "Введите количество строк: ";
        std::cin >> rows;
        std::cout << "Введите количество столбцов: ";
        std::cin >> cols;
        if (rows <= 0 || cols <= 0) {
            std::cout << "Ошибка: Размеры матрицы должны быть положительными" << std::endl;
            return;
        }
        Matrix<double> m1(rows, cols), m2(rows, cols);
        std::cout << "Заполните матрицу A:" << std::endl;
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j) {
                std::cout << "A[" << i << "][" << j << "]: ";
                std::cin >> m1[i][j];
            }
        std::cout << "Заполните матрицу B:" << std::endl;
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j) {
                std::cout << "B[" << i << "][" << j << "]: ";
                std::cin >> m2[i][j];
            }
        try {
            std::cout << "\nРезультат вычитания:" << std::endl;
            
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    }
    else {
        Triangle<double> t1, t2;
        create_triangle_matrix(t1, "A");
        create_triangle_matrix(t2, "B", t1.rows(), t1.get_type());
        try {
            if (t1.get_type() != t2.get_type()) {
                throw std::invalid_argument("Типы треугольных матриц должны совпадать");
            }
            std::cout << "\nРезультат вычитания:" << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    }
}

void multiply_matrices() {
    int choice;
    std::cout << "\n=== УМНОЖЕНИЕ МАТРИЦ ===" << std::endl;
    std::cout << "1. Обычные матрицы" << std::endl;
    std::cout << "2. Треугольные матрицы" << std::endl;
    std::cout << "Выбор: ";
    std::cin >> choice;

    if (choice == 1) {
        int rows, cols, cols2;
        std::cout << "Введите количество строк первой матрицы: ";
        std::cin >> rows;
        std::cout << "Введите количество столбцов первой матрицы (и строк второй): ";
        std::cin >> cols;
        std::cout << "Введите количество столбцов второй матрицы: ";
        std::cin >> cols2;
        if (rows <= 0 || cols <= 0 || cols2 <= 0) {
            std::cout << "Ошибка: Размеры матрицы должны быть положительными" << std::endl;
            return;
        }
        Matrix<double> m1(rows, cols), m2(cols, cols2);
        std::cout << "Заполните матрицу A:" << std::endl;
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j) {
                std::cout << "A[" << i << "][" << j << "]: ";
                std::cin >> m1[i][j];
            }
        std::cout << "Заполните матрицу B:" << std::endl;
        for (int i = 0; i < cols; ++i)
            for (int j = 0; j < cols2; ++j) {
                std::cout << "B[" << i << "][" << j << "]: ";
                std::cin >> m2[i][j];
            }
        try {
            std::cout << "\nРезультат умножения:" << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    }
    else {
        Triangle<double> t1, t2;
        create_triangle_matrix(t1, "A");
        create_triangle_matrix(t2, "B", t1.rows(), t1.get_type());
        try {
            std::cout << "\nРезультат умножения:" << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    }
}

void scalar_multiply() {
    int choice;
    double scalar;
    std::cout << "\n=== УМНОЖЕНИЕ НА СКАЛЯР ===" << std::endl;
    std::cout << "1. Обычная матрица" << std::endl;
    std::cout << "2. Треугольная матрица" << std::endl;
    std::cout << "Выбор: ";
    std::cin >> choice;
    std::cout << "Введите скаляр: ";
    std::cin >> scalar;
    if (choice == 1) {
        int rows, cols;
        std::cout << "Введите количество строк: ";
        std::cin >> rows;
        std::cout << "Введите количество столбцов: ";
        std::cin >> cols;
        if (rows <= 0 || cols <= 0) {
            std::cout << "Ошибка: Размеры матрицы должны быть положительными" << std::endl;
            return;
        }
        Matrix<double> m(rows, cols);
        std::cout << "Заполните матрицу:" << std::endl;
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j) {
                std::cout << "A[" << i << "][" << j << "]: ";
                std::cin >> m[i][j];
            }
        std::cout << "\nРезультат умножения на скаляр:" << std::endl;
    }
    else {
        Triangle<double> t;
        create_triangle_matrix(t, "A");
        for (size_t i = 0; i < t.rows(); ++i) {
            for (size_t j = 0; j < t.rows(); ++j) {
                if ((t.get_type() == TriangleType::Lower && j >= i) ||
                    (t.get_type() == TriangleType::Upper && j <= i)) {
                }
            }
        }
        std::cout << "\nРезультат умножения на скаляр:" << std::endl;
    }
}

void transpose_matrix() {
    int choice;
    std::cout << "\n=== ТРАНСПОНИРОВАНИЕ МАТРИЦЫ ===" << std::endl;
    std::cout << "1. Обычная матрица" << std::endl;
    std::cout << "2. Треугольная матрица" << std::endl;
    std::cout << "Выбор: ";
    std::cin >> choice;
    if (choice == 1) {
        int rows, cols;
        std::cout << "Введите количество строк: ";
        std::cin >> rows;
        std::cout << "Введите количество столбцов: ";
        std::cin >> cols;
        if (rows <= 0 || cols <= 0) {
            std::cout << "Ошибка: Размеры матрицы должны быть положительными" << std::endl;
            return;
        }
        Matrix<double> m(rows, cols);
        std::cout << "Заполните матрицу:" << std::endl;
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j) {
                std::cout << "A[" << i << "][" << j << "]: ";
                std::cin >> m[i][j];
            }
        try {
            std::cout << "\nТранспонированная матрица:" << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    }
    else {
        std::cout << "Транспонирование треугольных матриц меняет их тип" << std::endl;
        Triangle<double> t;
        create_triangle_matrix(t, "A");
        TriangleType new_type = (t.get_type() == TriangleType::Lower) ? TriangleType::Upper : TriangleType::Lower;
        for (size_t i = 0; i < t.rows(); ++i) {
            for (size_t j = 0; j < t.rows(); ++j) {
                if ((new_type == TriangleType::Lower && j >= i) ||
                    (new_type == TriangleType::Upper && j <= i)) {
                }
            }
        }
        std::cout << "\nТранспонированная матрица:" << std::endl;
    }
}

int show_main_menu() {
    int choice;
    std::cout << "\n=== ГЛАВНОЕ МЕНЮ ===" << std::endl;
    std::cout << "1. Сложение матриц" << std::endl;
    std::cout << "2. Вычитание матриц" << std::endl;
    std::cout << "3. Умножение матриц" << std::endl;
    std::cout << "4. Умножение на скаляр" << std::endl;
    std::cout << "5. Транспонирование матрицы" << std::endl;
    std::cout << "6. Показать информацию о матрицах" << std::endl;
    std::cout << "0. Выйти" << std::endl;
    std::cout << "Выбор: ";
    std::cin >> choice;
    return choice;
}

int main() {
    setlocale(LC_ALL, "rus");

    std::cout << "================================" << std::endl;
    std::cout << "|   СИСТЕМА РАБОТЫ С МАТРИЦАМИ  |" << std::endl;
    std::cout << "|  (обычные и треугольные)      |" << std::endl;
    std::cout << "================================" << std::endl;

    try {
        while (true) {
            int choice = show_main_menu();

            switch (choice) {
            case 1:
                add_matrices();
                break;
            case 2:
                subtract_matrices();
                break;
            case 3:
                multiply_matrices();
                break;
            case 4:
                scalar_multiply();
                break;
            case 5:
                transpose_matrix();
                break;
            case 6:
                std::cout << "\nИнформация о типах матриц:" << std::endl;
                std::cout << "- Обычные матрицы: любые размеры M x N" << std::endl;
                std::cout << "- Треугольные матрицы: только квадратные N x N" << std::endl;
                std::cout << "- Нижние треугольные: нули выше главной диагонали" << std::endl;
                std::cout << "- Верхние треугольные: нули ниже главной диагонали" << std::endl;
                break;
            case 0:
                std::cout << "Выход из программы..." << std::endl;
                return 0;
            default:
                std::cout << "Неверный выбор! Попробуйте снова." << std::endl;
                break;
            }

            std::cout << "\nНажмите Enter для продолжения...";
            std::cin.ignore();
            std::cin.get();
        }
    }
    catch (const std::exception& e) {
        std::cout << "Произошла ошибка: " << e.what() << std::endl;
    }

    return 0;
}

#endif MENU