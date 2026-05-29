#include <gtest/gtest.h>
#include <string>
#include "../lib_RBTree/rbtree.h" 
#include "../lib_BaseBSTree/base_bstree.h"
#include "../lib_Polynom/polynom.h"
#include "../lib_Monom/monom.h" 

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




TEST(TestRBTree, case1_recolor) {
    RBTree<int, int> tree;
    /*
        ������� 50, 25, 75              ������� 15

         50 (B)                             50 (B)                           50 (B)
        /      \                           /      \                         /      \
     25 (R)   75 (R)                    25 (R)   75 (R)                  25 (B)   75 (B)
                                        /                                /
                                    15 (R)                           15 (R)
    */

    tree.insert(50, 0);
    tree.insert(25, 0);
    tree.insert(75, 0);
    tree.insert(15, 0);

    auto* root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->_data.first, 50);
    EXPECT_EQ(root->_color, Color::Black);

    EXPECT_EQ(root->_left->_data.first, 25);
    EXPECT_EQ(root->_left->_color, Color::Black);

    EXPECT_EQ(root->_right->_data.first, 75);
    EXPECT_EQ(root->_right->_color, Color::Black);

    EXPECT_EQ(root->_left->_left->_data.first, 15);
    EXPECT_EQ(root->_left->_left->_color, Color::Red);
}

TEST(TestRBTree, case2_LL) {
    RBTree<int, int> tree;

    /*
                                                    ������� 5                          LL

                 50 (B)                             50 (B)                           50 (B)
                /      \                           /      \                         /      \
             25 (B)   75 (B)                    25 (B)   75 (B)                  15 (B)   75 (B)
             /                                  /                                /    \
          15 (R)                             15 (R)                           5 (R)  25 (R)
                                             /
                                           5 (R)
    */

    tree.insert(50, 0);
    tree.insert(25, 0);
    tree.insert(75, 0);
    tree.insert(15, 0);

    tree.insert(5, 0);

    auto* root = tree.get_root_ptr();
    auto* node_25 = root->_left;

    EXPECT_EQ(node_25->_data.first, 15);
    EXPECT_EQ(node_25->_color, Color::Black);

    EXPECT_EQ(node_25->_left->_data.first, 5);
    EXPECT_EQ(node_25->_left->_color, Color::Red);

    EXPECT_EQ(node_25->_right->_data.first, 25);
    EXPECT_EQ(node_25->_right->_color, Color::Red);
}


TEST(TestRBTree, case3_LR) {
    RBTree<int, int> tree;

    /*
                                              ������� 18

             50 (B)                             50 (B)                           50 [B]
            /      \                           /      \                         /      \
         25 (B)   75 (B)                    25 (B)   75 (B)                 18 [B]     75 [R]
         /                                  /                               /    \
      15 (R)                             15 (R)                         25 [R]   75 [R]
                                           \
                                           18 (R)
    */

    tree.insert(50, 0);
    tree.insert(25, 0);
    tree.insert(75, 0);
    tree.insert(15, 0);
    tree.insert(18, 0);

    auto* root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->_data.first, 50);
    EXPECT_EQ(root->_color, Color::Black);

    EXPECT_EQ(root->_right->_data.first, 75);
    EXPECT_EQ(root->_right->_color, Color::Black);

    auto* node_18 = root->_left;
    ASSERT_NE(node_18, nullptr);
    EXPECT_EQ(node_18->_data.first, 18);
    EXPECT_EQ(node_18->_color, Color::Black);

    ASSERT_NE(node_18->_left, nullptr);
    EXPECT_EQ(node_18->_left->_data.first, 15);
    EXPECT_EQ(node_18->_left->_color, Color::Red);

    ASSERT_NE(node_18->_right, nullptr);
    EXPECT_EQ(node_18->_right->_data.first, 25);
    EXPECT_EQ(node_18->_right->_color, Color::Red);
}


TEST(TestRBTree, case4_RL) {
    RBTree<int, int> tree;
    /*
                                          ������� 80                           RL

         50 (B)                             50 (B)                           50 (B)
        /      \                           /      \                         /      \
     25 (B)   75 (B)                    25 (B)   75 (B)                  25 (B)   80 (B)
                 \                                  \                             /    \
                 85 (R)                             85 (R)                     75 (R)  85 (R)
                                                    /
                                                  80 (R)
    */
    tree.insert(50, 0);
    tree.insert(25, 0);
    tree.insert(75, 0);
    tree.insert(85, 0);
    tree.insert(80, 0);

    auto* root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->_data.first, 50);
    EXPECT_EQ(root->_color, Color::Black);

    EXPECT_EQ(root->_left->_data.first, 25);
    EXPECT_EQ(root->_left->_color, Color::Black);

    auto* node_80 = root->_right;
    ASSERT_NE(node_80, nullptr);
    EXPECT_EQ(node_80->_data.first, 80);
    EXPECT_EQ(node_80->_color, Color::Black);

    EXPECT_EQ(node_80->_left->_data.first, 75);
    EXPECT_EQ(node_80->_left->_color, Color::Red);

    EXPECT_EQ(node_80->_right->_data.first, 85);
    EXPECT_EQ(node_80->_right->_color, Color::Red);
}

