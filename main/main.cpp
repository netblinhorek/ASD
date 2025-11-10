// Copyright 2024 Marina Usova

#include <iostream>
#include <string>
#include <map> // Добавляем include для std::map
#include <limits>
//#define EASY_EXAMPLE
#define ARITHMETIC_EXPRESSION_CALCULATOR
#ifdef EASY_EXAMPLE




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
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  a = 1; b = 0;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  return 0;
}

#endif EASY_EXAMPLE

#ifdef ARITHMETIC_EXPRESSION_CALCULATOR

#include "../lib_Expression/expression.h"
#include "../lib_Lexem/lexem.h"
#include "../lib_Parser/parser.h"
#include <iostream>
#include <string>

void print_expression(const std::map<int, Expression>& expressions, int selected_id) {
    std::cout << " + —————————————————————————————————————————————"
        "————————————————————————————————— +" << std::endl;
    std::cout << " | ID | EXPRESSION | VARIABLES VALUES |" << std::endl;
    std::cout << " +———————————————————————————————————————————————"
        "———————————————————————————————— +" << std::endl;

    if (expressions.empty()) {
        std::cout << " |   |   |" << std::endl;
    } else {
        for (const auto& pair : expressions) {
            int id = pair.first;
            const Expression& expr = pair.second;
            std::cout << " | " << id << " | ";
            std::cout << expr.get_expression_string() << " | "; 

            bool first_var = true;
            for (const auto& var_pair : expr.variables()) {
                if (!first_var) std::cout << ", ";
                std::cout << var_pair.first << " = " << var_pair.second;
                first_var = false;
            }
            std::cout << " |" << std::endl;
        }
    }

    std::cout << " +——————————————————————————————————————————————"
        "————————————————————————————————— +" << std::endl;
    if (selected_id != 0) {
        std::cout << "Текущее выбранное выражение: ID " << selected_id << std::endl;
    }
}

void print_menu() {
    std::cout << "1. Создать новое выражение" << std::endl;
    std::cout << "2. Задать переменные для выражения" << std::endl;
    std::cout << "3. Вычислить значение выражения" << std::endl;
    std::cout << "4. Удалить выражение" << std::endl;
    std::cout << "5. Выбрать выражение" << std::endl; 
    std::cout << "0. Выйти" << std::endl;
}

void create_new_expression(std::map<int, Expression>& expressions, int& next_id,
    int& selected_id) {
    std::cout << "Введите выражение: ";
    std::string expr_string;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    std::getline(std::cin, expr_string);

    try {
        expressions.emplace(next_id, Expression(expr_string));
        selected_id = next_id;
        std::cout << "Создано выражение ID: " << next_id
            << ", выражение: '" << expr_string << "'" << std::endl;
        next_id++;
    } catch (const std::exception& e) {
        std::cout << "Ошибка при создании выражения: " << e.what() << std::endl;
    }
}

void set_variables_for_expression(std::map<int, Expression>& expressions,
    int selected_id) {
    if (selected_id == 0 || expressions.find(selected_id) == expressions.end()) {
        std::cout << "Сначала выберите или создайте выражение!" << std::endl;
        return;
    }

    Expression& current_expr = expressions.at(selected_id);
    std::cout << "Введите значения переменных для выражения ID " << selected_id <<
        ". Введите 'x' и 'y':" << std::endl;

    double x_val, y_val;
    std::cout << "x = ";
    std::cin >> x_val;
    current_expr.set_variable("x", x_val);

    std::cout << "y = ";
    std::cin >> y_val;
    current_expr.set_variable("y", y_val);

    std::cout << "Установлены переменные для выражения ID " << selected_id <<
        ": x = " << x_val << ", y = " << y_val << std::endl;
}

void calculate_selected_expression(const std::map<int, Expression>& expressions, int selected_id) {
    if (selected_id == 0 || expressions.find(selected_id) == expressions.end()) {
        std::cout << "Сначала выберите или создайте выражение!" << std::endl;
        return;
    }

    const Expression& current_expr = expressions.at(selected_id);
    try {
        double result = current_expr.calculate();
        std::cout << "Результат вычисления для выражения ID " << selected_id << ": " <<
            result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка вычисления для выражения ID " << selected_id << ": " << 
            e.what() << std::endl;
    }
}

void delete_selected_expression(std::map<int, Expression>& expressions, int& selected_id,
    int& next_expression_id) {
    if (selected_id == 0 || expressions.find(selected_id) == expressions.end()) {
        std::cout << "Сначала выберите или создайте выражение!" << std::endl;
        return;
    }

    std::cout << "Удалено выражение ID: " << selected_id << std::endl;

    int deleted_id = selected_id;

    std::map<int, Expression> new_expressions;
    int new_id_counter = 1;

    for (const auto& pair : expressions) {
        if (pair.first == deleted_id) {
            continue;
        }
        new_expressions.emplace(new_id_counter, pair.second);
        new_id_counter++;
    }

    expressions = new_expressions; 
    next_expression_id = new_id_counter;

    if (!expressions.empty()) {
        if (selected_id == deleted_id) {
            selected_id = expressions.begin()->first;
        }
        if (selected_id > next_expression_id - 1) {
            selected_id = next_expression_id - 1;
        }
    } else {
        selected_id = 0;
    }

    std::cout << "Выражения переиндексированы." << std::endl;
}

void select_expression(std::map<int, Expression>& expressions, int& selected_id) {
    if (expressions.empty()) {
        std::cout << "Нет доступных выражений для выбора." << std::endl;
        selected_id = 0;
        return;
    }

    std::cout << "Введите ID выражения для выбора: ";
    int id_to_select;
    std::cin >> id_to_select;

    if (expressions.count(id_to_select)) {
        selected_id = id_to_select;
        std::cout << "Выбрано выражение ID: " << selected_id << std::endl;
    } else {
        std::cout << "Выражение с ID " << id_to_select << " не найдено." << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    int choice = 1;

    std::map<int, Expression> expressions;
    int next_expression_id = 1;
    int selected_expression_id = 0;

    while (choice != 0) {
        print_expression(expressions, selected_expression_id);
        print_menu();
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            create_new_expression(expressions, next_expression_id, selected_expression_id);
            break;
        case 2:
            set_variables_for_expression(expressions, selected_expression_id);
            break;
        case 3:
            calculate_selected_expression(expressions, selected_expression_id);
            break;
        case 4:
            delete_selected_expression(expressions, selected_expression_id, next_expression_id);
            break;
        case 5:
            select_expression(expressions, selected_expression_id);
            break;
        case 0:
            std::cout << "Выход из программы." << std::endl;
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
            break;
        }

        if (choice != 0) {
            system("pause");
            system("cls");
        }
    }
    return 0;
}

#endif