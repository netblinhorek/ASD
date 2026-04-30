#include <gtest/gtest.h>
#include "../lib_ListGraph/list_graph.h"


TEST(ListGraphTest, construction_and_print) {
    TVector<std::pair<std::pair<int, int>, int>> edges;
    edges.push_back({ {1, 2}, 10 });
    edges.push_back({ {2, 3}, 20 });

    ListGraph<int> graph(edges, false); 

    EXPECT_EQ(graph.vertices.size(), 3);
    EXPECT_EQ(graph.find_index(1), 0);
    EXPECT_EQ(graph.find_index(3), 2);
    graph.print();
}

TEST(ListGraphTest, delete_vertex) {
    TVector<std::pair<std::pair<int, int>, int>> edges;
    edges.push_back({ {1, 2}, 10 });
    edges.push_back({ {2, 3}, 20 });
    edges.push_back({ {1, 3}, 5 });

    ListGraph<int> graph(edges, true); 

    graph.delete_vertex(2);

    EXPECT_EQ(graph.vertices.size(), 2);

    int idx_1 = graph.find_index(1);
    bool found_3 = false;
    for (auto it = graph.adj[idx_1].begin(); it != graph.adj[idx_1].end(); ++it) {
        if ((*it).to == 1) found_3 = true; 
    }
    EXPECT_TRUE(found_3);
}

TEST(ListGraphTest, unweighted_graph) {
    TVector<std::pair<int, int>> edges;
    edges.push_back({ 10, 20 });

    ListGraph<int> graph(edges, true);

    int u = graph.find_index(10);
    int v = graph.find_index(20);

    bool found = false;
    for (auto it = graph.adj[u].begin(); it != graph.adj[u].end(); ++it) {
        if ((*it).to == v && (*it).weight == 1) found = true;
    }
    EXPECT_TRUE(found);
    graph.print();
}

TEST(ListGraphTest, undirected_weighted_graph) {
    
    TVector<std::pair<std::pair<char, char>, int>> edges;
    edges.push_back({ {'A', 'B'}, 2 });
    edges.push_back({ {'B', 'C'}, 3 });
    edges.push_back({ {'A', 'C'}, 4 });

    ListGraph<char> graph(edges, false);

    EXPECT_EQ(graph.vertices.size(), 3);

    int idxA = graph.find_index('A');
    int idxB = graph.find_index('B');
    int idxC = graph.find_index('C');


    bool found_AB = false;
    for (auto it = graph.adj[idxA].begin(); it != graph.adj[idxA].end(); ++it) {
        if ((*it).to == idxB && (*it).weight == 2) {
            found_AB = true;
            break;
        }
    }
    EXPECT_TRUE(found_AB) << "Edge A->B with weight 2 not found";


    bool found_BA = false;
    for (auto it = graph.adj[idxB].begin(); it != graph.adj[idxB].end(); ++it) {
        if ((*it).to == idxA && (*it).weight == 2) { 
            found_BA = true;
            break;
        }
    }
    EXPECT_TRUE(found_BA);

    bool found_BC = false;
    for (auto it = graph.adj[idxB].begin(); it != graph.adj[idxB].end(); ++it) {
        if ((*it).to == idxC && (*it).weight == 3) { 
            found_BC = true;
            break;
        }
    }
    EXPECT_TRUE(found_BC);

    bool found_CB = false;
    for (auto it = graph.adj[idxC].begin(); it != graph.adj[idxC].end(); ++it) {
        if ((*it).to == idxB && (*it).weight == 3) { 
            found_CB = true;
            break;
        }
    }
    EXPECT_TRUE(found_CB) ;
}

TEST(ListGraphTest, directed_weighted_graph) {
    TVector<std::pair<std::pair<char, char>, int>> edges;
    edges.push_back({ {'A', 'B'}, 2 });
    edges.push_back({ {'B', 'C'}, 3 });
    edges.push_back({ {'C', 'A'}, 4 });
    edges.push_back({ {'A', 'C'}, 10 });

    ListGraph<char> graph(edges, true);

    EXPECT_EQ(graph.vertices.size(), 3);

    int idxA = graph.find_index('A');
    int idxB = graph.find_index('B');
    int idxC = graph.find_index('C');

    auto check_edge = [&](int from_idx, int to_idx, int expected_weight) {
        for (auto it = graph.adj[from_idx].begin(); it != graph.adj[from_idx].end(); ++it) {
            if ((*it).to == to_idx && (*it).weight == expected_weight) return true;
        }
        return false;
        };

    EXPECT_TRUE(check_edge(idxA, idxB, 2));
    EXPECT_TRUE(check_edge(idxB, idxC, 3));
    EXPECT_TRUE(check_edge(idxC, idxA, 4));
    EXPECT_TRUE(check_edge(idxA, idxC, 10));

    bool found_BtoA = false;
    for (auto it = graph.adj[idxB].begin(); it != graph.adj[idxB].end(); ++it) {
        if ((*it).to == idxA) { 
            found_BtoA = true;
            break;
        }
    }
    EXPECT_FALSE(found_BtoA);

    bool found_CtoB = false;
    for (auto it = graph.adj[idxC].begin(); it != graph.adj[idxC].end(); ++it) {
        if ((*it).to == idxB) { 
            found_CtoB = true;
            break;
        }
    }
    EXPECT_FALSE(found_CtoB);
}

