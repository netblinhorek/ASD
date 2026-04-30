//#include <gtest/gtest.h>
//#include <string>
//#include "../lib_algorithms/algorithms.h" 
//
//TEST(DictionaryMergeTest, test_is_empty_input) {
//    TVector<std::pair<std::string, int>> d1;
//    TVector<std::pair<std::string, int>> d2;
//
//    auto result = merge_dictionaries(d1, d2);
//
//    EXPECT_EQ(result.size(), 0);
//}
//TEST(DictionaryMergeTest, test_check_Ppriority_of_first_vector_sem) {
//    TVector<std::pair<std::string, int>> d1;
//    d1.push_back({ "table", 1349 });
//    d1.push_back({ "hash", 1985 });
//    d1.push_back({ "list", 4372 });
//    TVector<std::pair<std::string, int>> d2;
//    d2.push_back({ "massive", 4312 });
//    d2.push_back({ "list", 5863 });
//    d2.push_back({ "hash", 4317 });
//    d2.push_back({ "vector", 2586 });
//    auto result = merge_dictionaries(d1, d2);
//
//    EXPECT_EQ(result.size(), 5);
//    EXPECT_EQ(result.found("list"), 4372);
//    EXPECT_EQ(result.found("hash"), 1985);  
//}