TEST(TestRBTree, case5_RR) {
    RBTree<int, int> tree;
    /*
                                          ������� 95                           RR

         50 (B)                             50 (B)                           50 (B)
        /      \                           /      \                         /      \
     25 (B)   75 (B)                    25 (B)   75 (B)                  25 (B)   85 (B)
                 \                                  \                             /    \
                 85 (R)                             85 (R)                     75 (R)  95 (R)
                                                      \
                                                      95 (R)
    */
    tree.insert(50, 0);
    tree.insert(25, 0);
    tree.insert(75, 0);
    tree.insert(85, 0);


    tree.insert(95, 0);
    tree.print();

    auto* root = tree.get_root_ptr();
    auto* sub_root = root->_right;

    EXPECT_EQ(sub_root->_data.first, 85);
    EXPECT_EQ(sub_root->_color, Color::Black);

    EXPECT_EQ(sub_root->_left->_data.first, 75);
    EXPECT_EQ(sub_root->_left->_color, Color::Red);

    EXPECT_EQ(sub_root->_right->_data.first, 95);
    EXPECT_EQ(sub_root->_right->_color, Color::Red);
}



TEST(TestRBTree, cascade_recolor_to_LL) {
    RBTree<int, int> tree;

    tree.insert(100, 0);
    tree.insert(50, 0);
    tree.insert(150, 0);
    tree.insert(25, 0);
    tree.insert(75, 0);
    tree.insert(15, 0);

    /*
                           100 [B]
                         /         \
                      50 [R]      150 [B]
                     /      \
                  25 [B]    75 [B]
                 /
              15 [R]


    */
    tree.insert(5, 0);
    tree.print();
    /*
                       100 [Black]
                     /             \
                 50 [Red]           150 [Black]
                /        \
            15 [Black]  75 [Black]
           /          \
        5 [Red]       25 [Red]


    */

    tree.insert(35, 0);
    tree.print();

    /*
                        50 [Black]
                     /              \
                 15 [Red]            100 [Red]
                /        \          /          \
             5 [B]      25 [B]   75 [B]       150 [B]
                          \
                        35 [Red]
    */

    tree.insert(45, 0);
    tree.print();
    /*
                        50 [Black]
                     /              \
                 15 [Red]            100 [Red]
                /        \          /          \
             5 [B]      35 [B]   75 [B]       150 [B]
                       /      \
                    25 [R]    45 [R]
    */
    auto* root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->_data.first, 50);
    EXPECT_EQ(root->_color, Color::Black);

    auto* left_15 = root->_left;
    ASSERT_NE(left_15, nullptr);
    EXPECT_EQ(left_15->_data.first, 15);
    EXPECT_EQ(left_15->_color, Color::Red);

    EXPECT_EQ(left_15->_left->_data.first, 5);
    EXPECT_EQ(left_15->_left->_color, Color::Black);

    auto* node_35 = left_15->_right;
    ASSERT_NE(node_35, nullptr);
    EXPECT_EQ(node_35->_data.first, 35);
    EXPECT_EQ(node_35->_color, Color::Black);

    EXPECT_EQ(node_35->_left->_data.first, 25);
    EXPECT_EQ(node_35->_left->_color, Color::Red);
    EXPECT_EQ(node_35->_right->_data.first, 45);
    EXPECT_EQ(node_35->_right->_color, Color::Red);

    auto* right_100 = root->_right;
    ASSERT_NE(right_100, nullptr);
    EXPECT_EQ(right_100->_data.first, 100);
    EXPECT_EQ(right_100->_color, Color::Red);

    EXPECT_EQ(right_100->_left->_data.first, 75);
    EXPECT_EQ(right_100->_left->_color, Color::Black);
    EXPECT_EQ(right_100->_right->_data.first, 150);
    EXPECT_EQ(right_100->_right->_color, Color::Black);
}

