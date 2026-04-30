#include <gtest/gtest.h>
#include "../lib_Tree/tree.h"


TEST(TestTree, test_default_constructor_empty_tree) {
    Tree<int, std::string> tree;
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestTree, test_insert_no_throw) {
    Tree<int, std::string> tree;

    EXPECT_NO_THROW({
        tree.insert(1, "one");
        tree.insert(2, "two");
        tree.insert(3, "three");
        tree.insert(4, "four");
        tree.insert(5, "five");
        });

    EXPECT_FALSE(tree.is_empty());
}


TEST(TestTree, test_print_w_empty_no_throw) {
    Tree<int, std::string> tree;
    EXPECT_NO_THROW(tree.print_w());
}

TEST(TestTree, test_print_dlcr_empty_no_throw) {
    Tree<int, std::string> tree;
    EXPECT_NO_THROW(tree.print_dlcr());
}

TEST(TestTree, test_print_dlrc_empty_no_throw) {
    Tree<int, std::string> tree;
    EXPECT_NO_THROW(tree.print_dlrc());
}

TEST(TestTree, test_print_dclr_empty_no_throw) {
    Tree<int, std::string> tree;
    EXPECT_NO_THROW(tree.print_dclr());
}


TEST(TestTree, test_print_w_with_elements_no_throw) {
    Tree<int, std::string> tree;
    tree.insert(1, "one");
    tree.insert(2, "two");
    tree.insert(3, "three");
    tree.insert(4, "four");
    tree.insert(5, "five");
    tree.insert(6, "six");
    tree.insert(7, "seven");

    EXPECT_NO_THROW(tree.print_w());
}

TEST(TestTree, test_print_dlcr_with_elements_no_throw) {
    Tree<int, std::string> tree;
    tree.insert(1, "one");
    tree.insert(2, "two");
    tree.insert(3, "three");
    tree.insert(4, "four");
    tree.insert(5, "five");
    tree.insert(6, "six");
    tree.insert(7, "seven");

    EXPECT_NO_THROW(tree.print_dlcr());
}

TEST(TestTree, test_print_dlrc_with_elements_no_throw) {
    Tree<int, std::string> tree;
    tree.insert(1, "one");
    tree.insert(2, "two");
    tree.insert(3, "three");
    tree.insert(4, "four");
    tree.insert(5, "five");
    tree.insert(6, "six");
    tree.insert(7, "seven");

    EXPECT_NO_THROW(tree.print_dlrc());
}
TEST(TestTree, test_print_dlrc_with_elements_no_throw_other) {
    Tree<int, std::string> tree;
    tree.insert(1, "one");
    tree.insert(2, "two");
    tree.insert(3, "three");
    tree.insert(4, "four");
    tree.insert(5, "five");
    tree.insert(6, "six");
    tree.insert(7, "seven");
    tree.insert(8, "five");
    tree.insert(9, "six");
    tree.insert(10, "seven");

    EXPECT_NO_THROW(tree.print_dlrc());
}


TEST(TestTree, test_print_dclr_with_elements_no_throw) {
    Tree<int, std::string> tree;
    tree.insert(1, "one");
    tree.insert(2, "two");
    tree.insert(3, "three");
    tree.insert(4, "four");
    tree.insert(5, "five");
    tree.insert(6, "six");
    tree.insert(7, "seven");
    EXPECT_NO_THROW(tree.print_dclr());
}


TEST(TestTree, test_clear_empty_tree) {
    Tree<int, std::string> tree;
    EXPECT_NO_THROW(tree.clear());
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestTree, test_clear_single_element) {
    Tree<int, std::string> tree;
    tree.insert(1, "one");
    tree.clear();
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestTree, test_insert_duplicate_key_throws) {
    Tree<int, std::string> tree;
    tree.insert(1, "one");

    EXPECT_THROW(tree.insert(1, "ONE"), std::logic_error);

    EXPECT_EQ(tree.find(1)->_data.second, "one");
}
TEST(TestTree, test_get_root_ptr) {
    Tree<int, std::string> tree;
    EXPECT_EQ(tree.get_root_ptr(), nullptr);

    tree.insert(1, "one");
    EXPECT_NE(tree.get_root_ptr(), nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_data.first, 1);
}

TEST(TestTree, test_erase_last_node) {
    Tree<int, std::string> tree;
    tree.insert(1, "one");
    tree.insert(2, "two");
    tree.insert(3, "three");
    tree.insert(4, "four");  

    EXPECT_NO_THROW(tree.erase(4));  
    EXPECT_THROW(tree.find(4), std::out_of_range);
    EXPECT_EQ(tree.find(1)->_data.first, 1); 
}

TEST(TestTree, test_deep_tree) {
    Tree<int, std::string> tree;

    for (int i = 1; i <= 15; ++i) {
        EXPECT_NO_THROW(tree.insert(i, "val"));
    }

    EXPECT_EQ(tree.find(15)->_data.first, 15);
}

TEST(TestTree, test_find_empty_throws) {
    Tree<int, std::string> tree;
    EXPECT_THROW(tree.find(42), std::out_of_range);
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestTree, test_find_negative_keys) {
    Tree<int, std::string> tree;
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

    Node<int, std::string>* node = tree.find(5);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->_data.second, "five");
}


