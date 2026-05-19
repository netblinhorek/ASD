#include <gtest/gtest.h>
#include <string>
#include "../lib_AVLTree/avltree.h"

TEST(TestAVLTree, test_default_constructor_empty_tree) {
    AVLTree<int, std::string> tree;
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestAVLTree, test_insert_no_throw) {
    AVLTree<int, std::string> tree;

    EXPECT_NO_THROW({
        tree.insert(1, "one");
        tree.insert(2, "two");
        tree.insert(3, "three");
        tree.insert(4, "four");
        tree.insert(5, "five");
        });

    EXPECT_FALSE(tree.is_empty());
}

TEST(TestAVLTree, test_clear_empty_tree) {
    AVLTree<int, std::string> tree;
    EXPECT_NO_THROW(tree.clear());
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestAVLTree, test_clear_single_element) {
    AVLTree<int, std::string> tree;
    tree.insert(1, "one");
    tree.clear();
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestAVLTree, test_find_empty_throws) {
    AVLTree<int, std::string> tree;
    EXPECT_THROW(tree.find(42), std::out_of_range);
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestAVLTree, test_find_negative_keys) {
    AVLTree<int, std::string> tree;
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

    std::string* value_ptr = tree.find(5);
    ASSERT_NE(value_ptr, nullptr);
    EXPECT_EQ(*value_ptr, "five");
}

TEST(TestAVLTree, Erase_Empty_Throws) {
    AVLTree<int, std::string> tree;
    EXPECT_THROW(tree.erase(42), std::out_of_range);
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestAVLTree, erase_root_single_element_empty) {
    AVLTree<int, std::string> tree;
    tree.insert(42, "answer");

    EXPECT_NO_THROW(tree.erase(42));
    EXPECT_TRUE(tree.is_empty());
    EXPECT_THROW(tree.find(42), std::out_of_range);
}

TEST(TestAVLTree, test_erase_root) {
    AVLTree<int, std::string> tree;
    tree.insert(1, "one");
    tree.insert(2, "two");
    tree.insert(3, "three");

    EXPECT_NO_THROW(tree.erase(1));
    EXPECT_THROW(tree.find(1), std::out_of_range);
    EXPECT_NO_THROW(tree.find(2));
    EXPECT_NO_THROW(tree.find(3));
    EXPECT_NE(tree.find(2), nullptr);
    EXPECT_NE(tree.find(3), nullptr);

    std::string* value_ptr = tree.find(2);
    ASSERT_NE(value_ptr, nullptr);
    EXPECT_EQ(*value_ptr, "two");
}

TEST(TestAVLTree, test_erase_non_existent_throws) {
    AVLTree<int, std::string> tree;
    tree.insert(1, "one");
    tree.insert(2, "two");

    EXPECT_THROW(tree.erase(999), std::out_of_range);
    EXPECT_NO_THROW(tree.find(1));
    EXPECT_NO_THROW(tree.find(2));
    EXPECT_NE(tree.find(1), nullptr);
    EXPECT_NE(tree.find(2), nullptr);
}

TEST(TestAVLTree, test_erase_empty_tree_throws) {
    AVLTree<int, std::string> tree;
    EXPECT_THROW(tree.erase(42), std::out_of_range);
}

TEST(TestAVLTree, test_find_after_erase_throws) {
    AVLTree<int, std::string> tree;
    tree.insert(10, "ten");
    tree.insert(20, "twenty");
    tree.erase(10);

    EXPECT_THROW(tree.find(10), std::out_of_range);
    EXPECT_NO_THROW(tree.find(20));
    EXPECT_NE(tree.find(20), nullptr);
}

TEST(TestAVLTree, test_erase_and_find_remaining) {
    AVLTree<int, std::string> tree;
    tree.insert(100, "hundred");
    tree.insert(200, "two hundred");
    tree.insert(300, "three hundred");

    tree.erase(200);

    EXPECT_THROW(tree.find(200), std::out_of_range);
    EXPECT_NO_THROW(tree.find(100));
    EXPECT_NO_THROW(tree.find(300));
    EXPECT_NE(tree.find(100), nullptr);
    EXPECT_NE(tree.find(300), nullptr);

    std::string* value_ptr1 = tree.find(100);
    std::string* value_ptr3 = tree.find(300);
    ASSERT_NE(value_ptr1, nullptr);
    ASSERT_NE(value_ptr3, nullptr);
    EXPECT_EQ(*value_ptr1, "hundred");
    EXPECT_EQ(*value_ptr3, "three hundred");
}


