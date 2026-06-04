#include <clocale>
#include <iostream>
#include <stdexcept>

void run_unsorted_experiments();
void run_sorted_experiments();

int main() {
    setlocale(LC_ALL, "Russian");
    try {
        run_unsorted_experiments();
        run_sorted_experiments();
    }
    catch (const std::exception& ex) {
        std::cerr << "TableExperiments failed: " << ex.what() << '\n';
        return 1;
    }
    return 0;
}
