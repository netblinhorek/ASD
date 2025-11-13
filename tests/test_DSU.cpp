// Copyright 2024 Marina Usova

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

TEST(TestDSU, test_DSU_negative_indices) {
    DSU dsu(5);

    ASSERT_THROW(dsu.find(-1), std::logic_error);
    ASSERT_THROW(dsu.union_set(-1, 0), std::logic_error);
    ASSERT_THROW(dsu.union_set(0, -1), std::logic_error);
    ASSERT_THROW(dsu.union_set(-1, -2), std::logic_error);
}