TEST(TestAVLTree, test_LL_balance_rotation) {
    AVLTree<int, std::string> tree;

    tree.insert(30, "thirty");
    tree.insert(20, "twenty");

    EXPECT_NO_THROW(tree.insert(10, "ten"));

    //           30                      20
    //          /                       /  \
    //        20                       10  30
    //       /
    //     10

    ASSERT_NE(tree.find(20), nullptr);
    EXPECT_EQ(*tree.find(20), "twenty");

    ASSERT_NE(tree.find(10), nullptr);
    EXPECT_EQ(*tree.find(10), "ten");

    ASSERT_NE(tree.find(30), nullptr);
    EXPECT_EQ(*tree.find(30), "thirty");
}

TEST(TestAVLTree, test_RR_balance_rotation) {
    AVLTree<int, std::string> tree;

    tree.insert(10, "ten");
    tree.insert(20, "twenty");

    EXPECT_NO_THROW(tree.insert(30, "thirty"));

    //     10                                 20
    //       \                               /  \
    //       20                            10   30
    //         \
    //         30

    ASSERT_NE(tree.find(20), nullptr);
    EXPECT_EQ(*tree.find(20), "twenty");

    ASSERT_NE(tree.find(10), nullptr);
    EXPECT_EQ(*tree.find(10), "ten");

    ASSERT_NE(tree.find(30), nullptr);
    EXPECT_EQ(*tree.find(30), "thirty");
}

TEST(TestAVLTree, test_LR_balance_rotation) {
    AVLTree<int, std::string> tree;

    tree.insert(30, "thirty");
    tree.insert(10, "ten");
   
    EXPECT_NO_THROW(tree.insert(20, "twenty"));

    //           30                         30                              20
    //          /                          /                               /  \
    //        10                         20                              10    30
    //          \                       /
    //          20                    10

    ASSERT_NE(tree.find(20), nullptr);
    EXPECT_EQ(*tree.find(20), "twenty");

    ASSERT_NE(tree.find(10), nullptr);
    EXPECT_EQ(*tree.find(10), "ten");

    ASSERT_NE(tree.find(30), nullptr);
    EXPECT_EQ(*tree.find(30), "thirty");
}

TEST(TestAVLTree, test_RL_balance_rotation) {
    AVLTree<int, std::string> tree;

    tree.insert(10, "ten");
    tree.insert(30, "thirty");
    
    EXPECT_NO_THROW(tree.insert(20, "twenty"));

    //     10                             10                                20
    //       \                              \                              /  \
    //       30                             20                           10    30
    //       /                                \
    //     20                                 30

    ASSERT_NE(tree.find(20), nullptr);
    EXPECT_EQ(*tree.find(20), "twenty");

    ASSERT_NE(tree.find(10), nullptr);
    EXPECT_EQ(*tree.find(10), "ten");

    ASSERT_NE(tree.find(30), nullptr);
    EXPECT_EQ(*tree.find(30), "thirty");
}


TEST(TestAVLTree, test_erase_node_with_two_children_and_rebalance) {
    AVLTree<int, std::string> tree;
    tree.insert(50, "50");
    tree.insert(30, "30");
    tree.insert(70, "70");
    tree.insert(20, "20");
    tree.insert(40, "40");
    tree.insert(60, "60");
    tree.insert(80, "80");
    tree.insert(35, "35");
    tree.insert(45, "45");
    tree.insert(55, "55");
    tree.insert(65, "65");
    //          50
    //        /    \
    //     30        70
    //    /  \      /  \
    //   20  40    60   80
    //      /  \  /  \
    //     35  45 55 65

    EXPECT_NO_THROW(tree.erase(30));
   /*           50
              /    \
            40      70
           /  \    /  \
          20  45  60  80
           \
            35
            */
    EXPECT_THROW(tree.find(30), std::out_of_range);
    EXPECT_NO_THROW(tree.find(35));
    EXPECT_NO_THROW(tree.find(20));
    EXPECT_NO_THROW(tree.find(40));
    EXPECT_NO_THROW(tree.find(45));
    AVLNode<int, std::string>* root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->_data.first, 50);
    EXPECT_EQ(root->_parent, nullptr);

    AVLNode<int, std::string>* n40 = root->_left;
    ASSERT_NE(n40, nullptr);
    EXPECT_EQ(n40->_data.first, 40);
    EXPECT_EQ(n40->_parent, root);

    AVLNode<int, std::string>* n20 = n40->_left;
    ASSERT_NE(n20, nullptr);
    EXPECT_EQ(n20->_data.first, 20);
    EXPECT_EQ(n20->_parent, n40);

    AVLNode<int, std::string>* n35 = n20->_right;
    ASSERT_NE(n35, nullptr);
    EXPECT_EQ(n35->_data.first, 35);
    EXPECT_EQ(n35->_parent, n20);

    AVLNode<int, std::string>* n45 = n40->_right;
    ASSERT_NE(n45, nullptr);
    EXPECT_EQ(n45->_data.first, 45);
    EXPECT_EQ(n45->_parent, n40);
    EXPECT_EQ(n35->_height, 1);
    EXPECT_EQ(n45->_height, 1);
    EXPECT_EQ(n20->_height, 2);

    EXPECT_EQ(n40->_height, 3);
}


