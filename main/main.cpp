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
#include "../lib_Matrix/matrix.h"
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

int show_main_menu();


void create_regular_matrix(Matrix<double>& matrix, const std::string& name) {
    int rows, cols;
    std::cout << "\nСоздание матрицы " << name << std::endl;
    std::cout << "Введите количество строк: ";
    std::cin >> rows;
    std::cout << "Введите количество столбцов: ";
    std::cin >> cols;

    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Размеры матрицы должны быть"
            "положительными");
    }

    matrix = Matrix<double>(rows, cols);
    std::cout << "Матрица " << name << " создана размером " << rows
        << "x" << cols << std::endl;

    std::cout << "Заполните матрицу значениями:" << std::endl;
}

void create_triangle_matrix(Triangle<double>& matrix,
    const std::string& name,
    int size, TriangleType type) {
    matrix = Triangle<double>();
    std::cout << "Треугольная матрица " << name 
        << " создана размером " << size 
        << "x" << size << std::endl;
    std::cout << "Заполните значимые элементы матрицы:" 
        << std::endl;
}
void create_triangle_matrix(Triangle<double>& matrix,
    const std::string& name) {
    int size;
    int type_choice;

    std::cout << "\nСоздание треугольной матрицы " << name
        << std::endl;
    std::cout << "Введите размер матрицы (N x N): ";
    std::cin >> size;

    if (size <= 0) {
        throw std::invalid_argument("Размер матрицы должен быть"
            "положительным");
    }

    std::cout << "Выберите тип треугольной матрицы:"
        << std::endl;
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
        throw std::invalid_argument("Неверный выбор типа"
            "матрицы");
    }

    create_triangle_matrix(matrix, name, size, type);
}

int show_main_menu() {
    int choice;
    std::cout << "\n=== ГЛАВНОЕ МЕНЮ ===" << std::endl;
    std::cout << "1. Сложение матриц" << std::endl;
    std::cout << "2. Вычитание матриц" << std::endl;
    std::cout << "3. Умножение матриц" << std::endl;
    std::cout << "4. Умножение на скаляр" << std::endl;
    std::cout << "5. Деление на скаляр" << std::endl;
    std::cout << "6. Транспонирование матрицы" << std::endl;
    std::cout << "7. Показать информацию о матрицах" << std::endl;
    std::cout << "0. Выйти" << std::endl;
    std::cout << "Выбор: ";
    std::cin >> choice;
    return choice;
}

template<typename T>
bool ask_continue(const std::string& msg, T& obj, bool& has_obj) {
    if (!has_obj) return false;
    char again;
    std::cout << msg;
    std::cin >> again;
    if (again == 'y' || again == 'Y') return true;
    has_obj = false;
    return false;
}

void input_matrix(Matrix<double>& m, const std::string& name) {
    int rows, cols;
    std::cout << "Введите количество строк для " << name << ": ";
    std::cin >> rows;
    std::cout << "Введите количество столбцов для " << name << ": ";
    std::cin >> cols;
    m = Matrix<double>(rows, cols);
    std::cout << "Заполните матрицу " << name << ":\n/.../\nЗаполнение матрицы выполнено\n";
}

void show_matrix_info(const Matrix<double>& m, const std::string& name) {
    std::cout << "Текущая матрица " << name << ": " << m.rows() << " x " << m.cols() << std::endl;
}

void input_triangle(Triangle<double>& t, const std::string& name) {
    int size, type_choice;
    std::cout << "Введите размер треугольной матрицы " << name << " (N x N): ";
    std::cin >> size;
    std::cout << "1. Нижняя треугольная\n2. Верхняя треугольная\nВыбор: ";
    std::cin >> type_choice;
    TriangleType ttype = (type_choice == 1) ? TriangleType::Lower : TriangleType::Upper;
    t = Triangle<double>();
    std::cout << "Заполните треугольную матрицу " << name << ":\n/.../\nЗаполнение матрицы выполнено\n";
}

void show_triangle_info(const Triangle<double>& t, const std::string& name) {
    std::cout << "Текущая треугольная матрица " << name << ": " << t.rows() << " x " << t.rows();
    std::cout << " (" << (t.get_type() == TriangleType::Lower ? "нижняя" : "верхняя") << ")" << std::endl;
}
void start_print() {
    std::cout << "================================" << std::endl;
    std::cout << "|   СИСТЕМА РАБОТЫ С МАТРИЦАМИ  |" << std::endl;
    std::cout << "|  (обычные и треугольные)      |" << std::endl;
    std::cout << "================================" << std::endl;
}