TEST(TestRBTree, ManyElements_OnlyRotations) {
    RBTree<int, int> tree;


    tree.insert(10, 0);
    tree.insert(20, 0);
    tree.insert(30, 0);
    /*
                10 [B]                10 [B]                      20 [B]
                   \                     \                        /      \
                   20 [R]                20 [R]               10 [R]   30 [R]
                                           \
                                            30 [R] (RR)
    */



    tree.insert(5, 0);
    tree.insert(3, 0);

    /*
                    20 [B]                      20 [B]                        20 [B]
                  /      \                    /      \                      /      \
               10 [�]   30 [�]             10 [�]   30 [�]                5 [B]   30 [R]
               /                           /                             /    \
             5 [R]                       5 [R]                         3 [R]  10 [R]
                                        /
                                   3 [R] (LL)
    */

    tree.insert(25, 0);
    tree.insert(22, 0);

    /*
                   20 [B]                  20 [Black]                                20 [B]
                 /      \                  /          \                             /      \
              5 [B]     30 [b]          5 [Black]     30 [Black]                  5 [B]    25 [B]
             /   \        /              /    \         /                        /   \     /    \
           3 [R] 10[R]   25 [R] (LL) 3 [Red]  10 [Red] 25 [Red]               3 [R] 10 [R] 22 [R] 30 [R]
                                                         /
                                                        22 [Red]
    */
    tree.print();
    auto* root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->_data.first, 20);
    EXPECT_EQ(root->_color, Color::Black);

    auto* left_5 = root->_left;
    ASSERT_NE(left_5, nullptr);
    EXPECT_EQ(left_5->_data.first, 5);
    EXPECT_EQ(left_5->_color, Color::Black);
    EXPECT_EQ(left_5->_left->_data.first, 3);
    EXPECT_EQ(left_5->_left->_color, Color::Red);
    EXPECT_EQ(left_5->_right->_data.first, 10);
    EXPECT_EQ(left_5->_right->_color, Color::Red);

    auto* right_25 = root->_right;
    ASSERT_NE(right_25, nullptr);
    EXPECT_EQ(right_25->_data.first, 25);
    EXPECT_EQ(right_25->_color, Color::Black);

    EXPECT_EQ(right_25->_left->_data.first, 22);
    EXPECT_EQ(right_25->_left->_color, Color::Red);
    EXPECT_EQ(right_25->_right->_data.first, 30);
    EXPECT_EQ(right_25->_right->_color, Color::Red);
}

TEST(TestRBTree, strict_layers_no_rotations) {
    RBTree<int, int> tree;

    tree.insert(50, 0);
    tree.insert(25, 0);
    tree.insert(75, 0);
    tree.insert(15, 0);
    tree.insert(35, 0);
    tree.insert(60, 0);
    tree.insert(85, 0);

    /*
               50 [B]
             /        \
          25 [B]     75 [B]
         /    \     /    \
      15 [R] 35 [R] 60 [R] 85 [R]
    */

    auto* root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->_data.first, 50);
    EXPECT_EQ(root->_color, Color::Black);

    auto* layer2_left = root->_left;
    auto* layer2_right = root->_right;

    ASSERT_NE(layer2_left, nullptr);
    ASSERT_NE(layer2_right, nullptr);

    EXPECT_EQ(layer2_left->_data.first, 25);
    EXPECT_EQ(layer2_left->_color, Color::Black);

    EXPECT_EQ(layer2_right->_data.first, 75);
    EXPECT_EQ(layer2_right->_color, Color::Black);

    EXPECT_EQ(layer2_left->_left->_data.first, 15);
    EXPECT_EQ(layer2_left->_left->_color, Color::Red);

    EXPECT_EQ(layer2_left->_right->_data.first, 35);
    EXPECT_EQ(layer2_left->_right->_color, Color::Red);

    EXPECT_EQ(layer2_right->_left->_data.first, 60);
    EXPECT_EQ(layer2_right->_left->_color, Color::Red);

    EXPECT_EQ(layer2_right->_right->_data.first, 85);
    EXPECT_EQ(layer2_right->_right->_color, Color::Red);
}

