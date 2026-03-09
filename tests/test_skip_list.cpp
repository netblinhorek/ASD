#include <gtest/gtest.h>
#include "../lib_SkipList/skip_list.h"
#include "../lib_TVector/tvector.h"

#define EPSILON 0.000001

TEST(TestSkipList, test_skip_list_constructor) {
    SkipList<int, std::string> list(10);
    EXPECT_TRUE(list.is_empty());
}
TEST(TestSkipList, test_skip_list_print) {
    SkipList<std::string, std::string> list(5);
    list.print();
}

TEST(SkipListCoinTest, CoinWithZeroLevels_WouldCrash) {
    SkipList<int, std::string> list(1);
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(list._coin(), 0);  
    }
}

TEST(TestSkipList, test_skip_list_coin_function) {
    SkipList<int, std::string> list(10);  

    for (int i = 0; i < 100; i++) {
        size_t level = list._coin();
        EXPECT_GE(level, 0);  
        EXPECT_LT(level, 10); 
    }
}

TEST(TestSkipList, InsertIntoEmpty) {
    SkipList<int, std::string> list(6);

    EXPECT_TRUE(list.is_empty());
    list.insert(5, "five");
    EXPECT_FALSE(list.is_empty());
    list.print();
}

TEST(TestSkipList, test_insert_in_middle) {
    SkipList<int, std::string> list(12);

    list.insert(1, "one");
    list.insert(5, "five");
    list.insert(10, "ten");
    list.insert(3, "three");   
    list.insert(7, "seven");   
    list.insert(8, "eight");  

    EXPECT_FALSE(list.is_empty());
    list.print();
}

TEST(TestSkipList, test_find_nearest_duplicates_keep_first) {
    SkipList<int, std::string> list(50);

    EXPECT_NO_THROW(list.insert(5, "five"));
    EXPECT_THROW(list.insert(5, "FIVE"), std::runtime_error);
    Node<int, std::string>* node = list.find_nearest(5);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(*(node->data), "five");

}

TEST(TestSkipList, test_insert_reverse_order) {
    SkipList<int, std::string> list(10);


    for (int i = 10; i >= 1; i--) {
        list.insert(i, "value_" + std::to_string(i));
        std::cout << "После вставки " << i << ":" << std::endl;
        list.print();
        std::cout << "-------------------" << std::endl;
    }
}

TEST(TestSkipList, test_insert_random) {
    SkipList<int, std::string> list(15);
    srand(42);

    int numbers[] = { 42, 17, 8, 93, 55, 23, 71, 34, 86, 12 };

    for (int i = 0; i < 10; i++) {
        int key = numbers[i];
        list.insert(key, "value_" + std::to_string(key));
        std::cout << "После вставки " << key << ":" << std::endl;
        list.print();
        std::cout << "-------------------" << std::endl;
    }
}



TEST(TestSkipList, test_negative_numbers) {
    SkipList<int, std::string> list(5);

    list.insert(-5, "minus five");
    list.print();

    list.insert(-10, "minus ten");
    list.print();

    list.insert(0, "zero");
    list.print();

    list.insert(-1, "minus one");
    list.print();

    list.insert(5, "five");
    list.print();
}

TEST(TestSkipList, test_insert_the_front) {
    SkipList<int, std::string> list(10);

    list.insert(2, "2");
    list.insert(3, "3");
    list.insert(4, "4");
    list.insert(5, "5");
    list.insert(6, "6");
    list.insert(1, "1");
    list.print();
}
TEST(TestSkipList, test_insert_the_middle) {
    SkipList<int, std::string> list(10);

    list.insert(2, "2");
    list.insert(3, "3");
   
    list.insert(5, "5");
    list.insert(6, "6");
    list.insert(4, "4");
    list.print();
}
TEST(TestSkipList, test_insert_the_back) {
    SkipList<int, std::string> list(18);

    list.insert(2, "2");
    list.insert(3, "3");
    list.insert(4, "4");
    list.insert(5, "5");
    list.insert(6, "6");
    list.insert(17, "17");

    list.print();
}

