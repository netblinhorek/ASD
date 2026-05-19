#pragma once
#include "../lib_List/list.h"
#include "../lib_TVector/tvector.h"
#include "../lib_PriorityQueue/priority_queue.h"
#include "../lib_Matrix/matrix.h"
#include <iostream>
#include <iomanip> 
#include <stdexcept>
#include <string>
#define MAX_SIZE 1000000000

template <class T>
struct Vertex {
    T data;
    Vertex(T val) : data(val) {}
};

template<class T>
class AdjacencyMatrix {
public:
    TVector<Vertex<T>*> vertices;
    Matrix<int> adj;
    bool is_directed;  

    AdjacencyMatrix(TVector<std::pair<std::pair<T, T>, int>> edges, bool is_directed);
    AdjacencyMatrix(TVector<std::pair<T, T>> edges, bool is_directed);

    ~AdjacencyMatrix() { clear(); }

    int find_index(const T& val) const;
    void add_edge(const T& from, const T& to, int weight);
    void delete_vertex(const T& val);
    void clear() noexcept;
    void print() const noexcept;

private:
    TVector<T> get_unique_vertices(const TVector<std::pair<T, T>>& edges) const;
    void init_graph(const TVector<T>& unique);
};

template<class T>
TVector<T> AdjacencyMatrix<T>::get_unique_vertices(const TVector<std::pair<T, T>>& edges) const {
    TVector<T> unique;
    for (int i = 0; i < (int)edges.size(); i++) {
        T vals[2];
        vals[0] = edges[i].first;
        vals[1] = edges[i].second;
        for (int k = 0; k < 2; k++) {
            T val = vals[k];
            bool found = false;
            for (int j = 0; j < (int)unique.size(); j++) {
                if (unique[j] == val) { found = true; break; }
            }
            if (!found) unique.push_back(val);
        }
    }
    return unique;
}

template<class T>
void AdjacencyMatrix<T>::init_graph(const TVector<T>& unique) {
    int n = (int)unique.size();
    adj = Matrix<int>(n, n);

    for (int i = 0; i < n; i++) {
        vertices.push_back(new Vertex<T>(unique[i]));
        for (int j = 0; j < n; j++) {
            if (i == j) {
                adj[i][j] = 0;
            }
            else {
                adj[i][j] = MAX_SIZE;
            }
        }
    }
}

template<class T>
AdjacencyMatrix<T>::AdjacencyMatrix(TVector<std::pair<std::pair<T, T>, int>> edges, bool is_directed)
    : is_directed(is_directed) {
    TVector<std::pair<T, T>> simple_edges;
    for (int i = 0; i < (int)edges.size(); ++i) {
        simple_edges.push_back(edges[i].first);
    }
    init_graph(get_unique_vertices(simple_edges));

    for (int i = 0; i < (int)edges.size(); i++) {
        add_edge(edges[i].first.first, edges[i].first.second, edges[i].second);
    }
}

template<class T>
AdjacencyMatrix<T>::AdjacencyMatrix(TVector<std::pair<T, T>> edges, bool is_directed)
    : is_directed(is_directed) {  
    init_graph(get_unique_vertices(edges));

    for (int i = 0; i < (int)edges.size(); i++) {
        add_edge(edges[i].first, edges[i].second, 1);
    }
}

template<class T>
void AdjacencyMatrix<T>::print() const noexcept {
    int n = (int)vertices.size();
    const int width = 5;

    std::cout << std::setw(width + 2) << " ";
    for (int i = 0; i < n; i++) {
        std::cout << std::setw(width) << vertices[i]->data;
    }
    std::cout << "\n";
    std::cout << std::setw(width + 1) << " " <<
        std::string(n * width, '-') << "\n";

    for (int i = 0; i < n; i++) {
        std::cout << std::setw(width) << vertices[i]->data << " |";

        for (int j = 0; j < n; j++) {
            if (adj[i][j] == MAX_SIZE) {
                std::cout << std::setw(width) << "0";
            }
            else {
                std::cout << std::setw(width) << adj[i][j];
            }
        }
        std::cout << "\n";
    }
}

template<class T>
void AdjacencyMatrix<T>::clear() noexcept {
    for (size_t i = 0; i < vertices.size(); i++) {
        delete vertices[i];
    }
    vertices.clear();
    adj.clear();
}

template<class T>
int AdjacencyMatrix<T>::find_index(const T& val) const {
    for (int i = 0; i < (int)vertices.size(); i++)
        if (vertices[i]->data == val)
            return i;
    return -1;
}

template<class T>
void AdjacencyMatrix<T>::add_edge(const T& from, const T& to, int weight) {
    int u = find_index(from);
    int v = find_index(to);
    if (u != -1 && v != -1) {
        adj[u][v] = weight;
        if (!is_directed) {
            adj[v][u] = weight;
        }
    }
}

template<class T>
void AdjacencyMatrix<T>::delete_vertex(const T& val) {
    int idx = find_index(val);
    if (idx == -1) return;

    delete vertices[idx];
    vertices.erase(idx);
    adj.erase_row(idx);
    adj.erase_col(idx);
}