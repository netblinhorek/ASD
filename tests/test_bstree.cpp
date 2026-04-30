#include <gtest/gtest.h>
#include "../lib_BSTree/bstree.h"


TEST(TestBSTree, test_default_constructor_empty_bstree) {
    BSTree<int, std::string> bstree;
    EXPECT_TRUE(bstree.is_empty());
}

TEST(TestBSTree, test_insert_no_throw) {
    BSTree<int, std::string> bstree;

    EXPECT_NO_THROW({
        bstree.insert(1, "1");
        bstree.insert(2, "2");
        bstree.insert(3, "3");
        bstree.insert(4, "4");
        bstree.insert(5, "5");
        });

    EXPECT_FALSE(bstree.is_empty());
}

TEST(TestBSTree, test_bstree_print_dlcr_with_elements_no_throw) {
    BSTree<int, std::string> bstree;
    bstree.insert(6, "6");
    bstree.insert(4, "4");
    bstree.insert(9, "9");
    bstree.insert(1, "1");
    bstree.insert(5, "5");
    bstree.insert(7, "7");
    bstree.insert(12, "12");

    EXPECT_NO_THROW(bstree.print_dlcr());
}


TEST(TestBSTree, test_bstree_print_dlrc_with_elements_no_throw) {
    BSTree<int, std::string> bstree;
    bstree.insert(6, "6");
    bstree.insert(4, "4");
    bstree.insert(9, "9");
    bstree.insert(1, "1");
    bstree.insert(5, "5");
    bstree.insert(7, "7");
    bstree.insert(12, "12");

    EXPECT_NO_THROW(bstree.print_dlcr());
}
TEST(TestBSTree, test_bstree_print_dlrc_with_elements_throw) {
    BSTree<int, std::string> bstree;
    bstree.insert(6, "6");
    bstree.insert(1, "1");
    bstree.insert(4, "4");
    bstree.insert(9, "9");
    bstree.insert(5, "5");
    bstree.insert(7, "7");
    bstree.insert(12, "12");

    EXPECT_NO_THROW(bstree.print_dlcr());
}
TEST(BSTreeInsertTest, test_bstree_throws_when_insert_duplicate_key) {
    BSTree<int, std::string> tree;

    tree.insert(50, "fifty");
    tree.insert(25, "twenty-five");
    tree.insert(75, "seventy-five");
    tree.insert(10, "ten");
    tree.insert(30, "thirty");
    tree.insert(60, "sixty");
    tree.insert(90, "ninety");

    EXPECT_THROW(tree.insert(25, "25"), std::logic_error);
    EXPECT_THROW(tree.insert(90, "90"), std::logic_error);
    EXPECT_THROW(tree.insert(10, "10"), std::logic_error);
    EXPECT_THROW(tree.insert(50, "50"), std::logic_error);
}
TEST(TestBSTree, test_bstree_find_after_insert_multiple_elements) {
    BSTree<int, std::string> bstree;

    bstree.insert(6, "6");
    bstree.insert(4, "4");
    bstree.insert(9, "9");
    bstree.insert(1, "1");
    bstree.insert(5, "5");
    bstree.insert(7, "7");
    bstree.insert(12, "12");

    EXPECT_EQ(*bstree.find(1), "1");
    EXPECT_EQ(*bstree.find(4), "4");
    EXPECT_EQ(*bstree.find(5), "5");
    EXPECT_EQ(*bstree.find(6), "6");
    EXPECT_EQ(*bstree.find(7), "7");
    EXPECT_EQ(*bstree.find(9), "9");
    EXPECT_EQ(*bstree.find(12), "12");

   
}

TEST(TestBSTree, test_bstree_find_after_clear_returns_nullptr) {
    BSTree<int, std::string> bstree;

    bstree.insert(10, "ten");
    bstree.insert(20, "twenty");

    ASSERT_NO_THROW(bstree.find(10));

    bstree.clear();

    EXPECT_THROW(bstree.find(10), std::out_of_range);
    EXPECT_THROW(bstree.find(20), std::out_of_range);
}

