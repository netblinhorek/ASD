#include <gtest/gtest.h>
#include <string>
#include "../lib_RBTree/rbtree.h" 
#include "../lib_BaseBSTree/base_bstree.h" 

TEST(TestRBTree, test_default_constructor_empty_tree) {
    RBTree<int, std::string> tree;
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(tree.get_root_ptr(), nullptr);
}

TEST(TestRBTree, test_insert_no_throw_and_color_rules) {
    RBTree<int, std::string> tree;

    EXPECT_NO_THROW({
        tree.insert(10, "ten");
        tree.insert(20, "twenty");
        tree.insert(30, "thirty");
        tree.insert(15, "fifteen");
        });

    EXPECT_FALSE(tree.is_empty());

    auto root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->_color, Color::Black);
}

TEST(TestRBTree, test_clear_empty_tree) {
    RBTree<int, std::string> tree;
    EXPECT_NO_THROW(tree.clear());
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestRBTree, test_clear_single_element) {
    RBTree<int, std::string> tree;
    tree.insert(10, "ten");
    tree.clear();
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(tree.get_root_ptr(), nullptr);
}

TEST(TestRBTree, test_find_empty_throws) {
    RBTree<int, std::string> tree;
    EXPECT_THROW(tree.find(42), std::out_of_range);
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestRBTree, test_find_negative_keys) {
    RBTree<int, std::string> tree;
    tree.insert(-5, "minus five");
    tree.insert(0, "zero");
    tree.insert(5, "five");

    EXPECT_THROW(tree.find(10), std::out_of_range);

    std::string* value_ptr = tree.find(5);
    ASSERT_NE(value_ptr, nullptr);
    EXPECT_EQ(*value_ptr, "five");
}

TEST(TestRBTree, Erase_Empty_Throws) {
    RBTree<int, std::string> tree;
    EXPECT_THROW(tree.erase(42), std::out_of_range);
}

TEST(TestRBTree, erase_root_single_element_empty) {
    RBTree<int, std::string> tree;
    tree.insert(42, "answer");

    EXPECT_NO_THROW(tree.erase(42));
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestRBTree, test_erase_root) {
    RBTree<int, std::string> tree;
    tree.insert(10, "ten");
    tree.insert(20, "twenty");
    tree.insert(30, "thirty");

    /*
              20(Black)
             /         \
          10(Red)     30(Red)

    */

    EXPECT_NO_THROW(tree.erase(10));
    /*
     
              20(Black)
                       \
                      30(Red) 
    */
    EXPECT_THROW(tree.find(10), std::out_of_range);

    auto root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->_color, Color::Black);
}

TEST(TestRBTree, test_erase_red_leaf_no_rotation) {
    RBTree<int, std::string> tree;
    tree.insert(20, "twenty");
    tree.insert(10, "ten");
    tree.insert(30, "thirty");
    tree.insert(25, "twenty five");

    /*
                     20(Black)
                    /         \
                10(Black)    30(Black)
                             /
                          25(Red)
    */

    EXPECT_NO_THROW(tree.erase(25));
    /*
                     20(Black)
                    /         \
                10(Black)    30(Black)
    */
    EXPECT_THROW(tree.find(25), std::out_of_range);
}

TEST(TestRBTree, test_erase_node_with_one_red_child) {
    RBTree<int, std::string> tree;
    tree.insert(20, "twenty");
    tree.insert(10, "ten");
    tree.insert(30, "thirty");
    tree.insert(25, "twenty five");

    /*
                     20(Black)
                    /         \
                10(Black)    30(Black)
                             /
                          25(Red)
    */

    EXPECT_NO_THROW(tree.erase(30));
    /*
                     20(Black)
                    /         \
                10(Black)    25(Black)
    */
    EXPECT_THROW(tree.find(30), std::out_of_range);

    auto node25 = tree.find_node(25);
    ASSERT_NE(node25, nullptr);
    EXPECT_EQ(node25->_color, Color::Black);
}
TEST(TestRBTree, test_erase_complex_double_black_two_rotations) {
    RBTree<int, std::string> tree;

    tree.insert(50, "root");
    tree.insert(25, "left sibling");
    tree.insert(85, "target to delete"); 
    tree.insert(75, "right brother");
    tree.insert(65, "brother-left");
    tree.insert(60, "inner red child");
    tree.insert(15, "left-left");
    tree.insert(35, "left-right");

    /*
                           50 (Черный)
                         /             \
                  25 (Черный)         75 (Черный)
                  /        \          /         \
            15 (Черный)  35 (Ч)   65 (Черный)  85 (Черный) 
                                  /
                               60 (Красный)
    */
    auto root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->_color, Color::Black);

    EXPECT_NO_THROW(tree.erase(85));
    EXPECT_EQ(tree.find_node(85), nullptr);
    /*
                           50 (Черный)
                         /             \
                  25 (Черный)         65 (Черный)
                  /        \          /         \
            15 (Черный)  35 (Ч)   60 (Черный)  75 (Черный)
    */
    root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->_color, Color::Black);

}

TEST(TestRBTree, test_erase_red_node_with_black_children) {
    RBTree<int, std::string> tree;
    tree.insert(20, "twenty");
    tree.insert(10, "ten");
    tree.insert(30, "thirty");
    tree.insert(5, "five");
    tree.insert(15, "fifteen");

    /*
                     20(Black)
                    /         \
                10(Red)      30(Black)
                /    \
             5(B)    15(B)
    */

    EXPECT_NO_THROW(tree.erase(10));
    /*
    
                     20(Black)
                    /         \
                15(Black)    30(Black)
                /
             5(Black)
    */
    EXPECT_THROW(tree.find(10), std::out_of_range);
}

