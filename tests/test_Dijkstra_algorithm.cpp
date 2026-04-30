//#include <gtest/gtest.h>
//#include <string>
//#include "../lib_Dijkstra_algorithm/Dijkstra_algorithm.h"
//
//
//TEST(DijkstraTest, Correctness_UpdateDistance) {
//    TVector<std::pair<std::pair<char, char>, int>> edges = {
//        {{'A', 'B'}, 10},
//        {{'A', 'C'}, 3},
//        {{'C', 'B'}, 2},
//        {{'B', 'D'}, 1},
//        {{'C', 'D' },2}
//    };
//
//    ListGraph<char> graph(edges, true);
//    TVector<int> dist = dijkstra('A');
//
//    EXPECT_EQ(dist[graph.find_index('B')], 5);
//    EXPECT_EQ(dist[graph.find_index('D')], 6);  
//}