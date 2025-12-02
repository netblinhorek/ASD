#include <gtest/gtest.h>
#include "../lib_DSU/DSU.h"


TEST(TestDSU, test_constructor_DSU_and_throw) {
    ASSERT_THROW(DSU dsu(0), std::logic_error);
    ASSERT_NO_THROW(DSU dsu(5));
} 

TEST(TestDSU, test_DSU_union_set_and_throw) {
    DSU dsu(5);
    
    ASSERT_NO_THROW(dsu.union_set(2, 3));
    ASSERT_THROW(dsu.union_set(6, 3), std::logic_error);
    ASSERT_THROW(dsu.union_set(2, 7), std::logic_error);
}

TEST(TestDSU, test_DSU_union_find_and_throw) {
    DSU dsu(6);

    dsu.union_set(4, 1);
    dsu.union_set(3, 2);
    dsu.union_set(2, 5);

    int true_value = dsu.find(5); 
    ASSERT_EQ(true_value, 3);

    ASSERT_THROW(dsu.find(6), std::logic_error);
}

TEST(TestDSU, test_DSU_union_find_and_throw_tree) {
    DSU dsu(6);

    dsu.union_set(4, 1);
    dsu.union_set(2, 3);
    dsu.union_set(2, 5);

    int tree_value = dsu.find(5); //2
    int one_value = dsu.find(1); //4
    ASSERT_EQ(tree_value, 2);
    ASSERT_EQ(one_value, 4);

    dsu.union_set(3, 4);
    int general_value = dsu.find(1); //2
    ASSERT_EQ(general_value, 2);
}
TEST(TestDSU, test_DSU_repeated_union) {
    DSU dsu(5);

    dsu.union_set(0, 1);
    ASSERT_NO_THROW(dsu.union_set(0, 1)); 
    ASSERT_NO_THROW(dsu.union_set(1, 0)); 

    ASSERT_EQ(dsu.find(0), dsu.find(1));
}

TEST(TestDSU, test_DSU_rank) {
    DSU dsu(7);

    for (int i = 0; i < 7; ++i) {
        ASSERT_EQ(dsu.get_rank(i), 0);
    }

    dsu.union_set(0, 1);
    ASSERT_EQ(dsu.get_rank(dsu.find(0)), 1); 

    dsu.union_set(2, 3);
    dsu.union_set(4, 5);

    ASSERT_EQ(dsu.get_rank(dsu.find(2)), 1);
    ASSERT_EQ(dsu.get_rank(dsu.find(4)), 1);

    dsu.union_set(0, 2);
    ASSERT_EQ(dsu.get_rank(dsu.find(0)), 2);

    dsu.union_set(0, 6);
    ASSERT_EQ(dsu.get_rank(dsu.find(0)), 2);

    ASSERT_THROW(dsu.get_rank(-1), std::logic_error);
    ASSERT_THROW(dsu.get_rank(7), std::logic_error);
}

TEST(TestDSU, test_DSU_negative_indices) {
    DSU dsu(5);

    ASSERT_THROW(dsu.find(-1), std::logic_error);
    ASSERT_THROW(dsu.union_set(-1, 0), std::logic_error);
    ASSERT_THROW(dsu.union_set(0, -1), std::logic_error);
    ASSERT_THROW(dsu.union_set(-1, -2), std::logic_error);
}

TEST(TestDSU, test_DSU_find_recurtion_path_compression) {
    DSU dsu(6);

    dsu.union_set(1, 2);
    dsu.union_set(2, 3);
    dsu.union_set(3, 4);

    int root_before = dsu.find_recurtion(3);
    ASSERT_EQ(root_before, dsu.find_recurtion(1));

    ASSERT_EQ(dsu.get_rank(root_before), 1);
    ASSERT_EQ(dsu.get_rank(2), 0);
    ASSERT_EQ(dsu.get_rank(3), 0);
    ASSERT_EQ(dsu.get_rank(4), 0);

    ASSERT_EQ(dsu.find_recurtion(3), root_before);
}

