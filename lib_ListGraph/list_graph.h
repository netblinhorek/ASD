#pragma once
#include "../lib_List/list.h"
#include "../lib_TVector/tvector.h"
#include "../lib_PriorityQueue/priority_queue.h"
#include <iostream>
#include <stdexcept>
#include <string>
#define MAX_SIZE 1000000000

template <class T>
struct Edge {
    int to;
    int weight;
    Edge(int t, int w) : to(t), weight(w) {}
};

template <class T>
struct Vertex {
    T data;
    Vertex(T val) : data(val) {}
};

template<class T>
class ListGraph {
public:
    TVector<Vertex<T>*> vertices;
    TVector<List<Edge<T>>> adj;

    ListGraph(TVector<std::pair<std::pair<T, T>, int>> edges, bool is_directed);
    ListGraph(TVector<std::pair<T, T>> edges, bool is_directed);

    ~ListGraph() { clear(); }

    TVector<int> get_dijkstra_path(const T& start_val, const T& end_val);
    int find_index(const T& val) const;
    void add_edge(const T& from, const T& to, int weight);
    void delete_vertex(const T& val);
    void clear() noexcept;
    void print() const noexcept;
    TVector<int> dijkstra(const T& start_val, TVector<int>& parent);

private:
    TVector<T> get_unique_vertices(const TVector<std::pair<T, T>>& edges) const;
    void init_graph(const TVector<T>& unique);
};

template<class T>
TVector<T> ListGraph<T>::get_unique_vertices(const TVector<std::pair<T, T>>& edges) const {
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
void ListGraph<T>::init_graph(const TVector<T>& unique) {
    vertices = TVector<Vertex<T>*>();
    adj = TVector<List<Edge<T>>>();

    for (int i = 0; i < (int)unique.size(); i++) {
        vertices.push_back(new Vertex<T>(unique[i]));
        adj.push_back(List<Edge<T>>());
    }
}

template<class T>
ListGraph<T>::ListGraph(TVector<std::pair<std::pair<T, T>, int>> edges, bool is_directed) {
    TVector<std::pair<T, T>> simple_edges;
    for (int i = 0; i < (int)edges.size(); ++i) {
        simple_edges.push_back(edges[i].first);
    }
    init_graph(get_unique_vertices(simple_edges));
    for (int i = 0; i < (int)edges.size(); i++) {
        add_edge(edges[i].first.first, edges[i].first.second, edges[i].second);
        if (!is_directed)
            add_edge(edges[i].first.second, edges[i].first.first, edges[i].second);
    }
}

template<class T>
ListGraph<T>::ListGraph(TVector<std::pair<T, T>> edges, bool is_directed) {
    init_graph(get_unique_vertices(edges));

    for (int i = 0; i < (int)edges.size(); i++) {
        add_edge(edges[i].first, edges[i].second, 1);
        if (!is_directed)
            add_edge(edges[i].second, edges[i].first, 1);
    }
}

template<class T>
void ListGraph<T>::print() const noexcept {
    for (int i = 0; i < (int)vertices.size(); i++) {
        std::cout << vertices[i]->data << " -> ";
        for (typename List<Edge<T>>::Iterator it = adj[i].begin(); it != adj[i].end(); ++it) {
            std::cout << "[" << vertices[(*it).to]->data << ", w:" << (*it).weight << "] ";
        }
        std::cout << std::endl;
    }
}

template<class T>
void ListGraph<T>::clear() noexcept {
    for (size_t i = 0; i < vertices.size(); i++) {
        delete vertices[i];
    }
    vertices.clear();
    adj.clear();
}

template<class T>
int ListGraph<T>::find_index(const T& val) const {
    for (int i = 0; i < (int)vertices.size(); i++)
        if (vertices[i]->data == val)
            return i;
    return -1;
}

template<class T>
void ListGraph<T>::add_edge(const T& from, const T& to, int weight) {
    int u = find_index(from);
    int v = find_index(to);
    if (u != -1 && v != -1)
        adj[u].push_back(Edge<T>(v, weight));
}

template<class T>
void ListGraph<T>::delete_vertex(const T& val) {
    int idx = find_index(val);
    if (idx == -1) return;

    for (int i = 0; i < (int)adj.size(); i++) {
        typename List<Edge<T>>::Iterator it = adj[i].begin();
        while (it != adj[i].end()) {
            ListNode<Edge<T>>* cur = it.get_node();
            typename List<Edge<T>>::Iterator next_it = it;
            ++next_it;

            if (cur->value.to == idx) {
                adj[i].erase(cur);
            }
            else if (cur->value.to > idx) {
                cur->value.to--;
            }
            it = next_it;
        }
    }
    delete vertices[idx];
    vertices.erase(idx);
    adj.erase(idx);
}

template<class T>
TVector<int> ListGraph<T>::dijkstra(const T& start_val, TVector<int>& parent) {
    int start_idx = find_index(start_val);
    if (start_idx == -1) throw std::logic_error("Vertex not found");

    int n = (int)vertices.size();
    TVector<int> dist;
    TVector<bool> visited;

    for (int i = 0; i < n; i++) {
        dist.push_back(MAX_SIZE);
        visited.push_back(false);
        parent.push_back(-1);
    }

    dist[start_idx] = 0;
    PriorityQueue<int> pq;
    pq.push(start_idx, 0);

    while (!pq.is_empty()) {
        int u = pq.pop();
        if (visited[u]) continue;
        visited[u] = true;

        for (typename List<Edge<T>>::Iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
            int v = (*it).to;
            int weight = (*it).weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push(v, dist[v]);
            }
        }
    }
    return dist;
}

template<class T>
TVector<int> ListGraph<T>::get_dijkstra_path(const T& start_val, const T& end_val) {
    TVector<int> parent;
    dijkstra(start_val, parent);

    int end_idx = find_index(end_val);
    if (end_idx == -1) 
        throw std::logic_error("End vertex not found");

    int start_idx = find_index(start_val);
    TVector<int> path;

    if (parent[end_idx] == -1 && start_idx != end_idx) {
        return path;
    }

    for (int curr = end_idx; curr != -1; curr = parent[curr]) {
        path.push_back(curr);
    }

    TVector<int> reversed_path;
    for (int i = (int)path.size() - 1; i >= 0; i--) {
        reversed_path.push_back(path[i]);
    }

    return reversed_path;
}