// Copyright 2024 Marina Usova

#include <iostream>
#include <string>
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


void print_expression(int id, std::string expression, int x, int y) {
    std::cout << " + —————————————————————————————————————————————"
        "————————————————————————————————— +" << std::endl;
    std::cout << " | ID | EXPRESSION | VARIABLES VALUES |" << std::endl;
    std::cout << " +———————————————————————————————————————————————"
        "———————————————————————————————— +" << std::endl;
    if (id > 0) {
        for (int i = 1; i < id; i++) {
            std::cout << "   |" << id << " | " << expression <<
                " | x = " << x << ", y = " << y << "       |";
        }
    }
    std::cout << " +——————————————————————————————————————————————"
        "————————————————————————————————— +" << std::endl;
}

void print_selection_from_the_menu() {
    std::cout << "1. Ñîçäàòü íîâîå âûðàæåíèå" << std::endl;
    std::cout << "2. Çàäàòü ïåðåìåííûå" << std::endl;
    std::cout << "3. Âû÷èñëèòü çíà÷åíèå âûðàæåíèÿ" << std::endl;
    std::cout << "4. Óäàëèòü âûðàæåíèå" << std::endl;
    std::cout << "0. Âûéòè" << std::endl;
}

void create_new_expression(int id, std::string expression) {
    std::cout << "Çàãëóøêà - ñîçäàíèå âûðàæåíèÿ ID: " << id <<
        ", âûðàæåíèå: " << expression << std::endl;
}

void set_variables(int& x, int& y) {
    std::cout << "Ââåäèòå çíà÷åíèÿ ïåðåìåííûõ:" << std::endl;
    std::cout << "x = ";
    std::cin >> x;
    std::cout << "y = ";
    std::cin >> y;
    std::cout << "Óñòàíîâëåíû ïåðåìåííûå: x = " << x << ", y = " << y << std::endl;
}

void calculate_the_value_of_the_expression(std::string expression, int x, int y) {
    std::cout << "Çàãëóøêà - âû÷èñëåíèå âûðàæåíèÿ: " << expression <<
        " ñ x=" << x << ", y=" << y << std::endl;
}

void delete_expression(int id, std::string expression) {
    std::cout << "Çàãëóøêà - óäàëåíèå âûðàæåíèÿ ID: " << id << ", âûðàæåíèå: " <<
        expression << std::endl;
}

void print_variables(int id, std::string variable, int x, int y) {
    std::cout << "Ïåðåìåííûå äëÿ ID " << id << " (" << variable << "): x=" 
        << x << ", y=" << y << std::endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    int selection_in_the_menu = 1;

    int id = 1;
    std::string expression = "x + y";
    int x = 0;
    int y = 0;

    while (selection_in_the_menu != 0) {
        print_selection_from_the_menu();
        std::cout << "Âàø âûáîð: ";
        std::cin >> selection_in_the_menu;

        switch (selection_in_the_menu) {
        case 1:
            create_new_expression(id, expression);
            break;
        case 2:
            set_variables(x, y);
            break;
        case 3:
            calculate_the_value_of_the_expression(expression, x, y);
            break;
        case 4:
            delete_expression(id, expression);
            break;
        case 0:
            std::cout << "Âûõîä èç ïðîãðàììû." << std::endl;
            break;
        default:
            std::cout << "Íåâåðíûé âûáîð. Ïîïðîáóéòå ñíîâà." << std::endl;
            break;
        }
        print_expression(id, expression, x, y);
        system("pause");
        system("cls");
    }
    return 0;
}

#endif
