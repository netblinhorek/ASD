#include <clocale>
#include <iostream>

void run_unsorted_experiments();
void run_sorted_experiments();

int main() {
    setlocale(LC_ALL, "Russian");
    run_unsorted_experiments();
    run_sorted_experiments();
    return 0;
}