TEST(TestDSU, test_DSU_find_recurtion_out_of_range) {
    DSU dsu(3);

    ASSERT_THROW(dsu.find_recurtion(-1), std::logic_error);
    ASSERT_THROW(dsu.find_recurtion(3), std::logic_error);
}

TEST(TestDSU, test_DSU_find_recurtion_branching_tree) {
    DSU dsu(7);

    dsu.union_set(0, 1);
    dsu.union_set(0, 2);
    dsu.union_set(1, 3);
    dsu.union_set(1, 4);
    dsu.union_set(2, 5);


    int root = dsu.find_recurtion(3);

    ASSERT_EQ(root, dsu.find_recurtion(0));
    ASSERT_EQ(root, dsu.find_recurtion(1));
    ASSERT_EQ(root, dsu.find_recurtion(2));
    ASSERT_EQ(root, dsu.find_recurtion(4));
    ASSERT_EQ(root, dsu.find_recurtion(5));

    ASSERT_EQ(root, dsu.find_recurtion(3));
    ASSERT_EQ(root, dsu.find_recurtion(5));

    ASSERT_EQ(dsu.get_rank(root), 1);
    ASSERT_EQ(dsu.get_rank(1), 0);
    ASSERT_EQ(dsu.get_rank(2), 0);
    ASSERT_EQ(dsu.get_rank(3), 0);
    ASSERT_EQ(dsu.get_rank(4), 0);
    ASSERT_EQ(dsu.get_rank(5), 0);
}
TEST(TestDSU, unionn_rank) {
    DSU dsu(4);

    dsu.union_set(0, 1);
    dsu.union_set(2, 3);
    dsu.union_set(0, 2);

    EXPECT_EQ(0, dsu.find(0));
    EXPECT_EQ(0, dsu.find(1));
    EXPECT_EQ(0, dsu.find(2));
    EXPECT_EQ(0, dsu.find(3));

    EXPECT_EQ(dsu.find(3), dsu.find(2));
    EXPECT_EQ(2, dsu.get_rank(0));
}

TEST(TestDSU, test_DSU_find_recurtion_linear_chain) {
    DSU dsu(10);

    for (int i = 0; i < 9; ++i) {
        dsu.union_set(i, i + 1);
    }

    int root = dsu.find_recurtion(9);

    for (int i = 0; i < 10; ++i) {
        ASSERT_EQ(root, dsu.find_recurtion(i));
    }

    ASSERT_EQ(dsu.get_rank(root), 1);
    for (int i = 0; i < 10; ++i) {
        if (i == root) continue;
        ASSERT_EQ(dsu.get_rank(i), 0);
    }
}


TEST(TestDSU, complex_union_scenario) {

    DSU dsu(8);
    dsu.union_set(0, 1);  
    dsu.union_set(1, 2);  
    dsu.union_set(2, 3);  

    int root1 = dsu.find(0);
    EXPECT_EQ(root1, dsu.find(1));
    EXPECT_EQ(root1, dsu.find(2));
    EXPECT_EQ(root1, dsu.find(3));
    EXPECT_EQ(dsu.get_rank(root1), 1);  
    EXPECT_EQ(root1, 0);  

    dsu.union_set(4, 5);  
    dsu.union_set(6, 7);  
    dsu.union_set(4, 6);  

    int root2 = dsu.find(4);
    EXPECT_EQ(root2, dsu.find(5));
    EXPECT_EQ(root2, dsu.find(6));
    EXPECT_EQ(root2, dsu.find(7));
    EXPECT_EQ(dsu.get_rank(root2), 2);  
    EXPECT_EQ(root2, 4); 

    dsu.union_set(0, 4);  

    int final_root = dsu.find(0);

    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(final_root, dsu.find(i));
    }

    EXPECT_EQ(final_root, 4);
    EXPECT_EQ(dsu.get_rank(final_root), 2);
}