TEST(TestBSTree, test_bstree_erase_parent) {
    BSTree<int, std::string> bstree;

    bstree.insert(6, "6");
    bstree.insert(4, "4");
    bstree.insert(9, "9");
    bstree.insert(1, "1");
    bstree.insert(5, "5");
    bstree.insert(7, "7");
    bstree.insert(12, "12");

    bstree.erase(4);
    bstree.print_dlcr();
  
}
TEST(TestBSTree, test_bstree_erase_root) {
    BSTree<int, std::string> bstree;

    bstree.insert(6, "6");
    bstree.insert(4, "4");
    bstree.insert(9, "9");
    bstree.insert(1, "1");
    bstree.insert(5, "5");
    bstree.insert(7, "7");
    bstree.insert(12, "12");

    bstree.erase(6);
    bstree.print_dlcr();

}
TEST(TestBSTree, test_bstree_erase_sheet) {
    BSTree<int, std::string> bstree;

    bstree.insert(6, "6");
    bstree.insert(4, "4");
    bstree.insert(9, "9");
    bstree.insert(1, "1");
    bstree.insert(5, "5");
    bstree.insert(7, "7");
    bstree.insert(12, "12");

    bstree.erase(12);
    bstree.erase(1);
    bstree.print_dlcr();
}
TEST(TestBSTree, test_bstree_structure_after_operations) {
    BSTree<int, std::string> bstree;

    bstree.insert(50, "fifty");
    bstree.insert(25, "twenty-five");
    bstree.insert(75, "seventy-five");
    bstree.insert(10, "ten");
    bstree.insert(30, "thirty");
    bstree.insert(60, "sixty");
    bstree.insert(90, "ninety");

    EXPECT_NO_THROW(bstree.find(50));
    EXPECT_NO_THROW(bstree.find(25));
    EXPECT_NO_THROW(bstree.find(75));
    EXPECT_NO_THROW(bstree.find(10));
    EXPECT_NO_THROW(bstree.find(30));
    EXPECT_NO_THROW(bstree.find(60));
    EXPECT_NO_THROW(bstree.find(90));

    EXPECT_EQ(*bstree.find(50), "fifty");
    EXPECT_EQ(*bstree.find(25), "twenty-five");
    EXPECT_EQ(*bstree.find(75), "seventy-five");
    EXPECT_EQ(*bstree.find(10), "ten");
    EXPECT_EQ(*bstree.find(30), "thirty");
    EXPECT_EQ(*bstree.find(60), "sixty");
    EXPECT_EQ(*bstree.find(90), "ninety");

    std::cout << "Tree after insertions: ";
    bstree.print_dlcr();

    bstree.erase(25);

    EXPECT_THROW(bstree.find(25), std::out_of_range);
    EXPECT_NO_THROW(bstree.find(50));
    EXPECT_NO_THROW(bstree.find(75));
    EXPECT_NO_THROW(bstree.find(10));
    EXPECT_NO_THROW(bstree.find(30));
    EXPECT_NO_THROW(bstree.find(60));
    EXPECT_NO_THROW(bstree.find(90));

    std::cout << "Tree after erasing 25: ";
    bstree.print_dlcr();

    bstree.erase(10);

    EXPECT_THROW(bstree.find(10), std::out_of_range);
    EXPECT_NO_THROW(bstree.find(50));
    EXPECT_NO_THROW(bstree.find(30));
    EXPECT_NO_THROW(bstree.find(60));
    EXPECT_NO_THROW(bstree.find(90));

    std::cout << "Tree after erasing 10: ";
    bstree.print_dlcr();

    EXPECT_FALSE(bstree.is_empty());

    bstree.print_dlcr();
}
TEST(TestBSTree, test_erase_nonexistent_key_throws_exception) {
    BSTree<int, std::string> tree;

    tree.insert(10, "ten");
    tree.insert(20, "twenty");
    tree.insert(30, "thirty");
    tree.insert(40, "forty");
    tree.insert(50, "fifty");

    EXPECT_THROW(tree.erase(999), std::out_of_range);
    EXPECT_THROW(tree.erase(15), std::out_of_range);
    EXPECT_THROW(tree.erase(100), std::out_of_range);

    EXPECT_NO_THROW(tree.erase(10));

}
TEST(TestBSTree, test_erase_root) {
    BSTree<int, std::string> tree;
    tree.insert(50, "50");
    tree.insert(30, "30");
    tree.insert(70, "70");
    tree.insert(20, "20");
    tree.insert(40, "40");
    tree.insert(60, "60");
    tree.insert(80, "80");

    //          50
    //         /  \
    //       30    70
    //      /  \   / \
    //     20  40 60 80

    EXPECT_NO_THROW(tree.erase(50));

    //          40
    //         /  \
    //       30    70
    //      /     / \
    //     20    60 80

    ASSERT_NE(tree.get_root_ptr(), nullptr);

    EXPECT_EQ(tree.get_root_ptr()->_data.first, 40);
    EXPECT_EQ(tree.get_root_ptr()->_data.second, "40");

    ASSERT_NE(tree.get_root_ptr()->_left, nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_left->_data.first, 30);

    ASSERT_NE(tree.get_root_ptr()->_left->_left, nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_left->_left->_data.first, 20);

    EXPECT_EQ(tree.get_root_ptr()->_left->_right, nullptr);

    ASSERT_NE(tree.get_root_ptr()->_right, nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_right->_data.first, 70);

    ASSERT_NE(tree.get_root_ptr()->_right->_left, nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_right->_left->_data.first, 60);

    ASSERT_NE(tree.get_root_ptr()->_right->_right, nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_right->_right->_data.first, 80);

    EXPECT_THROW(tree.find(50), std::out_of_range);
    EXPECT_NO_THROW(tree.find(40));
    EXPECT_NO_THROW(tree.find(30));
    EXPECT_NO_THROW(tree.find(20));
    EXPECT_NO_THROW(tree.find(70));
    EXPECT_NO_THROW(tree.find(60));
    EXPECT_NO_THROW(tree.find(80));
}