TEST(TestRBTree, rbtree_big_rotation) {
    RBTree<int, int> tree;

    tree.insert(50, 0);
    tree.print();
    tree.insert(25, 0);
    tree.print();
    tree.insert(100, 0);
    tree.print();
    tree.insert(15, 0);
    tree.print();
    tree.insert(35, 0);
    tree.print();
    tree.insert(10, 0);
    tree.print();
    tree.insert(5, 0);
    tree.print();

    tree.insert(75, 0);
    tree.print();
    tree.insert(150, 0);
    tree.print();
    tree.insert(60, 0);
    tree.print();
    tree.insert(65, 0);
    tree.print();
    tree.insert(160, 0);
    tree.print();
    tree.insert(170, 0);

    /*
                              50 [Black]
                             /            \
                  25 [Red]                    100 [Red]
                 /         \                 /          \
           10 [Black]   35 [Black]     65 [Black]     160 [Black]
           /        \                  /        \      /         \
        5 [Red]   15 [Red]          60 [Red] 75 [Red] 150 [Red] 170 [Red]
    */
    auto* root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->_data.first, 50);
    EXPECT_EQ(root->_color, Color::Black);

    auto* n25 = root->_left;
    ASSERT_NE(n25, nullptr);
    EXPECT_EQ(n25->_data.first, 25);
    EXPECT_EQ(n25->_color, Color::Red);

    EXPECT_EQ(n25->_right->_data.first, 35);
    EXPECT_EQ(n25->_right->_color, Color::Black);

    auto* n10 = n25->_left;
    ASSERT_NE(n10, nullptr);
    EXPECT_EQ(n10->_data.first, 10);
    EXPECT_EQ(n10->_color, Color::Black);
    EXPECT_EQ(n10->_left->_data.first, 5);
    EXPECT_EQ(n10->_left->_color, Color::Red);
    EXPECT_EQ(n10->_right->_data.first, 15);
    EXPECT_EQ(n10->_right->_color, Color::Red);

    auto* n100 = root->_right;
    ASSERT_NE(n100, nullptr);
    EXPECT_EQ(n100->_data.first, 100);
    EXPECT_EQ(n100->_color, Color::Red);

    auto* n65 = n100->_left;
    ASSERT_NE(n65, nullptr);
    EXPECT_EQ(n65->_data.first, 65);
    EXPECT_EQ(n65->_color, Color::Black);
    EXPECT_EQ(n65->_left->_data.first, 60);
    EXPECT_EQ(n65->_left->_color, Color::Red);
    EXPECT_EQ(n65->_right->_data.first, 75);
    EXPECT_EQ(n65->_right->_color, Color::Red);

    auto* n160 = n100->_right;
    ASSERT_NE(n160, nullptr);
    EXPECT_EQ(n160->_data.first, 160);
    EXPECT_EQ(n160->_color, Color::Black);
    EXPECT_EQ(n160->_left->_data.first, 150);
    EXPECT_EQ(n160->_left->_color, Color::Red);
    EXPECT_EQ(n160->_right->_data.first, 170);
    EXPECT_EQ(n160->_right->_color, Color::Red);
}
TEST(TestRBTree, many_elements_only_rotations) {
    RBTree<int, int> tree;

    tree.insert(50, 0);
    tree.insert(20, 0);
    tree.insert(80, 0);
    tree.insert(10, 0);
    tree.insert(15, 0);
    tree.print();
}

TEST(TestRBTree, double_recolor_cascade_) {
    RBTree<int, std::string> tree;

    tree.insert(50, "a");
    tree.insert(20, "b");
    tree.insert(80, "c");
    tree.insert(10, "d");
    tree.insert(30, "e");
    tree.insert(70, "f");
    tree.insert(100, "g");
    tree.insert(5, "h");
    tree.insert(15, "k");
    tree.insert(40, "l");
    tree.insert(110, "m");
    tree.insert(7, "p");
    tree.print();
}


TEST(TestRBTree, rotation_to_rotation) {
    RBTree<int, int> tree;

    tree.insert(100, 0);
    tree.insert(50, 0);
    tree.insert(25, 0);
    tree.print();
    tree.insert(75, 0);
    tree.print();
    tree.insert(15, 0);
    tree.print();
    tree.insert(35, 0);
    tree.insert(65, 0);
    tree.insert(85, 0);

    tree.insert(150, 0);
    tree.insert(125, 0);
    tree.insert(175, 0);

    tree.insert(10, 0);
    tree.print();
    tree.insert(20, 0);


    tree.insert(12, 0);
    tree.print();
    auto* root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->_data.first, 75);
    EXPECT_EQ(root->_color, Color::Black);

    auto* n25 = root->_left;
    ASSERT_NE(n25, nullptr);
    EXPECT_EQ(n25->_data.first, 25);
    EXPECT_EQ(n25->_color, Color::Black);

    auto* n15 = n25->_left;
    ASSERT_NE(n15, nullptr);
    EXPECT_EQ(n15->_data.first, 15);
    EXPECT_EQ(n15->_color, Color::Red);

    auto* n10 = n15->_left;
    ASSERT_NE(n10, nullptr);
    EXPECT_EQ(n10->_data.first, 10);
    EXPECT_EQ(n10->_left, nullptr);

    ASSERT_NE(n10->_right, nullptr);
    EXPECT_EQ(n10->_right->_data.first, 12);
    EXPECT_EQ(n10->_right->_color, Color::Red);

    auto* n50 = n25->_right;
    ASSERT_NE(n50, nullptr);
    EXPECT_EQ(n50->_data.first, 50);
    EXPECT_EQ(n50->_color, Color::Red);

    auto* n100 = root->_right;
    ASSERT_NE(n100, nullptr);
    EXPECT_EQ(n100->_data.first, 100);
    EXPECT_EQ(n100->_color, Color::Black);
}

