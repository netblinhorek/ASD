// Copyright 2024 Marina Usova

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>

//#define EASY_EXAMPLE
//#define MATHVECTOR
// #define MATRIX
//#define TRIANGLE
//#define STACK
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

#ifdef STACK
#include "../lib_Stack/stack.h"
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

void start_print() {
    std::cout << "================================" << std::endl;
    std::cout << "|   СИСТЕМА РАБОТЫ С МАТРИЦАМИ  |" << std::endl;
    std::cout << "|  (обычные и треугольные)      |" << std::endl;
    std::cout << "================================" << std::endl;
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

void information_about_matrix() {
    std::cout << "\nИнформация о типах матриц:" << std::endl;
    std::cout << "- Обычные матрицы: любые размеры M x N" << std::endl;
    std::cout << "- Треугольные матрицы: только квадратные N x N" << std::endl;
    std::cout << "- Нижние треугольные: нули выше главной диагонали" << std::endl;
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

void show_matrix_info(const Matrix<double>& m, const std::string& name) {
    std::cout << "Текущая матрица " << name << ": " << m.rows() << " x " << m.cols() << std::endl;
    std::cout << m << std::endl;
}

void input_matrix(Matrix<double>& m, const std::string& name) {
    int rows, cols;
    std::cout << "Введите количество строк для " << name << ": ";
    std::cin >> rows;
    std::cout << "Введите количество столбцов для " << name << ": ";
    std::cin >> cols;

    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Размеры матрицы должны быть положительными");
    }

    m = Matrix<double>(rows, cols);
    std::cout << "Заполните матрицу " << name << ":\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << "  [" << i << "," << j << "]: ";
            std::cin >> m[i][j];
        }
    }
    std::cout << "Заполнение матрицы выполнено\n";
    show_matrix_info(m, name);
}

void input_matrix(Matrix<double>& m, const std::string& name, int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Размеры матрицы должны быть положительными");
    }

    m = Matrix<double>(rows, cols);
    std::cout << "Заполните матрицу " << name << ":\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << "  [" << i << "," << j << "]: ";
            std::cin >> m[i][j];
        }
    }
    std::cout << "Заполнение матрицы выполнено\n";
    show_matrix_info(m, name);
}

void show_triangle_info(const Triangle<double>& t, const std::string& name) {
    std::cout << "Текущая треугольная матрица " << name << ": " << t.rows() << " x " << t.rows();
    std::cout << " (нижняя)" << std::endl;

    size_t size = t.rows();
    for (size_t i = 0; i < size; ++i) {
        std::cout << "  ";
        for (size_t j = 0; j < size; ++j) {
            try {
                std::cout << std::setw(8) << t(i, j) << " ";
            }
            catch (const std::exception&) {
                std::cout << std::setw(8) << "0" << " ";
            }
        }
        std::cout << std::endl;
    }
}

void input_triangle_with_size(Triangle<double>& t, const std::string& name, int size) {
    t = Triangle<double>(size, 0.0, TriangleType::Lower);

    std::cout << "Заполните треугольную матрицу " << name << ":\n";

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j <= i; ++j) {
            std::cout << "  [" << i << "," << j << "]: ";
            std::cin >> t(i, j);
        }
    }

    std::cout << "Заполнение матрицы выполнено\n";
    show_triangle_info(t, name);
}

void input_triangle(Triangle<double>& t, const std::string& name) {
    int size;
    std::cout << "Введите размер треугольной матрицы " << name << " (N x N): ";
    std::cin >> size;

    if (size <= 0) {
        throw std::invalid_argument("Размер матрицы должен быть положительным");
    }

    input_triangle_with_size(t, name, size);
}

