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
        if ((*it).to == graph.find_index(3)) found_3 = true;
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
    EXPECT_TRUE(found_AB);

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
    EXPECT_TRUE(found_CB);
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

TEST(ListGraphTest, dijkstra_path_simple_path) {
    TVector<std::pair<char, char>> edges;
    edges.push_back({ 'A', 'B' });
    edges.push_back({ 'B', 'C' });
    edges.push_back({ 'C', 'D' });

    ListGraph<char> graph(edges, false);
    TVector<int> path = graph.get_dijkstra_path('A', 'D');

    EXPECT_EQ(path.size(), 4);

    EXPECT_EQ(path[0], graph.find_index('A'));
    EXPECT_EQ(path[1], graph.find_index('B'));
    EXPECT_EQ(path[2], graph.find_index('C'));
    EXPECT_EQ(path[3], graph.find_index('D'));
}

TEST(ListGraphTest, dijkstra_path_with_alternative_routes) {
    TVector<std::pair<char, char>> edges;
    edges.push_back({ 'A', 'B' });
    edges.push_back({ 'B', 'D' });
    edges.push_back({ 'A', 'C' });
    edges.push_back({ 'C', 'D' });

    ListGraph<char> graph(edges, false);
    TVector<int> path = graph.get_dijkstra_path('A', 'D');

    EXPECT_EQ(path.size(), 3);
    EXPECT_EQ(path[0], graph.find_index('A'));
    EXPECT_EQ(path[path.size() - 1], graph.find_index('D'));
}

TEST(ListGraphTest, dijkstra_path_weighted_graph) {
    TVector<std::pair<std::pair<char, char>, int>> edges;
    edges.push_back({ {'A', 'B'}, 1 });
    edges.push_back({ {'B', 'D'}, 5 });
    edges.push_back({ {'A', 'C'}, 2 });
    edges.push_back({ {'C', 'D'}, 1 });

    ListGraph<char> graph(edges, false);
    TVector<int> path = graph.get_dijkstra_path('A', 'D');

    EXPECT_EQ(path.size(), 3);
    EXPECT_EQ(path[0], graph.find_index('A'));
    EXPECT_EQ(path[1], graph.find_index('C'));
    EXPECT_EQ(path[2], graph.find_index('D'));
}

TEST(ListGraphTest, dijkstra_path_same_vertex) {
    TVector<std::pair<char, char>> edges;
    edges.push_back({ 'A', 'B' });

    ListGraph<char> graph(edges, false);
    TVector<int> path = graph.get_dijkstra_path('A', 'A');

    EXPECT_EQ(path.size(), 1);
    EXPECT_EQ(path[0], graph.find_index('A'));
}

TEST(ListGraphTest, dijkstra_path_no_path) {
    TVector<std::pair<char, char>> edges;
    edges.push_back({ 'A', 'B' });
    edges.push_back({ 'C', 'D' });

    ListGraph<char> graph(edges, false);
    TVector<int> path = graph.get_dijkstra_path('A', 'D');

    EXPECT_EQ(path.size(), 0);
}

TEST(ListGraphTest, dijkstra_path_directed_graph) {
    TVector<std::pair<std::pair<char, char>, int>> edges;
    edges.push_back({ {'A', 'B'}, 1 });
    edges.push_back({ {'B', 'C'}, 1 });
    edges.push_back({ {'A', 'C'}, 3 });

    ListGraph<char> graph(edges, true);
    TVector<int> path = graph.get_dijkstra_path('A', 'C');

    EXPECT_EQ(path.size(), 3);
    EXPECT_EQ(path[0], graph.find_index('A'));
    EXPECT_EQ(path[1], graph.find_index('B'));
    EXPECT_EQ(path[2], graph.find_index('C'));
}

TEST(ListGraphTest, dijkstra_path_unreachable_in_directed) {
    TVector<std::pair<std::pair<char, char>, int>> edges;
    edges.push_back({ {'A', 'B'}, 1 });
    edges.push_back({ {'C', 'D'}, 1 });

    ListGraph<char> graph(edges, true);
    TVector<int> path = graph.get_dijkstra_path('A', 'D');

    EXPECT_EQ(path.size(), 0);
}

TEST(ListGraphTest, dijkstra_path_complex_graph) {
    TVector<std::pair<std::pair<int, int>, int>> edges;
    edges.push_back({ {1, 2}, 4 });
    edges.push_back({ {1, 3}, 2 });
    edges.push_back({ {2, 3}, 1 });
    edges.push_back({ {2, 4}, 5 });
    edges.push_back({ {3, 4}, 8 });
    edges.push_back({ {3, 5}, 10 });
    edges.push_back({ {4, 5}, 2 });
    edges.push_back({ {4, 6}, 6 });
    edges.push_back({ {5, 6}, 3 });

    ListGraph<int> graph(edges, false);
    TVector<int> path = graph.get_dijkstra_path(1, 6);


    EXPECT_GT(path.size(), 0);
    EXPECT_EQ(path[0], graph.find_index(1));
    EXPECT_EQ(path[path.size() - 1], graph.find_index(6));


    for (size_t i = 0; i < path.size() - 1; i++) {
        bool edge_exists = false;
        for (auto it = graph.adj[path[i]].begin(); it != graph.adj[path[i]].end(); ++it) {
            if ((*it).to == path[i + 1]) {
                edge_exists = true;
                break;
            }
        }
        EXPECT_TRUE(edge_exists) << "No edge between " << path[i] << " and " << path[i + 1];
    }
}

TEST(ListGraphTest, dijkstra_path_throws_on_invalid_start) {
    TVector<std::pair<char, char>> edges;
    edges.push_back({ 'A', 'B' });

    ListGraph<char> graph(edges, false);

    EXPECT_THROW(graph.get_dijkstra_path('Z', 'A'), std::logic_error);
}

TEST(ListGraphTest, dijkstra_path_throws_on_invalid_end) {
    TVector<std::pair<char, char>> edges;
    edges.push_back({ 'A', 'B' });

    ListGraph<char> graph(edges, false);

    EXPECT_THROW(graph.get_dijkstra_path('A', 'Z'), std::logic_error);
}

TEST(ListGraphTest, dijkstra_path_zero_weight_edges) {
    TVector<std::pair<std::pair<char, char>, int>> edges;
    edges.push_back({ {'A', 'B'}, 0 });
    edges.push_back({ {'B', 'C'}, 0 });
    edges.push_back({ {'A', 'C'}, 5 });

    ListGraph<char> graph(edges, false);
    TVector<int> path = graph.get_dijkstra_path('A', 'C');


    EXPECT_EQ(path.size(), 3);
    EXPECT_EQ(path[0], graph.find_index('A'));
    EXPECT_EQ(path[1], graph.find_index('B'));
    EXPECT_EQ(path[2], graph.find_index('C'));
}