TEST(TestRBTree, case1_red_sibling) { // �� �������� �� �����
    RBTree<int, int> tree;

    tree.insert(30, 0);
    tree.insert(10, 0);
    tree.insert(50, 0);
    tree.insert(5, 0);
    tree.insert(20, 0);
    tree.insert(15, 0);
    tree.insert(25, 0);
    tree.print();

    /*
                             30 [Black]
                        /                 \
                 10 [Red]                 50 [Black]
                /          \
            5 [Black]      20 [Black]
                          /          \
                      15 [Red]       25 [Red]
    */


    tree.erase(5);

    /*
                              30 [Black]
                             /        \
                       20 [Red]      50 [Black]
                      /        \
               10 [Black]  25 [Black]
                  \
                 15 [Red]
    */
    tree.print();
    auto* root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->_data.first, 30);

    auto* n20 = root->_left;
    ASSERT_NE(n20, nullptr);
    EXPECT_EQ(n20->_data.first, 20);
    EXPECT_EQ(n20->_color, Color::Red);

    ASSERT_NE(n20->_left, nullptr);
    EXPECT_EQ(n20->_left->_data.first, 10);
    EXPECT_EQ(n20->_left->_color, Color::Black);

    ASSERT_NE(n20->_left->_right, nullptr);
    EXPECT_EQ(n20->_left->_right->_data.first, 15);
    EXPECT_EQ(n20->_left->_right->_color, Color::Red);

    ASSERT_NE(n20->_right, nullptr);
    EXPECT_EQ(n20->_right->_data.first, 25);
    EXPECT_EQ(n20->_right->_color, Color::Black);
}

TEST(TestRBTree, erase_case1_red_sibling) { // ���� ������� + ���� 3 � - ��
    RBTree<int, int> tree;
    tree.insert(30, 0);
    tree.insert(10, 0);
    tree.insert(50, 0);
    tree.insert(40, 0);
    tree.insert(70, 0);
    tree.insert(80, 0);

    /*
             30 [B]
            /      \
        10 [B]*    50 [R]
                   /     \
               40 [B]   70 [B]
                           \
                          80 [R]
    */

    tree.print();
    tree.erase(10);
    tree.print();

    /*
                 70 [B]
                /      \
            50 [B]      80 [B]
               /
             30 [�]
               \
             40[R]
    */

    auto* root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->_data.first, 70);
    EXPECT_EQ(root->_color, Color::Black);

    auto* n80 = root->_right;
    ASSERT_NE(n80, nullptr);
    EXPECT_EQ(n80->_data.first, 80);
    EXPECT_EQ(n80->_color, Color::Black);

    auto* n50 = root->_left;
    ASSERT_NE(n50, nullptr);
    EXPECT_EQ(n50->_data.first, 50);
    EXPECT_EQ(n50->_color, Color::Black);

    auto* n30 = n50->_left;
    ASSERT_NE(n30, nullptr);
    EXPECT_EQ(n30->_data.first, 30);
    EXPECT_EQ(n30->_color, Color::Black);

    auto* n40 = n30->_right;
    ASSERT_NE(n40, nullptr);
    EXPECT_EQ(n40->_data.first, 40);
    EXPECT_EQ(n40->_color, Color::Red);
}


TEST(TestRBTree, erase_case2A_black_sibling_red_parent) { //�������� �������
    RBTree<int, int> tree;

    tree.insert(30, 0);
    tree.insert(20, 0);
    tree.insert(40, 0);
    tree.insert(10, 0);
    tree.insert(25, 0);

    /*
                       30 [Black]
                     /            \
                20 [Red]         40 [Black]
               /        \
          10 [Black]* 25 [Black]
    */

    auto* root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);


    tree.print();

    tree.erase(10);

    /*
                30 [Black]
             /            \
        20 [Black]       40 [Red]
             \
            25 [Red]
    */

    tree.print();

    auto* n20 = root->_left;
    ASSERT_NE(n20, nullptr);
    EXPECT_EQ(n20->_data.first, 20);
    EXPECT_EQ(n20->_color, Color::Black);

    auto* n25 = n20->_right;
    ASSERT_NE(n25, nullptr);
    EXPECT_EQ(n25->_data.first, 25);
    EXPECT_EQ(n25->_color, Color::Red);
}

