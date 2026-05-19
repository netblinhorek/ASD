#include <gtest/gtest.h>
#include "../lib_AdjacencyMatrix/adjacency_matrix.h"

TEST(AdjacencyMatrixTest, construction_and_print) {
    TVector<std::pair<std::pair<int, int>, int>> edges;
    edges.push_back({ {1, 2}, 10 });
    edges.push_back({ {2, 3}, 20 });

    AdjacencyMatrix<int> graph(edges, false);

    EXPECT_EQ(graph.vertices.size(), 3);
    EXPECT_EQ(graph.adj.rows(), 3);
    EXPECT_EQ(graph.find_index(1), 0);
    EXPECT_EQ(graph.find_index(3), 2);
    graph.print();
}

TEST(AdjacencyMatrixTest, delete_vertex) {
    TVector<std::pair<std::pair<int, int>, int>> edges;
    edges.push_back({ {1, 2}, 10 });
    edges.push_back({ {2, 3}, 20 });
    edges.push_back({ {1, 3}, 5 });

    AdjacencyMatrix<int> graph(edges, true);

    graph.delete_vertex(2);

    EXPECT_EQ(graph.vertices.size(), 2);
    EXPECT_EQ(graph.adj.rows(), 2);
    EXPECT_EQ(graph.adj.cols(), 2);

    int idx_1 = graph.find_index(1);
    int idx_3 = graph.find_index(3);

    EXPECT_EQ(graph.adj[idx_1][idx_3], 5);
    graph.print();
}

TEST(AdjacencyMatrixTest, unweighted_graph) {
    TVector<std::pair<int, int>> edges;
    edges.push_back({ 10, 20 });

    AdjacencyMatrix<int> graph(edges, true);

    int u = graph.find_index(10);
    int v = graph.find_index(20);

    EXPECT_EQ(graph.adj[u][v], 1);
    graph.print();
}

TEST(AdjacencyMatrixTest, undirected_weighted_graph) {
    TVector<std::pair<std::pair<char, char>, int>> edges;
    edges.push_back({ {'A', 'B'}, 2 });
    edges.push_back({ {'B', 'C'}, 3 });

    AdjacencyMatrix<char> graph(edges, false);

    int idxA = graph.find_index('A');
    int idxB = graph.find_index('B');
    int idxC = graph.find_index('C');

    EXPECT_EQ(graph.adj[idxA][idxB], 2);
    EXPECT_EQ(graph.adj[idxB][idxA], 2);
    EXPECT_EQ(graph.adj[idxB][idxC], 3);
    EXPECT_EQ(graph.adj[idxC][idxB], 3);
}
TEST(AdjacencyMatrixTest, add_edge_after_delete_vertex) {
    TVector<std::pair<int, int>> edges;
    edges.push_back({ 0, 1 });
    edges.push_back({ 1, 2 });
    edges.push_back({ 2, 0 });

    AdjacencyMatrix<int> graph(edges, false);

    graph.delete_vertex(1);

    graph.add_edge(0, 2, 7);

    int idx0 = graph.find_index(0);
    int idx2 = graph.find_index(2);

    ASSERT_NE(idx0, -1);
    ASSERT_NE(idx2, -1);

    EXPECT_EQ(graph.adj[idx0][idx2], 7);
    EXPECT_EQ(graph.adj[idx2][idx0], 7);
}

TEST(AdjacencyMatrixTest, directed_weighted_graph) {
    TVector<std::pair<std::pair<char, char>, int>> edges;
    edges.push_back({ {'A', 'B'}, 2 });
    edges.push_back({ {'B', 'C'}, 3 });

    AdjacencyMatrix<char> graph(edges, true);

    int idxA = graph.find_index('A');
    int idxB = graph.find_index('B');
    int idxC = graph.find_index('C');

    EXPECT_EQ(graph.adj[idxA][idxB], 2);
    EXPECT_EQ(graph.adj[idxB][idxC], 3);

    EXPECT_EQ(graph.adj[idxB][idxA], MAX_SIZE);
}

TEST(AdjacencyMatrixTest, custom_matrix_example) {
    TVector<std::pair<int, int>> edges;

    for (int i = 0; i <= 6; ++i) edges.push_back({ i, i });

    edges.push_back({ 0, 3 }); 
    edges.push_back({ 0, 5 });
    edges.push_back({ 1, 2 }); 
    edges.push_back({ 1, 4 });
    edges.push_back({ 2, 3 }); 
    edges.push_back({ 2, 4 }); 
    edges.push_back({ 2, 5 });
    edges.push_back({ 3, 6 });
    edges.push_back({ 4, 6 });

    AdjacencyMatrix<int> graph(edges, false);

    ASSERT_EQ(graph.vertices.size(), 7);

    EXPECT_EQ(graph.adj[0][0], 1);
    EXPECT_EQ(graph.adj[0][3], 1);
    EXPECT_EQ(graph.adj[0][5], 1);
    EXPECT_EQ(graph.adj[0][1], MAX_SIZE); 

    EXPECT_EQ(graph.adj[2][1], 1);
    EXPECT_EQ(graph.adj[2][2], 1);
    EXPECT_EQ(graph.adj[2][3], 1);
    EXPECT_EQ(graph.adj[2][4], 1);
    EXPECT_EQ(graph.adj[2][5], 1);
    EXPECT_EQ(graph.adj[2][0], MAX_SIZE);
    EXPECT_EQ(graph.adj[2][6], MAX_SIZE);

    EXPECT_EQ(graph.adj[6][3], 1);
    EXPECT_EQ(graph.adj[6][4], 1);
    EXPECT_EQ(graph.adj[6][6], 1);
    EXPECT_EQ(graph.adj[6][0], MAX_SIZE);

    graph.print();
}

TEST(AdjacencyMatrixTest, delete_vertex_complex) {
    TVector<std::pair<int, int>> edges;
    edges.push_back({ 0, 1 });
    edges.push_back({ 1, 2 });
    edges.push_back({ 2, 0 });

    AdjacencyMatrix<int> graph(edges, false);

    graph.delete_vertex(1);

    EXPECT_EQ(graph.vertices.size(), 2);

    int idx0 = graph.find_index(0);
    int idx2 = graph.find_index(2);

    ASSERT_NE(idx0, -1);
    ASSERT_NE(idx2, -1);
    EXPECT_EQ(graph.adj[idx0][idx2], 1);
    EXPECT_EQ(graph.adj[idx2][idx0], 1);
}