void perform_matrix_operation(int choice, Matrix<double>& m1, Matrix<double>& m2, Matrix<double>& result,
    bool& has_m1, bool& has_m2) {
    if (has_m1) {
        show_matrix_info(m1, "A");
        std::cout << "Использовать текущую матрицу A? (y/n): ";
        char use_current;
        std::cin >> use_current;
        if (use_current != 'y' && use_current != 'Y') {
            input_matrix(m1, "A");
        }
    }
    else {
        input_matrix(m1, "A");
        has_m1 = true;
    }

    if (has_m2) {
        show_matrix_info(m2, "B");
        std::cout << "Использовать текущую матрицу B? (y/n): ";
        char use_current;
        std::cin >> use_current;
        if (use_current != 'y' && use_current != 'Y') {
            input_matrix(m2, "B", m1.rows(), m1.cols());
        }
    }
    else {
        input_matrix(m2, "B", m1.rows(), m1.cols());
        has_m2 = true;
    }

    try {
        switch (choice) {
        case 1: result = m1 + m2; break;
        case 2: result = m1 - m2; break;
        case 3: result = m1 * m2; break;
        }

        std::cout << "\nРезультат:\n";
        show_matrix_info(result, "Result");

        char use_result;
        std::cout << "Использовать полученную матрицу как новую матрицу A, B или не использовать? (a/b/n): ";
        std::cin >> use_result;
        if (use_result == 'a' || use_result == 'A') {
            m1 = result;
            has_m1 = true;
            std::cout << "Теперь матрица A:\n";
            show_matrix_info(m1, "A");
        }
        else if (use_result == 'b' || use_result == 'B') {
            m2 = result;
            has_m2 = true;
            std::cout << "Теперь матрица B:\n";
            show_matrix_info(m2, "B");
        }
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void perform_triangle_operation(int choice, Triangle<double>& t1, Triangle<double>& t2, Triangle<double>& tresult,
    bool& has_t1, bool& has_t2) {
    if (has_t1) {
        show_triangle_info(t1, "A");
        std::cout << "Использовать текущую матрицу A? (y/n): ";
        char use_current;
        std::cin >> use_current;
        if (use_current != 'y' && use_current != 'Y') {
            input_triangle(t1, "A");
        }
    }
    else {
        input_triangle(t1, "A");
        has_t1 = true;
    }

    int size = t1.rows();

    if (has_t2) {
        show_triangle_info(t2, "B");
        std::cout << "Использовать текущую матрицу B? (y/n): ";
        char use_current;
        std::cin >> use_current;
        if (use_current != 'y' && use_current != 'Y') {
            std::cout << "Матрица B будет создана размером " << size << "x" << size << " (как матрица A)\n";
            input_triangle_with_size(t2, "B", size);
        }
        else {
            if (t2.rows() != size) {
                std::cout << "Размеры матриц не совпадают! Матрица B будет пересоздана размером "
                    << size << "x" << size << std::endl;
                input_triangle_with_size(t2, "B", size);
            }
        }
    }
    else {
        std::cout << "Матрица B будет создана размером " << size << "x" << size << " (как матрица A)\n";
        input_triangle_with_size(t2, "B", size);
        has_t2 = true;
    }

    if (t1.rows() != t2.rows()) {
        std::cout << "Ошибка: размеры матриц не совпадают! ("
            << t1.rows() << "x" << t1.rows() << " vs "
            << t2.rows() << "x" << t2.rows() << ")" << std::endl;
        return;
    }

    try {
        switch (choice) {
        case 1: tresult = t1 + t2; break;
        case 2: tresult = t1 - t2; break;
        case 3: tresult = t1 * t2; break;
        }

        std::cout << "\nРезультат:\n";
        show_triangle_info(tresult, "Result");

        char use_result;
        std::cout << "Использовать полученную матрицу как новую матрицу A, B или не использовать? (a/b/n): ";
        std::cin >> use_result;
        if (use_result == 'a' || use_result == 'A') {
            t1 = tresult;
            has_t1 = true;
            std::cout << "Теперь матрица A:\n";
            show_triangle_info(t1, "A");
        }
        else if (use_result == 'b' || use_result == 'B') {
            t2 = tresult;
            has_t2 = true;
            std::cout << "Теперь матрица B:\n";
            show_triangle_info(t2, "B");
        }
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void perform_unary_matrix_operation(int choice, Matrix<double>& m1, Matrix<double>& result, bool& has_m1) {
    if (has_m1) {
        show_matrix_info(m1, "A");
        std::cout << "Использовать текущую матрицу A? (y/n): ";
        char use_current;
        std::cin >> use_current;
        if (use_current != 'y' && use_current != 'Y') {
            input_matrix(m1, "A");
        }
    }
    else {
        input_matrix(m1, "A");
        has_m1 = true;
    }

    try {
        switch (choice) {
        case 4: {
            double scalar;
            std::cout << "Введите скаляр: ";
            std::cin >> scalar;
            result = m1 * scalar;
            break;
        }
        case 5: {
            result = m1.transpose();
            break;
        }
        }

        std::cout << "\nРезультат:\n";
        show_matrix_info(result, "Result");

        char use_result;
        std::cout << "Использовать полученную матрицу как новую матрицу A? (y/n): ";
        std::cin >> use_result;
        if (use_result == 'y' || use_result == 'Y') {
            m1 = result;
            has_m1 = true;
            std::cout << "Теперь матрица A:\n";
            show_matrix_info(m1, "A");
        }
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void perform_unary_triangle_operation(int choice, Triangle<double>& t1, Triangle<double>& tresult, bool& has_t1) {
    if (has_t1) {
        show_triangle_info(t1, "A");
        std::cout << "Использовать текущую матрицу A? (y/n): ";
        char use_current;
        std::cin >> use_current;
        if (use_current != 'y' && use_current != 'Y') {
            input_triangle(t1, "A");
        }
    }
    else {
        input_triangle(t1, "A");
        has_t1 = true;
    }

    try {
        switch (choice) {
        case 4: {
            double scalar;
            std::cout << "Введите скаляр: ";
            std::cin >> scalar;
            tresult = t1 * scalar;
            break;
        }
        case 5: {
            tresult = t1.transpose();
            break;
        }
        }

        std::cout << "\nРезультат:\n";
        show_triangle_info(tresult, "Result");

        char use_result;
        std::cout << "Использовать полученную матрицу как новую матрицу A? (y/n): ";
        std::cin >> use_result;
        if (use_result == 'y' || use_result == 'Y') {
            t1 = tresult;
            has_t1 = true;
            std::cout << "Теперь матрица A:\n";
            show_triangle_info(t1, "A");
        }
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
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
//#ifdef STACK
//int main() {
//    setlocale(LC_ALL, "rus");
//    std::string input;
//
//    std::cout << "Введите выражение для проверки скобок: ";
//    std::getline(std::cin, input);
//
//    number_of_brackets(input);
//
//    if (check_of_brackets(input)) {
//        std::cout << "Скобки расставлены правильно!" << std::endl;
//    }
//    else {
//        std::cout << "Ошибка в расстановке скобок!" << std::endl;
//    }
//
//    return 0;
//}
//#endif STACK