TEST(TestRBTree, erase_case2B_black_sibling_black_children_black_parent) {
    RBTree<int, int> tree;
    tree.insert(20, 0);
    tree.insert(10, 0);
    tree.insert(30, 0);
    tree.insert(5, 0);

    tree.erase(5);

    /*
               20 [B]
              /      \
         10 [B]*   30 [B]
    */
    tree.erase(10);

    /*
               20 [B]
                     \
                    30 [R]
    */
    auto* root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->_data.first, 20);
    EXPECT_EQ(root->_color, Color::Black);

    auto* n30 = root->_right;
    ASSERT_NE(n30, nullptr);
    EXPECT_EQ(n30->_data.first, 30);
    EXPECT_EQ(n30->_color, Color::Red);
    EXPECT_EQ(root->_left, nullptr);
}
TEST(TestRBTree, erase_case3_black_sibling_near_child_red_left) {
    RBTree<int, int> tree;
    tree.insert(20, 0);
    tree.insert(10, 0);
    tree.insert(40, 0);
    tree.insert(30, 0);

    /*
               20 [B]
              /      \
          10 [B]* 40 [B] (���� S)
                    /
                30 [R]
    */
    tree.erase(10);

    /*
               30 [B]
              /      \
          20 [B]    40 [B]
    */
    auto* root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->_data.first, 30);
    EXPECT_EQ(root->_color, Color::Black);

    ASSERT_NE(root->_left, nullptr);
    EXPECT_EQ(root->_left->_color, Color::Black);

    ASSERT_NE(root->_right, nullptr);
    EXPECT_EQ(root->_right->_color, Color::Black);
}
TEST(TestRBTree, erase_case3_black_sibling_near_child_red_right) {
    RBTree<int, int> tree;
    tree.insert(40, 0);
    tree.insert(20, 0);
    tree.insert(50, 0);
    tree.insert(30, 0);

    /*
               40 [B]
              /      \
           20 [B]  50 [B]*
              \
             30 [R]
    */
    tree.erase(50);

    /*
               30 [B]
              /      \
          20 [B]    40 [B]
    */
    auto* root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->_data.first, 30);
    EXPECT_EQ(root->_color, Color::Black);

    ASSERT_NE(root->_left, nullptr);
    EXPECT_EQ(root->_left->_data.first, 20);

    ASSERT_NE(root->_right, nullptr);
    EXPECT_EQ(root->_right->_data.first, 40);
}

TEST(TestRBTree, erase_case4_black_sibling_far_child_red_left) {
    RBTree<int, int> tree;
    tree.insert(20, 0);
    tree.insert(10, 0);
    tree.insert(40, 0);
    tree.insert(50, 0);

    /*
               20 [B]
              /      \
          10 [B]* 40 [B]
                      \
                      50 [R]
    */
    tree.erase(10);

    /*
               40 [B]
              /      \
          20 [B]    50 [B]
    */
    auto* root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->_data.first, 40);
    EXPECT_EQ(root->_color, Color::Black);

    ASSERT_NE(root->_left, nullptr);
    EXPECT_EQ(root->_left->_data.first, 20);
    EXPECT_EQ(root->_left->_color, Color::Black);

    ASSERT_NE(root->_right, nullptr);
    EXPECT_EQ(root->_right->_data.first, 50);
    EXPECT_EQ(root->_right->_color, Color::Black);
}

TEST(TestRBTree, erase_case4_black_sibling_far_child_red_right) {
    RBTree<int, int> tree;
    tree.insert(40, 0);
    tree.insert(20, 0);
    tree.insert(50, 0);
    tree.insert(10, 0);

    /*
               40 [B]
              /      \
          20 [B]    50 [B]*
          /
      10 [R]
    */
    tree.erase(50);

    /*
               20 [B]
              /      \
          10 [B]    40 [B]
    */
    auto* root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->_data.first, 20);
    EXPECT_EQ(root->_color, Color::Black);

    ASSERT_NE(root->_left, nullptr);
    EXPECT_EQ(root->_left->_data.first, 10);
    EXPECT_EQ(root->_left->_color, Color::Black);

    ASSERT_NE(root->_right, nullptr);
    EXPECT_EQ(root->_right->_data.first, 40);
    EXPECT_EQ(root->_right->_color, Color::Black);
}