TEST(TestAVLTree, erase_leaf_node) {
    AVLTree<int, std::string> tree;
    tree.insert(50, "50");
    tree.insert(20, "20");
    tree.insert(70, "70");
       //   50 
       //  /  \
       // 20   70
    EXPECT_NO_THROW(tree.erase(20));

   /* 50 
        \
        70   */

    AVLNode<int, std::string>* root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->_data.first, 50);
    EXPECT_EQ(root->_left, nullptr);
    EXPECT_EQ(root->_height, 2); 
    EXPECT_EQ(root->_right->_data.first, 70);
}
TEST(TestAVLTree, erase_node_with_one_child) {
    AVLTree<int, std::string> tree;
    tree.insert(50, "50");
    tree.insert(30, "30");
    tree.insert(70, "70");
    tree.insert(80, "80");

    /*   50 
        /  \
       30   70
        \
        80
               */

    EXPECT_NO_THROW(tree.erase(70));
   /*   50 (h:2)
       /  \
      30   80
               */

    AVLNode<int, std::string>* root = tree.get_root_ptr();
    EXPECT_EQ(root->_right->_data.first, 80);
    EXPECT_EQ(root->_right->_parent, root);
    EXPECT_EQ(root->_height, 2);
}
TEST(TestAVLTree, erase_root_complex) {
    AVLTree<int, std::string> tree;
    tree.insert(50, "50");
    tree.insert(30, "30");
    tree.insert(70, "70");
    tree.insert(20, "20");
    tree.insert(40, "40");
    tree.insert(60, "60");
   /*    50 
       /    \
      30     70
     /  \    /
    20  40  60     */
    EXPECT_NO_THROW(tree.erase(50));
   /*       40 
          /   \
        30      70
        /       /
       20     60     */
    AVLNode<int, std::string>* root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->_data.first, 40);
    EXPECT_EQ(root->_parent, nullptr);

    EXPECT_EQ(root->_left->_data.first, 30);
    EXPECT_EQ(root->_right->_data.first, 70);

    EXPECT_EQ(root->_left->_left->_data.first, 20);
    EXPECT_EQ(root->_left->_left->_parent->_data.first, 30);
}
TEST(TestAVLTreeFind, find_in_empty_tree_throws) {
    AVLTree<int, std::string> tree;

    EXPECT_THROW(tree.find(10), std::out_of_range);
}

TEST(TestAVLTreeFind, find_non_existent_key_throws) {
    AVLTree<int, std::string> tree;
    tree.insert(10, "ten");
    tree.insert(20, "twenty");

    EXPECT_THROW(tree.find(15), std::out_of_range);
}

TEST(TestAVLTreeFind, find_after_rebalancing) {
    AVLTree<int, std::string> tree;

    tree.insert(10, "ten");
    tree.insert(20, "twenty");
    tree.insert(30, "thirty");

    EXPECT_NO_THROW({
        EXPECT_EQ(*tree.find(10), "ten");
        EXPECT_EQ(*tree.find(20), "twenty");
        EXPECT_EQ(*tree.find(30), "thirty");
        });
}