TEST(ListGraphTest, dijkstra_on_unweighted_graph) {
    TVector<std::pair<char, char>> edges;
    edges.push_back({ 'A', 'B' });
    edges.push_back({ 'B', 'C' });
    edges.push_back({ 'C', 'D' });
    edges.push_back({ 'A', 'D' });

    ListGraph<char> graph(edges, false);
    TVector<int> dist = graph.dijkstra('A');

    int idxA = graph.find_index('A');
    int idxB = graph.find_index('B');
    int idxC = graph.find_index('C');
    int idxD = graph.find_index('D');

    EXPECT_EQ(dist[idxA], 0);
    EXPECT_EQ(dist[idxB], 1);   
    EXPECT_EQ(dist[idxC], 2);   
    EXPECT_EQ(dist[idxD], 1);   
}

TEST(ListGraphTest, on_directed_unweighted_graph) {
    TVector<std::pair<char, char>> edges;
    edges.push_back({ 'A', 'B' });
    edges.push_back({ 'B', 'C' });
    edges.push_back({ 'A', 'C' });

    ListGraph<char> graph(edges, true);
    TVector<int> dist = graph.dijkstra('A');

    EXPECT_EQ(dist[graph.find_index('A')], 0);
    EXPECT_EQ(dist[graph.find_index('B')], 1);   
    EXPECT_EQ(dist[graph.find_index('C')], 1);   
}
TEST(DijkstraTest, UndirectedGraph_Triangle) {
    TVector<std::pair<std::pair<char, char>, int>> edges;
    edges.push_back({ {'A', 'B'}, 3 });
    edges.push_back({ {'B', 'C'}, 4 });
    edges.push_back({ {'A', 'C'}, 5 });

    ListGraph<char> graph(edges, false);
    TVector<int> dist = graph.dijkstra('A');

    EXPECT_EQ(dist[graph.find_index('A')], 0);
    EXPECT_EQ(dist[graph.find_index('B')], 3);
    EXPECT_EQ(dist[graph.find_index('C')], 5);
}

TEST(DijkstraTest, undirected_graph_complete_graph) {
    TVector<std::pair<std::pair<char, char>, int>> edges;
    edges.push_back({ {'A', 'B'}, 2 });
    edges.push_back({ {'A', 'C'}, 4 });
    edges.push_back({ {'A', 'D'}, 1 });
    edges.push_back({ {'B', 'C'}, 1 });
    edges.push_back({ {'B', 'D'}, 5 });
    edges.push_back({ {'C', 'D'}, 3 });

    ListGraph<char> graph(edges, false);
    TVector<int> dist = graph.dijkstra('A');

    EXPECT_EQ(dist[graph.find_index('A')], 0);
    EXPECT_EQ(dist[graph.find_index('B')], 2);
    EXPECT_EQ(dist[graph.find_index('C')], 3);
    EXPECT_EQ(dist[graph.find_index('D')], 1);
}


TEST(DijkstraTest, integer_vertices) {
    TVector<std::pair<std::pair<int, int>, int>> edges;
    edges.push_back({ {1, 2}, 10 });
    edges.push_back({ {1, 3}, 5 });
    edges.push_back({ {2, 4}, 2 });
    edges.push_back({ {3, 2}, 3 });
    edges.push_back({ {3, 4}, 8 });

    ListGraph<int> graph(edges, true);
    TVector<int> dist = graph.dijkstra(1);

    EXPECT_EQ(dist[graph.find_index(1)], 0);
    EXPECT_EQ(dist[graph.find_index(2)], 8);
    EXPECT_EQ(dist[graph.find_index(3)], 5);
    EXPECT_EQ(dist[graph.find_index(4)], 10);
}


TEST(DijkstraTest, zero_weight_edges) {
    TVector<std::pair<std::pair<char, char>, int>> edges;
    edges.push_back({ {'A', 'B'}, 0 });
    edges.push_back({ {'B', 'C'}, 0 });
    edges.push_back({ {'A', 'C'}, 5 });

    ListGraph<char> graph(edges, true);
    TVector<int> dist = graph.dijkstra('A');

    EXPECT_EQ(dist[graph.find_index('A')], 0);
    EXPECT_EQ(dist[graph.find_index('B')], 0);
    EXPECT_EQ(dist[graph.find_index('C')], 0);
}