TEST(TestRBTree, rbtree_big_rotation_root) {
    RBTree<int, int> tree;

    tree.insert(50, 0);
    tree.insert(25, 0);
    tree.insert(100, 0);
    tree.insert(15, 0);
    tree.insert(35, 0);
    tree.insert(5, 0);
    tree.insert(75, 0);
    tree.insert(150, 0);
    tree.insert(60, 0);
    tree.insert(65, 0);
    tree.insert(160, 0);
    tree.insert(170, 0);


    /*

                              50 [Black]
                             /            \
                  25 [Red]                    100 [Red]
                 /         \                 /          \
             5 [Black]   35 [Black]    65 [Black]     160 [Black]
             \                            /        \      /         \
           15 [Red]                    60 [Red] 75 [Red] 150 [Red] 170 [Red]
    */

    tree.erase(50);

    tree.print();

    auto* root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->_data.first, 35);
    EXPECT_EQ(root->_color, Color::Black);

    auto* left_child = root->_left;
    ASSERT_NE(left_child, nullptr);
    EXPECT_EQ(left_child->_data.first, 15);
    EXPECT_EQ(left_child->_color, Color::Red);

    ASSERT_NE(left_child->_left, nullptr);
    EXPECT_EQ(left_child->_left->_data.first, 5);
    EXPECT_EQ(left_child->_left->_color, Color::Black);
    EXPECT_EQ(left_child->_left->_left, nullptr);
    EXPECT_EQ(left_child->_left->_right, nullptr);

    ASSERT_NE(left_child->_right, nullptr);
    EXPECT_EQ(left_child->_right->_data.first, 25);
    EXPECT_EQ(left_child->_right->_color, Color::Black);
    EXPECT_EQ(left_child->_right->_left, nullptr);
    EXPECT_EQ(left_child->_right->_right, nullptr);

    auto* right_child = root->_right;
    ASSERT_NE(right_child, nullptr);
    EXPECT_EQ(right_child->_data.first, 100);
    EXPECT_EQ(right_child->_color, Color::Red);

    auto* node_65 = right_child->_left;
    ASSERT_NE(node_65, nullptr);
    EXPECT_EQ(node_65->_data.first, 65);
    EXPECT_EQ(node_65->_color, Color::Black);

    ASSERT_NE(node_65->_left, nullptr);
    EXPECT_EQ(node_65->_left->_data.first, 60);
    EXPECT_EQ(node_65->_left->_color, Color::Red);
    EXPECT_EQ(node_65->_left->_left, nullptr);
    EXPECT_EQ(node_65->_left->_right, nullptr);

    ASSERT_NE(node_65->_right, nullptr);
    EXPECT_EQ(node_65->_right->_data.first, 75);
    EXPECT_EQ(node_65->_right->_color, Color::Red);
    EXPECT_EQ(node_65->_right->_left, nullptr);
    EXPECT_EQ(node_65->_right->_right, nullptr);

    auto* node_160 = right_child->_right;
    ASSERT_NE(node_160, nullptr);
    EXPECT_EQ(node_160->_data.first, 160);
    EXPECT_EQ(node_160->_color, Color::Black);

    ASSERT_NE(node_160->_left, nullptr);
    EXPECT_EQ(node_160->_left->_data.first, 150);
    EXPECT_EQ(node_160->_left->_color, Color::Red);
    EXPECT_EQ(node_160->_left->_left, nullptr);
    EXPECT_EQ(node_160->_left->_right, nullptr);

    ASSERT_NE(node_160->_right, nullptr);
    EXPECT_EQ(node_160->_right->_data.first, 170);
    EXPECT_EQ(node_160->_right->_color, Color::Red);
    EXPECT_EQ(node_160->_right->_left, nullptr);
    EXPECT_EQ(node_160->_right->_right, nullptr);
}
TEST(TestRBTree, double_black) {
    RBTree<int, int> tree;

    tree.insert(50, 0);
    tree.insert(30, 0);
    tree.insert(20, 0);
    tree.insert(25, 0);
    tree.insert(45, 0);
    tree.insert(55, 0);
    /*
        30 [B]
       /      \
    20 [B]    50 [B]
     \         /   \
     25 [R]   45[R]  55[R]
     
     */

    tree.erase(20); 
    tree.print();
    /*
           30 [B]
          /      \
       25 [B]    50 [B]
                  /   \
               45[R]  55[R]

    */
    EXPECT_NE(tree.get_root_ptr(), nullptr);
}

