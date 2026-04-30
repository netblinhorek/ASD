#pragma once
#include "../lib_Dijkstra_algorithm/Dijkstra_algorithm.h"
#include "../lib_PriorityQueue/priority_queue.h"
#include "../lib_ListGraph/list_graph.h"
const long long INF = 1e18;

template<class T>
TVector<int> dijkstra(const T& start_val) {
	int start_idx = find_index(start_val);
	if (start_index == -1)
		throw std::logic_error("Vertex not found");
	int n = (int)vertices.size();
	TVector<int> dist(n);
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
    }
    dist[start_idx] = 0;

    PriorityQueue<int> pq;
    pq.push(start_idx, 0);

    while (!pq.is_empty()) {
        int u = pq.pop(); 

        for (typename List<Edge<T>>::Iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
            Edge<T>& edge = *it;
            int v = edge.to;
            int weight = edge.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push(v, dist[v]);
            }
        }
    }
    return dist;
}