TEST(TestTree, test_erase_empty_throws) {
    Tree<int, std::string> tree;
    EXPECT_THROW(tree.erase(42), std::logic_error);
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestTree, erase_root_single_element_empty) {
    Tree<int, std::string> tree;
    tree.insert(42, "answer");

    EXPECT_NO_THROW(tree.erase(42));
    EXPECT_TRUE(tree.is_empty());
    EXPECT_THROW(tree.find(42), std::out_of_range);
}

TEST(TestTree, test_erase_root) {
    Tree<int, std::string> tree;
    tree.insert(1, "one");
    tree.insert(2, "two");
    tree.insert(3, "three");

    EXPECT_NO_THROW(tree.erase(1));
    EXPECT_THROW(tree.find(1), std::out_of_range);
    EXPECT_NO_THROW(tree.find(2));
    EXPECT_NO_THROW(tree.find(3));
    EXPECT_NE(tree.find(2), nullptr);
    EXPECT_NE(tree.find(3), nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_data.first, 3);
    EXPECT_EQ(tree.get_root_ptr()->_data.second, "three");

    ASSERT_NE(tree.get_root_ptr()->_left, nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_left->_data.first, 2);
    EXPECT_EQ(tree.get_root_ptr()->_left->_data.second, "two");

    EXPECT_EQ(tree.get_root_ptr()->_right, nullptr);
}


TEST(TestTree, test_erase_parent) {
    Tree<int, std::string> tree;
    tree.insert(10, "10");
    tree.insert(5, "5");
    tree.insert(15, "15");
    tree.insert(2, "2");
    tree.insert(7, "7");
    tree.insert(12, "12");
    tree.insert(20, "20");

    //          10
    //         /  \
    //        5    15
    //       / \   / \
    //      2   7 12 20

    EXPECT_NO_THROW(tree.erase(5));


    ASSERT_NE(tree.get_root_ptr(), nullptr);

    EXPECT_EQ(tree.get_root_ptr()->_data.first, 10);
    EXPECT_EQ(tree.get_root_ptr()->_data.second, "10");

    ASSERT_NE(tree.get_root_ptr()->_left, nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_left->_data.first, 20); 
    EXPECT_EQ(tree.get_root_ptr()->_left->_data.second, "20");

    ASSERT_NE(tree.get_root_ptr()->_left->_left, nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_left->_left->_data.first, 2);
    EXPECT_EQ(tree.get_root_ptr()->_left->_left->_data.second, "2");

    ASSERT_NE(tree.get_root_ptr()->_left->_right, nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_left->_right->_data.first, 7);
    EXPECT_EQ(tree.get_root_ptr()->_left->_right->_data.second, "7");

    ASSERT_NE(tree.get_root_ptr()->_right, nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_right->_data.first, 15);
    EXPECT_EQ(tree.get_root_ptr()->_right->_data.second, "15");

    ASSERT_NE(tree.get_root_ptr()->_right->_left, nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_right->_left->_data.first, 12);
    EXPECT_EQ(tree.get_root_ptr()->_right->_left->_data.second, "12");

    EXPECT_EQ(tree.get_root_ptr()->_right->_right, nullptr);

    EXPECT_THROW(tree.find(5), std::logic_error);

    EXPECT_NO_THROW(tree.find(10));
    EXPECT_NO_THROW(tree.find(2));
    EXPECT_NO_THROW(tree.find(7));
    EXPECT_NO_THROW(tree.find(15));
    EXPECT_NO_THROW(tree.find(12));
    EXPECT_NO_THROW(tree.find(20));
}


TEST(TestTree, test_erase_non_existent_throws) {
    Tree<int, std::string> tree;
    tree.insert(1, "one");
    tree.insert(2, "two");

    EXPECT_THROW(tree.erase(999), std::logic_error);
    EXPECT_NO_THROW(tree.find(1));
    EXPECT_NO_THROW(tree.find(2));
    EXPECT_NE(tree.find(1), nullptr);
    EXPECT_NE(tree.find(2), nullptr);
}

TEST(TestTree, test_erase_empty_tree_throws) {
    Tree<int, std::string> tree;
    EXPECT_THROW(tree.erase(42), std::logic_error);
}

TEST(TestTree, test_find_after_erase_throws) {
    Tree<int, std::string> tree;
    tree.insert(10, "ten");
    tree.insert(20, "twenty");
    tree.erase(10);

    EXPECT_THROW(tree.find(10), std::out_of_range);
    EXPECT_NO_THROW(tree.find(20));
    EXPECT_NE(tree.find(20), nullptr);
}

TEST(TestTree, test_erase_and_find_remaining) {
    Tree<int, std::string> tree;
    tree.insert(100, "hundred");
    tree.insert(200, "two hundred");
    tree.insert(300, "three hundred");

    tree.erase(200);

    EXPECT_THROW(tree.find(200), std::out_of_range);
    EXPECT_NO_THROW(tree.find(100));
    EXPECT_NO_THROW(tree.find(300));
    EXPECT_NE(tree.find(100), nullptr);
    EXPECT_NE(tree.find(300), nullptr);

    Node<int, std::string>* node1 = tree.find(100);
    Node<int, std::string>* node3 = tree.find(300);
    ASSERT_NE(node1, nullptr);
    ASSERT_NE(node3, nullptr);
    EXPECT_EQ(node1->_data.second, "hundred");
    EXPECT_EQ(node3->_data.second, "three hundred");
}