TEST(TestRBTree, rbtree_big_rotation_black_wiht_red_child) {
    RBTree<int, int> tree;

    tree.insert(50, 0);
    tree.insert(25, 0);
    tree.insert(100, 0);
    tree.insert(15, 0);
    tree.insert(35, 0);
    tree.insert(10, 0);
    tree.insert(5, 0);
    tree.insert(75, 0);
    tree.insert(150, 0);
    tree.insert(60, 0);
    tree.insert(65, 0);
    tree.insert(160, 0);
    tree.insert(170, 0);


    /*
                              50 [Black]
                             /            \
                  25 [Red]                    100 [Red]
                 /         \                 /          \
           10 [Black]   35 [Black]     65 [Black]     160 [Black]
           /        \                  /        \      /         \
        5 [Red]   15 [Red]          60 [Red] 75 [Red] 150 [Red] 170 [Red]
    */

    tree.erase(10);

    /*

                              50 [Black]
                             /            \
                  25 [Red]                    100 [Red]
                 /         \                 /          \
             5 [Black]   35 [Black]    65 [Black]     160 [Black]
             \                           /        \      /         \
           15 [Red]                    60 [Red] 75 [Red] 150 [Red] 170 [Red]
    */

    tree.print();

    auto* root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->_data.first, 50);
    EXPECT_EQ(root->_color, Color::Black);

    auto* node_25 = root->_left;
    ASSERT_NE(node_25, nullptr);
    EXPECT_EQ(node_25->_data.first, 25);
    EXPECT_EQ(node_25->_color, Color::Red);

    auto* node_5 = node_25->_left;
    ASSERT_NE(node_5, nullptr);
    EXPECT_EQ(node_5->_data.first, 5);
    EXPECT_EQ(node_5->_color, Color::Black);

    ASSERT_NE(node_5->_right, nullptr);
    EXPECT_EQ(node_5->_right->_data.first, 15);
    EXPECT_EQ(node_5->_right->_color, Color::Red);

    EXPECT_EQ(node_5->_left, nullptr);

    auto* node_35 = node_25->_right;
    ASSERT_NE(node_35, nullptr);
    EXPECT_EQ(node_35->_data.first, 35);
    EXPECT_EQ(node_35->_color, Color::Black);

    auto* node_100 = root->_right;
    ASSERT_NE(node_100, nullptr);
    EXPECT_EQ(node_100->_data.first, 100);
    EXPECT_EQ(node_100->_color, Color::Red);

    auto* node_65 = node_100->_left;
    ASSERT_NE(node_65, nullptr);
    EXPECT_EQ(node_65->_data.first, 65);
    EXPECT_EQ(node_65->_color, Color::Black);

    ASSERT_NE(node_65->_left, nullptr);
    EXPECT_EQ(node_65->_left->_data.first, 60);
    EXPECT_EQ(node_65->_left->_color, Color::Red);

    ASSERT_NE(node_65->_right, nullptr);
    EXPECT_EQ(node_65->_right->_data.first, 75);
    EXPECT_EQ(node_65->_right->_color, Color::Red);

    auto* node_160 = node_100->_right;
    ASSERT_NE(node_160, nullptr);
    EXPECT_EQ(node_160->_data.first, 160);
    EXPECT_EQ(node_160->_color, Color::Black);


    ASSERT_NE(node_160->_left, nullptr);
    EXPECT_EQ(node_160->_left->_data.first, 150);
    EXPECT_EQ(node_160->_left->_color, Color::Red);

    ASSERT_NE(node_160->_right, nullptr);
    EXPECT_EQ(node_160->_right->_data.first, 170);
    EXPECT_EQ(node_160->_right->_color, Color::Red);
}

TEST(TestRBTree, SequentialInsertFindErase100) {
    RBTree<int, std::string> tree;
    for (int i = 0; i < 100; ++i) {
        EXPECT_NO_THROW(tree.insert(i, std::to_string(i)));
    }
    for (int i = 0; i < 100; ++i) {
        EXPECT_NO_THROW(tree.find(i));
    }
    for (int i = 0; i < 100; ++i) {
        EXPECT_NO_THROW(tree.erase(i));
    }
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestRBTree, SequentialInsertFindErase100WithPolynom) {
    RBTree<int, Polynom> tree;
    for (int i = 0; i < 100; ++i) {
        Polynom p;
        p.add_monom(Monom(static_cast<double>(i + 1), i % 5, (i + 1) % 4, (i + 2) % 3));
        EXPECT_NO_THROW(tree.insert(i, p));
    }
    for (int i = 0; i < 100; ++i) {
        EXPECT_NO_THROW(tree.find(i));
    }
    for (int i = 0; i < 100; ++i) {
        EXPECT_NO_THROW(tree.erase(i));
    }
    EXPECT_TRUE(tree.is_empty());
}