TEST(TestAVLTree, test_erase_triple_cascade_rotation_fixed) {
    AVLTree<int, std::string> tree;

    tree.insert(40, "40");
    tree.insert(20, "20");
    tree.insert(60, "60");
    tree.insert(15, "15");
    tree.insert(25, "25");
    tree.insert(50, "50");
    tree.insert(70, "70");
    tree.insert(5, "5");
    tree.insert(45, "45");
    tree.insert(55, "55");
    tree.insert(65, "65");
    tree.insert(80, "80");
    tree.insert(75, "75");

    AVLNode<int, std::string>* root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->_data.first, 40);
    
     /*
                        40 
                     /       \
                   20         60 
                 /    \      /   \
               15      25  50    70 
              /           /  \   / \
             5           45  55 65 80
                                   /
                                   75
     
     */



    EXPECT_NO_THROW(tree.erase(25));
    /*
                        40
                     /       \
                   20         60
                 /           /   \
               15          50    70
              /           /  \   / \
             5           45  55 65 80
                                   /
                                   75

     */
    EXPECT_THROW(tree.find(25), std::out_of_range);
    EXPECT_NO_THROW(tree.find(40));
    EXPECT_NO_THROW(tree.find(60));
    EXPECT_NO_THROW(tree.find(75));


    root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->_data.first, 60);
    EXPECT_EQ(root->_parent, nullptr);

    AVLNode<int, std::string>* n40 = root->_left;
    AVLNode<int, std::string>* n70 = root->_right;

    ASSERT_NE(n40, nullptr);
    EXPECT_EQ(n40->_data.first, 40);
    EXPECT_EQ(n40->_parent, root);

    ASSERT_NE(n70, nullptr);
    EXPECT_EQ(n70->_data.first, 70);
    EXPECT_EQ(n70->_parent, root);

    AVLNode<int, std::string>* n15 = n40->_left;
    AVLNode<int, std::string>* n50 = n40->_right;

    ASSERT_NE(n15, nullptr);
    EXPECT_EQ(n15->_data.first, 15);
    EXPECT_EQ(n15->_parent, n40);

    ASSERT_NE(n50, nullptr);
    EXPECT_EQ(n50->_data.first, 50);
    EXPECT_EQ(n50->_parent, n40);

    AVLNode<int, std::string>* n65 = n70->_left;
    AVLNode<int, std::string>* n80 = n70->_right;

    ASSERT_NE(n65, nullptr);
    EXPECT_EQ(n65->_data.first, 65);
    EXPECT_EQ(n65->_parent, n70);
    EXPECT_EQ(n65->_left, nullptr);
    EXPECT_EQ(n65->_right, nullptr);

    ASSERT_NE(n80, nullptr);
    EXPECT_EQ(n80->_data.first, 80);
    EXPECT_EQ(n80->_parent, n70);
    EXPECT_EQ(n80->_right, nullptr);

    AVLNode<int, std::string>* n5 = n15->_left;
    AVLNode<int, std::string>* n20 = n15->_right;

    ASSERT_NE(n5, nullptr);
    EXPECT_EQ(n5->_data.first, 5);
    EXPECT_EQ(n5->_parent, n15);
    EXPECT_EQ(n5->_left, nullptr);
    EXPECT_EQ(n5->_right, nullptr);

    ASSERT_NE(n20, nullptr);
    EXPECT_EQ(n20->_data.first, 20);
    EXPECT_EQ(n20->_parent, n15);
    EXPECT_EQ(n20->_left, nullptr);
    EXPECT_EQ(n20->_right, nullptr); 

    AVLNode<int, std::string>* n45 = n50->_left;
    AVLNode<int, std::string>* n55 = n50->_right;

    ASSERT_NE(n45, nullptr);
    EXPECT_EQ(n45->_data.first, 45);
    EXPECT_EQ(n45->_parent, n50);
    EXPECT_EQ(n45->_left, nullptr);
    EXPECT_EQ(n45->_right, nullptr);

    ASSERT_NE(n55, nullptr);
    EXPECT_EQ(n55->_data.first, 55);
    EXPECT_EQ(n55->_parent, n50);
    EXPECT_EQ(n55->_left, nullptr);
    EXPECT_EQ(n55->_right, nullptr);

    AVLNode<int, std::string>* n75 = n80->_left;

    ASSERT_NE(n75, nullptr);
    EXPECT_EQ(n75->_data.first, 75);
    EXPECT_EQ(n75->_parent, n80);
    EXPECT_EQ(n75->_left, nullptr);
    EXPECT_EQ(n75->_right, nullptr);

    /*
    
                             60 
                          /      \
                        40        70 
                       /  \      /  \
                     15    50   65   80
                    /  \  /  \      /
                   5   20 45 55    75
    */

}



