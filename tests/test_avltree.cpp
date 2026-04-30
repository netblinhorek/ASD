#include <gtest/gtest.h>
#include "../lib_AVLTree/avltree.h"


TEST(TestALVTree, test_default_constructor_empty_tree) {
    ALVTree<int, std::string> tree;  
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestALVTree, test_insert_no_throw) {
    ALVTree<int, std::string> tree;  

    EXPECT_NO_THROW({
        tree.insert(1, "one");
        tree.insert(2, "two");
        tree.insert(3, "three");
        tree.insert(4, "four");
        tree.insert(5, "five");
        });

    EXPECT_FALSE(tree.is_empty());
}

TEST(TestALVTree, test_clear_empty_tree) {
    ALVTree<int, std::string> tree; 
    EXPECT_NO_THROW(tree.clear());
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestALVTree, test_clear_single_element) {
    ALVTree<int, std::string> tree; 
    tree.insert(1, "one");
    tree.clear();
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestALVTree, test_find_empty_throws) {
    ALVTree<int, std::string> tree;  
    EXPECT_THROW(tree.find(42), std::out_of_range);
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestALVTree, test_find_negative_keys) {
    ALVTree<int, std::string> tree;  
    tree.insert(-5, "minus five");
    tree.insert(0, "zero");
    tree.insert(5, "five");

    EXPECT_NO_THROW(tree.find(-5));
    EXPECT_NO_THROW(tree.find(0));
    EXPECT_NO_THROW(tree.find(5));

    EXPECT_NE(tree.find(-5), nullptr);
    EXPECT_NE(tree.find(0), nullptr);
    EXPECT_NE(tree.find(5), nullptr);

    EXPECT_THROW(tree.find(10), std::out_of_range);
    EXPECT_THROW(tree.find(-10), std::out_of_range);

    ALVNode<int, std::string>* node = tree.find(5);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->_data.second, "five");
}

TEST(TestALVTree, Erase_Empty_Throws) {
    ALVTree<int, std::string> tree; 
    EXPECT_THROW(tree.erase(42), std::logic_error);
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestALVTree, erase_root_single_element_empty) {
    ALVTree<int, std::string> tree;  
    tree.insert(42, "answer");

    EXPECT_NO_THROW(tree.erase(42));
    EXPECT_TRUE(tree.is_empty());
    EXPECT_THROW(tree.find(42), std::out_of_range);
}

TEST(TestALVTree, test_erase_root) {
    ALVTree<int, std::string> tree; 
    tree.insert(1, "one");
    tree.insert(2, "two");
    tree.insert(3, "three");

    EXPECT_NO_THROW(tree.erase(1));
    EXPECT_THROW(tree.find(1), std::out_of_range);
    EXPECT_NO_THROW(tree.find(2));
    EXPECT_NO_THROW(tree.find(3));
    EXPECT_NE(tree.find(2), nullptr);
    EXPECT_NE(tree.find(3), nullptr);

    ALVNode<int, std::string>* node = tree.find(2);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->_data.second, "two");
}

TEST(TestALVTree, test_erase_non_existent_throws) {
    ALVTree<int, std::string> tree;  
    tree.insert(1, "one");
    tree.insert(2, "two");

    EXPECT_THROW(tree.erase(999), std::logic_error);
    EXPECT_NO_THROW(tree.find(1));
    EXPECT_NO_THROW(tree.find(2));
    EXPECT_NE(tree.find(1), nullptr);
    EXPECT_NE(tree.find(2), nullptr);
}

TEST(TestALVTree, test_erase_empty_tree_throws) {
    ALVTree<int, std::string> tree;  
    EXPECT_THROW(tree.erase(42), std::logic_error);
}

TEST(TestALVTree, test_find_after_erase_throws) {
    ALVTree<int, std::string> tree;  
    tree.insert(10, "ten");
    tree.insert(20, "twenty");
    tree.erase(10);

    EXPECT_THROW(tree.find(10), std::out_of_range);
    EXPECT_NO_THROW(tree.find(20));
    EXPECT_NE(tree.find(20), nullptr);
}

TEST(TestALVTree, test_erase_and_find_remaining) {
    ALVTree<int, std::string> tree;  
    tree.insert(100, "hundred");
    tree.insert(200, "two hundred");
    tree.insert(300, "three hundred");

    tree.erase(200);

    EXPECT_THROW(tree.find(200), std::out_of_range);
    EXPECT_NO_THROW(tree.find(100));
    EXPECT_NO_THROW(tree.find(300));
    EXPECT_NE(tree.find(100), nullptr);
    EXPECT_NE(tree.find(300), nullptr);

    ALVNode<int, std::string>* node1 = tree.find(100);
    ALVNode<int, std::string>* node3 = tree.find(300);
    ASSERT_NE(node1, nullptr);
    ASSERT_NE(node3, nullptr);
    EXPECT_EQ(node1->_data.second, "hundred");
    EXPECT_EQ(node3->_data.second, "three hundred");
}