TEST(TestSkipList, test_find_simple) {
    SkipList<int, std::string> list(5);

    list.insert(1, "one");
    list.insert(2, "two");
    list.insert(3, "three");

    EXPECT_NE(list.find_nearest(1), nullptr);
    EXPECT_NE(list.find_nearest(2), nullptr);
    EXPECT_NE(list.find_nearest(3), nullptr);

    EXPECT_EQ(list.find_nearest(0), nullptr);
    EXPECT_EQ(list.find_nearest(4), nullptr);

    TVector<int> keys = list.get_keys();
    EXPECT_EQ(keys.size(), 3);
    EXPECT_EQ(keys[0], 1);
    EXPECT_EQ(keys[1], 2);
    EXPECT_EQ(keys[2], 3);
}


TEST(TestSkipList, test_default_parameter_safe_behavior) {
    SkipList<int, std::string> list;  
    
    EXPECT_TRUE(list.is_empty());

    list.insert(42, "123");
    EXPECT_FALSE(list.is_empty());

    TVector<int> keys = list.get_keys();
    EXPECT_EQ(keys.size(), 1);
    EXPECT_EQ(keys[0], 42);
}
TEST(TestSkipList, test_pointers_levels_2_and_3) {

    SkipList<int, std::string> list(4);

    list.insert(5, "five");
    list.insert(15, "fifteen");
    list.insert(10, "ten");
    list.print();
    Node<int, std::string>* node5 = list.find_nearest(5);
    Node<int, std::string>* node10 = list.find_nearest(10);
    Node<int, std::string>* node15 = list.find_nearest(15);

    ASSERT_NE(node5, nullptr);
    ASSERT_NE(node10, nullptr);
    ASSERT_NE(node15, nullptr);

    if (node5->level >= 2) {
        if (node5->next[2] != nullptr) {
            EXPECT_GT(node5->next[2]->key, node5->key);
            EXPECT_TRUE(node5->next[2] == node10 || node5->next[2] == node15);
        }
    }
    if (node10->level >= 2) {
        if (node10->next[2] != nullptr) {
            EXPECT_GT(node10->next[2]->key, node10->key);
            EXPECT_EQ(node10->next[2], node15);
        }
    }
    if (node15->level >= 2) {
        EXPECT_EQ(node15->next[2], nullptr);
    }

    if (node5->level >= 3) {
        if (node5->next[3] != nullptr) {
            EXPECT_GT(node5->next[3]->key, node5->key);
            EXPECT_TRUE(node5->next[3] == node10 || node5->next[3] == node15);
        }
    }
    if (node10->level >= 3) {
        if (node10->next[3] != nullptr) {
            EXPECT_GT(node10->next[3]->key, node10->key);
            EXPECT_EQ(node10->next[3], node15);
        }
    }
    if (node15->level >= 3) {
        EXPECT_EQ(node15->next[3], nullptr);
    }

    if (node5->level >= 3) {
        EXPECT_GE(node5->level, 2);
        EXPECT_NE(node5->next[2], nullptr);
    }
    if (node10->level >= 3) {
        EXPECT_GE(node10->level, 2);
        EXPECT_NE(node10->next[2], nullptr);
    }

    EXPECT_EQ(list.find_nearest(5), node5);
    EXPECT_EQ(list.find_nearest(10), node10);
    EXPECT_EQ(list.find_nearest(15), node15);
}


TEST(TestSkipList, test_find_nearest_after_clear) {
    SkipList<int, std::string> list(10);

    list.insert(1, "one");
    list.insert(2, "two");

    list.clear();

    EXPECT_EQ(list.find_nearest(1), nullptr);
    EXPECT_EQ(list.find_nearest(2), nullptr);

    list.print();
}
TEST(TestSkipList, test_skip_list_coin_distribution) {
    SkipList<int, std::string> list(10);

    TVector<int> counts(10);
    const int ITERATIONS = 10000;

    for (int i = 0; i < ITERATIONS; i++) {
        size_t level = list._coin();
        counts[level]++;
    }

    double level0 = 100.0 * counts[0] / ITERATIONS;
    EXPECT_NEAR(level0, 50.0, 5.0);


    double level1 = 100.0 * counts[1] / ITERATIONS;
    EXPECT_NEAR(level1, 25.0, 5.0);


    double level2 = 100.0 * counts[2] / ITERATIONS;
    EXPECT_NEAR(level2, 12.5, 5.0);

    std::cout << "Распределение уровней:\n";
    for (int i = 0; i < 5; i++) {
        std::cout << "Уровень " << i << ": "
            << 100.0 * counts[i] / ITERATIONS << "%\n";
    }
}
