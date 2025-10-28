#include "../lib_Matrix/matrix.h"


template <typename T>
void find_smallest_neighbor(const Matrix<T>& matrix, size_t& row,
    size_t& col) {
    T current = matrix[row][col];
    T min_neighbor = current;
    size_t best_row = row, best_col = col;
    size_t n = matrix.rows();

    if (row > 0 && matrix[row - 1][col] < min_neighbor) {
        min_neighbor = matrix[row - 1][col];
        best_row = row - 1;
        best_col = col;
    }
    if (row < n - 1 && matrix[row + 1][col] < min_neighbor) {
        min_neighbor = matrix[row + 1][col];
        best_row = row + 1;
        best_col = col;
    }
    if (col > 0 && matrix[row][col - 1] < min_neighbor) {
        min_neighbor = matrix[row][col - 1];
        best_row = row;
        best_col = col - 1;
    }
    if (col < n - 1 && matrix[row][col + 1] < min_neighbor) {
        min_neighbor = matrix[row][col + 1];
        best_row = row;
        best_col = col + 1;
    }

    row = best_row;
    col = best_col;
}

template <typename T>
bool is_local_minimum(const Matrix<T>& matrix, size_t row,
    size_t col) {
    T current = matrix[row][col];
    size_t n = matrix.rows();

    if (row > 0 && matrix[row - 1][col] <= current)
        return false;
    if (row < n - 1 && matrix[row + 1][col] <= current)
        return false;
    if (col > 0 && matrix[row][col - 1] <= current)
        return false;
    if (col < n - 1 && matrix[row][col + 1] <= current)
        return false;

    return true;
}

template <typename T>
bool find_local_minimum(const Matrix<T>& matrix, size_t& row,
    size_t& col) {
    size_t n = matrix.rows();
    if (n == 0) return false;

    row = rand() % n;
    col = rand() % n;

    size_t max_steps = n * 3;
    size_t steps = 0;

    while (steps < max_steps) {
        if (is_local_minimum(matrix, row, col)) {
            return true;
        }

        size_t old_row = row, old_col = col;
        find_smallest_neighbor(matrix, row, col);

        if (row == old_row && col == old_col) {
            break;
        }

        steps++;
    }

    return false;
}