TEST(TestBSTree, test_erase_leaf) {
    BSTree<int, std::string> tree;
    tree.insert(10, "10");
    tree.insert(5, "5");
    tree.insert(15, "15");
    tree.insert(3, "3");
    tree.insert(7, "7");
    tree.insert(12, "12");
    tree.insert(18, "18");

    //          10
    //         /  \
    //        5    15
    //       / \   / \
    //      3   7 12 18

    EXPECT_NO_THROW(tree.erase(3));  

    //          10
    //         /  \
    //        5    15
    //         \   / \
    //          7 12 18


    ASSERT_NE(tree.get_root_ptr(), nullptr);

    EXPECT_EQ(tree.get_root_ptr()->_data.first, 10);
    EXPECT_EQ(tree.get_root_ptr()->_data.second, "10");

    ASSERT_NE(tree.get_root_ptr()->_left, nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_left->_data.first, 5);
    EXPECT_EQ(tree.get_root_ptr()->_left->_data.second, "5");

    EXPECT_EQ(tree.get_root_ptr()->_left->_left, nullptr);

    ASSERT_NE(tree.get_root_ptr()->_left->_right, nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_left->_right->_data.first, 7);
    EXPECT_EQ(tree.get_root_ptr()->_left->_right->_data.second, "7");

    ASSERT_NE(tree.get_root_ptr()->_right, nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_right->_data.first, 15);
    EXPECT_EQ(tree.get_root_ptr()->_right->_data.second, "15");

    ASSERT_NE(tree.get_root_ptr()->_right->_left, nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_right->_left->_data.first, 12);
    EXPECT_EQ(tree.get_root_ptr()->_right->_left->_data.second, "12");

    ASSERT_NE(tree.get_root_ptr()->_right->_right, nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_right->_right->_data.first, 18);
    EXPECT_EQ(tree.get_root_ptr()->_right->_right->_data.second, "18");

    EXPECT_THROW(tree.find(3), std::out_of_range);

    EXPECT_NO_THROW(tree.find(10));
    EXPECT_NO_THROW(tree.find(5));
    EXPECT_NO_THROW(tree.find(7));
    EXPECT_NO_THROW(tree.find(15));
    EXPECT_NO_THROW(tree.find(12));
    EXPECT_NO_THROW(tree.find(18));
}
TEST(TestBSTree, test_erase_node_with_one_child) {
    BSTree<int, std::string> tree;
    tree.insert(10, "10");
    tree.insert(5, "5");
    tree.insert(15, "15");
    tree.insert(3, "3");
    tree.insert(7, "7");
    tree.insert(12, "12");
    tree.insert(18, "18");
    tree.insert(6, "6");  
    tree.insert(20, "20");

    //          10
    //         /  \
    //        5    15
    //       / \   / \
    //      3   7 12 18
    //         /      \
    //        6       20

    EXPECT_NO_THROW(tree.erase(7)); 

    //          10
    //         /  \
    //        5    15
    //       / \   / \
    //      3   6 12 18
    //                 \
    //                  20


    ASSERT_NE(tree.get_root_ptr(), nullptr);

    EXPECT_EQ(tree.get_root_ptr()->_data.first, 10);

    ASSERT_NE(tree.get_root_ptr()->_left, nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_left->_data.first, 5);

    ASSERT_NE(tree.get_root_ptr()->_left->_left, nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_left->_left->_data.first, 3);

    ASSERT_NE(tree.get_root_ptr()->_left->_right, nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_left->_right->_data.first, 6);
    EXPECT_EQ(tree.get_root_ptr()->_left->_right->_data.second, "6");

    EXPECT_EQ(tree.get_root_ptr()->_left->_right->_left, nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_left->_right->_right, nullptr);

    ASSERT_NE(tree.get_root_ptr()->_right, nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_right->_data.first, 15);

    ASSERT_NE(tree.get_root_ptr()->_right->_left, nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_right->_left->_data.first, 12);

    ASSERT_NE(tree.get_root_ptr()->_right->_right, nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_right->_right->_data.first, 18);

    ASSERT_NE(tree.get_root_ptr()->_right->_right->_right, nullptr);
    EXPECT_EQ(tree.get_root_ptr()->_right->_right->_right->_data.first, 20);

    EXPECT_THROW(tree.find(7), std::out_of_range);

    EXPECT_NO_THROW(tree.find(6));

    EXPECT_NO_THROW(tree.find(10));
    EXPECT_NO_THROW(tree.find(5));
    EXPECT_NO_THROW(tree.find(3));
    EXPECT_NO_THROW(tree.find(15));
    EXPECT_NO_THROW(tree.find(12));
    EXPECT_NO_THROW(tree.find(18));
    EXPECT_NO_THROW(tree.find(20));
}
TEST(TestBSTree, test_erase_node_with_two_children) {
    BSTree<int, std::string> tree;
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
//         50
//        /  \
//     30      70
//    /  \     / \
//   20  40  60   80
//       / \      /\
//      35 45    55 65

    EXPECT_NO_THROW(tree.erase(30));

   /*   50
       /  \
     20    70
      \    / \
       40 60 80
      / \    / \
     35 45 55 65*/
    Node<int, std::string>* root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->_data.first, 50);
    EXPECT_EQ(root->_data.second, "50");

    ASSERT_NE(root->_left, nullptr);
    int left_value = root->_left->_data.first;


    EXPECT_TRUE(left_value == 20 || left_value == 35);

   

    ASSERT_NE(root->_right, nullptr);
    EXPECT_EQ(root->_right->_data.first, 70);

    ASSERT_NE(root->_right->_left, nullptr);
    EXPECT_EQ(root->_right->_left->_data.first, 60);

    ASSERT_NE(root->_right->_right, nullptr);
    EXPECT_EQ(root->_right->_right->_data.first, 80);

    ASSERT_NE(root->_right->_left->_left, nullptr);
    EXPECT_EQ(root->_right->_left->_left->_data.first, 55);

    ASSERT_NE(root->_right->_left->_right, nullptr);
    EXPECT_EQ(root->_right->_left->_right->_data.first, 65);

    EXPECT_THROW(tree.find(30), std::out_of_range);

    EXPECT_NO_THROW(tree.find(50));
    EXPECT_NO_THROW(tree.find(20));
    EXPECT_NO_THROW(tree.find(35));
    EXPECT_NO_THROW(tree.find(40));
    EXPECT_NO_THROW(tree.find(45));
    EXPECT_NO_THROW(tree.find(70));
    EXPECT_NO_THROW(tree.find(60));
    EXPECT_NO_THROW(tree.find(80));
    EXPECT_NO_THROW(tree.find(55));
    EXPECT_NO_THROW(tree.find(65));
}
TEST(TestBSTree, test_erase_node_with_two_children_other) {
    BSTree<int, std::string> tree;
    tree.insert(10, "10");
    tree.insert(70, "70");
    tree.insert(30, "30");

    Node<int, std::string>* root = tree.get_root_ptr();
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->_data.first, 10);
    EXPECT_EQ(root->_data.second, "10");

    ASSERT_NE(root->_right, nullptr);
    EXPECT_EQ(root->_right->_data.first, 70);

    ASSERT_NE(root->_right->_left, nullptr);
    EXPECT_EQ(root->_right->_left->_data.first, 30);

    EXPECT_EQ(root->_left, nullptr);
}