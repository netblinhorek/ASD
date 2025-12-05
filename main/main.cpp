#include <iostream>
#include <string>
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

#endif EASY_EXAMPLE

#ifdef ARITHMETIC_EXPRESSION_CALCULATOR

#include "../lib_Expression/expression.h"
#include "../lib_Lexem/lexem.h"
#include "../lib_Parser/parser.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <locale>

void print_expression(const std::map<int, Expression>& expressions, 
    const std::map<int, std::map<std::string, double>>& variable_values, int selected_id) {
    std::cout << " + —————————————————————————————————————————————"
        "————————————————————————————————— +" << std::endl;
    std::cout << " | ID | ÂÛÐÀÆÅÍÈÅ  | ÇÍÀ×ÅÍÈß ÏÅÐÅÌÅÍÍÛÕ |" << std::endl;
    std::cout << " +———————————————————————————————————————————————"
        "———————————————————————————————— +" << std::endl;

    if (expressions.empty()) {
        std::cout << " |   |   |" << std::endl;
    }
    else {
        for (const auto& pair : expressions) {
            int id = pair.first;
            const Expression& expr_data = pair.second;
            std::cout << " | " << id << " | ";
            std::cout << expr_data.get_infix() << " | ";

            bool first_var = true;
            auto vars_it = variable_values.find(id);
            if (vars_it != variable_values.end()) {
                for (const auto& var_pair : vars_it->second) {
                    if (!first_var) std::cout << ", ";
                    std::cout << var_pair.first << " = " << var_pair.second;
                    first_var = false;
                }
            }
            std::cout << " |" << std::endl;
        }
    }

    std::cout << " +——————————————————————————————————————————————"
        "————————————————————————————————— +" << std::endl;
    if (selected_id != 0) {
        std::cout << "Òåêóùåå âûáðàííîå âûðàæåíèå: ID " << selected_id << std::endl;
    }
}

void print_menu() {
    std::cout << "1. Ñîçäàòü íîâîå âûðàæåíèå" << std::endl;
    std::cout << "2. Çàäàòü çíà÷åíèÿ ïåðåìåííûõ äëÿ âûðàæåíèÿ" << std::endl;
    std::cout << "3. Âû÷èñëèòü âûáðàííîå âûðàæåíèå" << std::endl;
    std::cout << "4. Óäàëèòü âûáðàííîå âûðàæåíèå" << std::endl;
    std::cout << "5. Âûáðàòü âûðàæåíèå" << std::endl;
    std::cout << "0. Âûõîä" << std::endl;
}

void create_new_expression(std::map<int, Expression>& expressions, 
    std::map<int, std::map<std::string, double>>& variable_values, int& next_id,
    int& selected_id) {
    std::cout << "Ââåäèòå âûðàæåíèå: ";
    std::string expr_string;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, expr_string);

    try {
        expressions.emplace(next_id, Expression(expr_string));
        variable_values[next_id] = std::map<std::string, double>();
        selected_id = next_id;
        std::cout << "Ñîçäàíî âûðàæåíèå ID: " << next_id
            << ", âûðàæåíèå: '" << expr_string << "'" << std::endl;
        next_id++;
    }
    catch (const std::exception& e) {
        std::cout << "Îøèáêà ïðè ñîçäàíèè âûðàæåíèÿ: " << e.what() << std::endl;
    }
}

void set_variables_for_expression(std::map<int, Expression>& expressions,
    std::map<int, std::map<std::string, double>>& variable_values, int selected_id) {
    if (selected_id == 0 || expressions.find(selected_id) == expressions.end()) {
        std::cout << "Ñíà÷àëà âûáåðèòå âûðàæåíèå!" << std::endl;
        return;
    }

    Expression& expr_data = expressions.at(selected_id);
    List<std::string> operands = expr_data.get_operands();

    if (operands.is_empty()) {
        std::cout << "Â âûðàæåíèè íåò ïåðåìåííûõ." << std::endl;
        return;
    }

    std::cout << "Ââåäèòå çíà÷åíèÿ ïåðåìåííûõ äëÿ âûðàæåíèÿ ID " << selected_id << ":" << std::endl;

    std::vector<std::string> var_names;
    auto it = operands.begin();
    while (it != operands.end()) {
        var_names.push_back(*it);
        ++it;
    }

    for (const auto& var_name : var_names) {
        double val;
        std::cout << var_name << " = ";
        std::cin >> val;
        variable_values[selected_id][var_name] = val;
    }

    std::cout << "Óñòàíîâëåíû çíà÷åíèÿ äëÿ âûðàæåíèÿ ID " << selected_id << ":" << std::endl;
    for (const auto& var_pair : variable_values[selected_id]) {
        std::cout << "  " << var_pair.first << " = " << var_pair.second << std::endl;
    }
}

