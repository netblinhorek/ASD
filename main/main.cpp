// Copyright 2024 Marina Usova

//#define EASY_EXAMPLE
#define LABIRINT
#include <iostream>

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


#endif
#ifdef LABIRINT
#include <iostream>
#include <ctime>
#include <algorithm>
#include "../lib_Matrix/matrix.h"
#include "../lib_TVector/tvector.h"
#include "../lib_DSU/DSU.h"
#include "../lib_ListGraph/list_graph.h"


bool are_connected(size_t N, size_t M,
    const Matrix<bool>& right,
    const Matrix<bool>& down,
    size_t X, size_t Y)
{
    DSU dsu(N * M);

    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < M; ++j) {
            if (j + 1 < M && !right[i][j])
                dsu.union_set(i * M + j, i * M + j + 1);
            if (i + 1 < N && !down[i][j])
                dsu.union_set(i * M + j, i * M + M + j);
        }

    return dsu.find(X - 1) == dsu.find(N * M - M + Y - 1);
}

void shuffle_walls(Matrix<bool>& right, Matrix<bool>& down) {
    TVector<bool> walls;

    for (size_t i = 0; i < right.rows(); ++i)
        for (size_t j = 0; j < right.cols(); ++j)
            walls.push_back(right[i][j]);

    for (size_t i = 0; i < down.rows(); ++i)
        for (size_t j = 0; j < down.cols(); ++j)
            walls.push_back(down[i][j]);

    for (size_t i = walls.size() - 1; i > 0; --i) {
        size_t j = rand() % (i + 1);
        bool tmp = walls[i];
        walls[i] = walls[j];
        walls[j] = tmp;
    }

    size_t idx = 0;
    for (size_t i = 0; i < right.rows(); ++i)
        for (size_t j = 0; j < right.cols(); ++j)
            right[i][j] = walls[idx++];

    for (size_t i = 0; i < down.rows(); ++i)
        for (size_t j = 0; j < down.cols(); ++j)
            down[i][j] = walls[idx++];
}
void print_lab_with_path(size_t N, size_t M, size_t X, size_t Y,
    const Matrix<bool>& right, const Matrix<bool>& down,
    const TVector<int>& path_in_graph_indices, const ListGraph<int>& graph)
{
    TVector<int> real_cell_indices;
    for (size_t i = 0; i < path_in_graph_indices.size(); ++i) {
        real_cell_indices.push_back(graph.vertices[path_in_graph_indices[i]]->data);
    }

    std::cout << "    +";
    for (size_t j = 0; j < M; ++j) {
        if (j == X - 1) std::cout << "   +";
        else std::cout << "---+";
    }
    std::cout << "\n";

    for (size_t i = 0; i < N; ++i) {
        std::cout << "    |";
        for (size_t j = 0; j < M; ++j) {
            int curr_cell = (i * M + j);
            bool is_path = false;
            for (size_t p = 0; p < real_cell_indices.size(); ++p) {
                if (real_cell_indices[p] == curr_cell) {
                    is_path = true;
                    break;
                }
            }

            if (is_path) std::cout << " * ";
            else std::cout << "   ";

            if (j < M - 1) {
                if (right[i][j]) std::cout << "|";
                else std::cout << " ";
            }
        }
        std::cout << "|\n";

        if (i < N - 1) {
            std::cout << "    +";
            for (size_t j = 0; j < M; ++j) {
                if (down[i][j]) std::cout << "---+";
                else std::cout << "   +";
            }
            std::cout << "\n";
        }
    }

    std::cout << "    +";
    for (size_t j = 0; j < M; ++j) {
        if (j == Y - 1) std::cout << "   +";
        else std::cout << "---+";
    }
    std::cout << "\n";
}
void print_lab(size_t N, size_t M, size_t X, size_t Y, const Matrix<bool>& right, const Matrix<bool>& down) {
    TVector<int> empty_path;
    TVector<std::pair<std::pair<int, int>, int>> empty_edges;
    ListGraph<int> temp_graph(empty_edges, false);
    print_lab_with_path(N, M, X, Y, right, down, empty_path, temp_graph);
}
void generate(size_t N, size_t M, size_t X, size_t Y) {

    Matrix<bool> right(N, M - 1, true);
    Matrix<bool> down(N - 1, M, true);

    for (size_t i = 0; i < right.rows(); ++i)
        for (size_t j = 0; j < right.cols(); ++j)
            if (rand() % 2 == 0)
                right[i][j] = false;

    for (size_t i = 0; i < down.rows(); ++i)
        for (size_t j = 0; j < down.cols(); ++j)
            if (rand() % 2 == 0)
                down[i][j] = false;

    while (!are_connected(N, M, right, down, X, Y)) {
        shuffle_walls(right, down);
    }

    TVector<std::pair<std::pair<int, int>, int>> edges;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            int u = i * M + j;

            if (j + 1 < M && !right[i][j]) {
                int v = i * M + (j + 1);
                edges.push_back(std::make_pair(std::make_pair(u, v), 1));
            }
            if (i + 1 < N && !down[i][j]) {
                int v = (i + 1) * M + j;
                edges.push_back(std::make_pair(std::make_pair(u, v), 1));
            }
        }
    }

    ListGraph<int> graph(edges, false);
    int start_val = (0 * M + (X - 1));
    int end_val = ((N - 1) * M + (Y - 1));

    TVector<int> path = graph.get_dijkstra_path(start_val, end_val);

    print_lab_with_path(N, M, X, Y, right, down, path, graph);
}


void user_input(size_t& M, size_t& N, size_t& X, size_t& Y) {
    std::cout << "Columns M and rows N: ";
    std::cin >> M >> N;
    if (M == 0 || N == 0)
        throw std::logic_error("M and N must be > 0");

    std::cout << "Start column X and end column Y (1.." << M << "): ";
    std::cin >> X >> Y;
    if (X < 1 || X > M || Y < 1 || Y > M)
        throw std::logic_error("X or Y out of bounds");
}

int main() {
    size_t M, N, X, Y;
    setlocale(LC_ALL, "ru");

    user_input(M, N, X, Y);
    generate(N, M, X, Y);


    return 0;
}
#endif