TEST(TestRBTree, test_erase_root_with_two_children) {
    RBTree<int, std::string> tree;
    tree.insert(20, "twenty");
    tree.insert(10, "ten");
    tree.insert(30, "thirty");
    tree.insert(5, "five");
    tree.insert(15, "fifteen");
    tree.insert(25, "twenty five");
    tree.insert(35, "thirty five");

    /*
                     20(Black)
                    /         \
                10(Red)      30(Red)
                /    \       /    \
             5(B)   15(B)  25(B)  35(B)

    */

    EXPECT_NO_THROW(tree.erase(20));
    /*
    
                     25(Black)  
                    /         \
                10(Red)      30(Red)
                /    \            \
             5(B)   15(B)         35(B)
    */
    EXPECT_THROW(tree.find(20), std::out_of_range);

    auto new_root = tree.get_root_ptr();
    ASSERT_NE(new_root, nullptr);
    EXPECT_EQ(new_root->_color, Color::Black);
}


    TEST(TestRBTree, test_cascade_erase) {
    RBTree<int, std::string> tree;
    tree.insert(50, "fifty");
    tree.insert(30, "thirty");
    tree.insert(70, "seventy");
    tree.insert(20, "twenty");
    tree.insert(40, "forty");
    tree.insert(60, "sixty");
    tree.insert(80, "eighty");
    tree.insert(10, "ten");
    tree.insert(35, "thirty five");
    tree.insert(45, "forty five");
    tree.insert(55, "fifty five");
    tree.insert(75, "seventy five");
    tree.insert(90, "ninety");

    /*
                  50 (Black)
                /            \
               /              \
         30 (Black)           70 (Black)
         /        \           /        \
     20 (Red)    40 (Red) 60 (Red)    80 (Red)
     /           /    \    /   \      /    \
  10 (Black) 35(B) 45(B) 55(B) 65(B) 75(B) 90(B)
    */

    EXPECT_NO_THROW(tree.erase(10));
    EXPECT_THROW(tree.find(10), std::out_of_range);
    /*
                  50 (Black)
                /            \
              /                \
        30 (Red)               70 (Red)
        /      \               /        \
    20 (Black)  40 (Black) 60 (Black)  80 (Black)
                 /   \       /           /    \
           35 (Red) 45 (Red) 55 (Red) 75 (Red) 90 (Red)

 */
    auto* root = tree.find_node(50);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->_color, Color::Black);
    EXPECT_EQ(root->_parent, nullptr);

    auto* node30 = root->_left;
    ASSERT_NE(node30, nullptr);
    EXPECT_EQ(node30->_data.first, 30);
    EXPECT_EQ(node30->_color, Color::Red);
    EXPECT_EQ(node30->_parent, root);

    auto* node20 = node30->_left;
    ASSERT_NE(node20, nullptr);
    EXPECT_EQ(node20->_data.first, 20);
    EXPECT_EQ(node20->_color, Color::Black);
    EXPECT_EQ(node20->_parent, node30);

    auto* node40 = node30->_right;
    ASSERT_NE(node40, nullptr);
    EXPECT_EQ(node40->_data.first, 40);
    EXPECT_EQ(node40->_color, Color::Black);
    EXPECT_EQ(node40->_parent, node30);

    auto* node35 = node40->_left;
    ASSERT_NE(node35, nullptr);
    EXPECT_EQ(node35->_data.first, 35);
    EXPECT_EQ(node35->_color, Color::Red);
    EXPECT_EQ(node35->_parent, node40);

    auto* node45 = node40->_right;
    ASSERT_NE(node45, nullptr);
    EXPECT_EQ(node45->_data.first, 45);
    EXPECT_EQ(node45->_color, Color::Red);
    EXPECT_EQ(node45->_parent, node40);

    auto* node70 = root->_right;
    ASSERT_NE(node70, nullptr);
    EXPECT_EQ(node70->_data.first, 70);
    EXPECT_EQ(node70->_color, Color::Red);
    EXPECT_EQ(node70->_parent, root);

    auto* node60 = node70->_left;
    ASSERT_NE(node60, nullptr);
    EXPECT_EQ(node60->_data.first, 60);
    EXPECT_EQ(node60->_color, Color::Black);
    EXPECT_EQ(node60->_parent, node70);

    auto* node55 = node60->_left;
    ASSERT_NE(node55, nullptr);
    EXPECT_EQ(node55->_data.first, 55);
    EXPECT_EQ(node55->_color, Color::Red);
    EXPECT_EQ(node55->_parent, node60);

    auto* node80 = node70->_right;
    ASSERT_NE(node80, nullptr);
    EXPECT_EQ(node80->_data.first, 80);
    EXPECT_EQ(node80->_color, Color::Black);
    EXPECT_EQ(node80->_parent, node70);

    auto* node75 = node80->_left;
    ASSERT_NE(node75, nullptr);
    EXPECT_EQ(node75->_data.first, 75);
    EXPECT_EQ(node75->_color, Color::Red);
    EXPECT_EQ(node75->_parent, node80);

    auto* node90 = node80->_right;
    ASSERT_NE(node90, nullptr);
    EXPECT_EQ(node90->_data.first, 90);
    EXPECT_EQ(node90->_color, Color::Red);
    EXPECT_EQ(node90->_parent, node80);
}