void calculate_selected_expression(const std::map<int, Expression>& expressions, 
    const std::map<int, std::map<std::string, double>>& variable_values, int selected_id) {
    if (selected_id == 0 || expressions.find(selected_id) == expressions.end()) {
        std::cout << "Ñíà÷àëà âûáåðèòå âûðàæåíèå!" << std::endl;
        return;
    }

    const Expression& expr_data = expressions.at(selected_id);
    try {
        auto vars_it = variable_values.find(selected_id);
        std::map<std::string, double> values = (vars_it != variable_values.end()) ? vars_it->second : std::map<std::string, double>();
        double result = expr_data.calculate(values);
        std::cout << "Ðåçóëüòàò âû÷èñëåíèÿ âûðàæåíèÿ ID " << selected_id << ": " <<
            result << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Îøèáêà âû÷èñëåíèÿ âûðàæåíèÿ ID " << selected_id << ": " <<
            e.what() << std::endl;
    }
}

void delete_selected_expression(std::map<int, Expression>& expressions, 
    std::map<int, std::map<std::string, double>>& variable_values, int& selected_id,
    int& next_expression_id) {
    if (selected_id == 0 || expressions.find(selected_id) == expressions.end()) {
        std::cout << "Ñíà÷àëà âûáåðèòå âûðàæåíèå!" << std::endl;
        return;
    }

    std::cout << "Óäàëåíî âûðàæåíèå ID: " << selected_id << std::endl;

    int deleted_id = selected_id;

    std::map<int, Expression> new_expressions;
    std::map<int, std::map<std::string, double>> new_variable_values;
    int new_id_counter = 1;

    for (const auto& pair : expressions) {
        if (pair.first == deleted_id) {
            continue;
        }
        new_expressions.emplace(new_id_counter, pair.second);
        auto vars_it = variable_values.find(pair.first);
        if (vars_it != variable_values.end()) {
            new_variable_values[new_id_counter] = vars_it->second;
        }
        new_id_counter++;
    }

    expressions = new_expressions;
    variable_values = new_variable_values;
    next_expression_id = new_id_counter;

    if (!expressions.empty()) {
        if (selected_id == deleted_id) {
            selected_id = expressions.begin()->first;
        }
        if (selected_id > next_expression_id - 1) {
            selected_id = next_expression_id - 1;
        }
    }
    else {
        selected_id = 0;
    }

    std::cout << "Âûðàæåíèå óäàëåíî óñïåøíî." << std::endl;
}

void select_expression(std::map<int, Expression>& expressions, int& selected_id) {
    if (expressions.empty()) {
        std::cout << "Íåò ñîõðàíåííûõ âûðàæåíèé äëÿ âûáîðà." << std::endl;
        selected_id = 0;
        return;
    }

    std::cout << "Ââåäèòå ID âûðàæåíèÿ äëÿ âûáîðà: ";
    int id_to_select;
    std::cin >> id_to_select;

    if (expressions.count(id_to_select)) {
        selected_id = id_to_select;
        std::cout << "Âûáðàíî âûðàæåíèå ID: " << selected_id << std::endl;
    }
    else {
        std::cout << "Âûðàæåíèå ñ ID " << id_to_select << " íå íàéäåíî." << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    int choice = 1;

    std::map<int, Expression> expressions;
    std::map<int, std::map<std::string, double>> variable_values;
    int next_expression_id = 1;
    int selected_expression_id = 0;

    while (choice != 0) {
        print_expression(expressions, variable_values, selected_expression_id);
        print_menu();
        std::cout << "Âàø âûáîð: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            create_new_expression(expressions, variable_values, next_expression_id, selected_expression_id);
            break;
        case 2:
            set_variables_for_expression(expressions, variable_values, selected_expression_id);
            break;
        case 3:
            calculate_selected_expression(expressions, variable_values, selected_expression_id);
            break;
        case 4:
            delete_selected_expression(expressions, variable_values, selected_expression_id, next_expression_id);
            break;
        case 5:
            select_expression(expressions, selected_expression_id);
            break;
        case 0:
            std::cout << "Âûõîä èç ïðîãðàììû." << std::endl;
            break;
        default:
            std::cout << "Íåâåðíûé âûáîð. Ïîâòîðèòå ââîä." << std::endl;
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