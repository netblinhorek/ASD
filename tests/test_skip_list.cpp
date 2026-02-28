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

TEST(TestSkipList, InsertInMiddle) {
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

TEST(TestSkipList, InsertDuplicates) {
    SkipList<int, std::string> list(50);

    list.insert(5, "five");
    list.print();
    list.insert(5, "FIVE");  
    list.print();
    list.insert(5, "5");     
    list.print();

    SUCCEED();
}

TEST(TestSkipList, InsertReverseOrder) {
    SkipList<int, std::string> list(10);


    for (int i = 10; i >= 1; i--) {
        list.insert(i, "value_" + std::to_string(i));
        std::cout << "После вставки " << i << ":" << std::endl;
        list.print();
        std::cout << "-------------------" << std::endl;
    }
}

TEST(TestSkipList, InsertRandom) {
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



TEST(TestSkipList, NegativeNumbers) {
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


    auto keys = list.get_keys();
    EXPECT_EQ(keys.size(), 3);
    EXPECT_EQ(keys[0], 1);
    EXPECT_EQ(keys[1], 2);
    EXPECT_EQ(keys[2], 3);
}

TEST(TestSkipList, test_find_nearest_duplicates_keep_first) {
    SkipList<int, std::string> list(10);

    list.insert(5, "first");
    list.insert(5, "second");

    EXPECT_NE(list.find_nearest(5), nullptr);

    list.print();
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
TEST(TestSkipList, test_skip_list_check_with_for) {
    SkipList<int, std::string> list(5);

    EXPECT_TRUE(list.is_empty());

    list.insert(-5, "minus five");
    list.insert(-10, "minus ten");
    list.insert(0, "zero");
    list.insert(-1, "minus one");
    list.insert(5, "five");

    EXPECT_FALSE(list.is_empty());

    int keys[] = { -10, -5, -1, 0, 5 };
    std::string values[] = { "minus ten", "minus five", "minus one",
        "zero", "five" };

    for (int i = 0; i < 5; i++) {
        Node<int, std::string>* node = list.find_nearest(keys[i]);
        EXPECT_NE(node, nullptr);
        EXPECT_EQ(node->key, keys[i]);
        EXPECT_EQ(*(node->data), values[i]);
    }

    EXPECT_EQ(list.find_nearest(100), nullptr);
    EXPECT_EQ(list.find_nearest(-100), nullptr);

    TVector<int> expected;
    expected.push_back(-10);
    expected.push_back(-5);
    expected.push_back(-1);
    expected.push_back(0);
    expected.push_back(5);

    TVector<int> actual = list.get_keys();

    EXPECT_EQ(actual.size(), expected.size());
    for (size_t i = 0; i < expected.size(); i++) {
        EXPECT_EQ(actual[i], expected[i]);
    }
}