void perform_matrix_operation(int choice, Matrix<double>& m1, Matrix<double>& m2, Matrix<double>& result,
    bool& has_m1, bool& has_m2) {
    if (has_m1) show_matrix_info(m1, "A");
    if (!ask_continue("Использовать первую матрицу (A)? (y/n): ", m1, has_m1)) {
        input_matrix(m1, "A");
        has_m1 = true;
    }
    if (has_m2) show_matrix_info(m2, "B");
    if (!ask_continue("Использовать вторую матрицу (B)? (y/n): ", m2, has_m2)) {
        input_matrix(m2, "B");
        has_m2 = true;
    }
    try {
        if (choice == 1) result = m1 + m2;
        if (choice == 2) result = m1 - m2;
        if (choice == 3) result = m1 * m2;
        if (choice == 4) result = m1 / m2;
        std::cout << "\nРезультат:\n" << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void perform_triangle_operation(int choice, Triangle<double>& t1, Triangle<double>& t2, Triangle<double>& tresult,
    bool& has_t1, bool& has_t2) {
    if (has_t1) show_triangle_info(t1, "A");
    if (!ask_continue("Использовать первую треугольную матрицу (A)? (y/n): ", t1, has_t1)) {
        input_triangle(t1, "A");
        has_t1 = true;
    }
    if (has_t2) show_triangle_info(t2, "B");
    if (!ask_continue("Использовать вторую треугольную матрицу (B)? (y/n): ", t2, has_t2)) {
        input_triangle(t2, "B");
        has_t2 = true;
    }
    try {
        if (choice == 1) tresult = t1 + t2;
        if (choice == 2) tresult = t1 - t2;
        if (choice == 3) tresult = t1 * t2;
        if (choice == 4) tresult = t1 / t2;
        std::cout << "\nРезультат:\n" << tresult << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void perform_unary_matrix_operation(int choice, Matrix<double>& m1, Matrix<double>& result, bool& has_m1) {
    if (has_m1) show_matrix_info(m1, "");
    if (!ask_continue("Использовать текущую матрицу? (y/n): ", m1, has_m1)) {
        input_matrix(m1, "");
        has_m1 = true;
    }
    try {
        if (choice == 5) {
            double scalar;
            std::cout << "Введите скаляр: ";
            std::cin >> scalar;
            result = m1 * scalar;
        }
        if (choice == 6) {
            double scalar;
            std::cout << "Введите скаляр: ";
            std::cin >> scalar;
            result = m1 / scalar;
        }
        if (choice == 7) {
            result = m1.transpose();
        }
        std::cout << "\nРезультат:\n" << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void perform_unary_triangle_operation(int choice, Triangle<double>& t1, Triangle<double>& tresult, bool& has_t1) {
    if (has_t1) show_triangle_info(t1, "");
    if (!ask_continue("Использовать текущую треугольную матрицу? (y/n): ", t1, has_t1)) {
        input_triangle(t1, "");
        has_t1 = true;
    }
    try {
        if (choice == 5) {
            double scalar;
            std::cout << "Введите скаляр: ";
            std::cin >> scalar;
            tresult = t1 * scalar;
        }
        if (choice == 6) {
            double scalar;
            std::cout << "Введите скаляр: ";
            std::cin >> scalar;
            tresult = t1 / scalar;
        }
        if (choice == 7) {
            tresult = t1.transpose();
        }
        std::cout << "\nРезультат:\n" << tresult << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}
void information_about_matrix() {
    std::cout << "\nИнформация о типах матриц:" << std::endl;
    std::cout << "- Обычные матрицы: любые размеры M x N" << std::endl;
    std::cout << "- Треугольные матрицы: только квадратные N x N" << std::endl;
    std::cout << "- Нижние треугольные: нули выше главной диагонали" << std::endl;
    std::cout << "- Верхние треугольные: нули ниже главной диагонали" << std::endl;
}

int main() {
    setlocale(LC_ALL, "rus");

    Matrix<double> m1, m2, result;
    bool has_m1 = false, has_m2 = false;
    Triangle<double> t1, t2, tresult;
    bool has_t1 = false, has_t2 = false;

    start_print();

    try {
        while (true) {
            int choice = show_main_menu();
            if (choice == 0) {
                std::cout << "Выход из программы..." << std::endl;
                break;
            }

            switch (choice) {
            case 1:
            case 2:
            case 3:
            case 4:
            {
                int type;
                std::cout << "1. Обычные матрицы\n2. Треугольные матрицы\nВыбор: ";
                std::cin >> type;
                if (type == 1) {
                    perform_matrix_operation(choice, m1, m2, result, has_m1, has_m2);
                }
                else {
                    perform_triangle_operation(choice, t1, t2, tresult, has_t1, has_t2);
                }
                break;
            }
            case 5:
            case 6:
            {
                int type;
                std::cout << "1. Обычная матрица\n2. Треугольная матрица\nВыбор: ";
                std::cin >> type;
                if (type == 1) {
                    perform_unary_matrix_operation(choice, m1, result, has_m1);
                }
                else {
                    perform_unary_triangle_operation(choice, t1, tresult, has_t1);
                }
                break;
            }
            case 7:
                information_about_matrix();
                break;
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
#endif