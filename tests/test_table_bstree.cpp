#include <gtest/gtest.h>
#include "../lib_TableBSTree/table_bstree.h"
#include "../lib_Polynom/polynom.h"
#define EPSILON 0.000001

TEST(TestTableBSTree, test_unsorted_table_on_tree_empty) {
    TableBSTree<std::string, Polynom> table_on_arr;
    ASSERT_TRUE(table_on_arr.is_empty());
}

TEST(TestTableBSTree, test_unsorted_table_on_arr_erase) {
    TableBSTree<std::string, Polynom> table_on_arr;
    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("3x^2 + 2y - 5z");

    table_on_arr.insert("pol1", p1);
    table_on_arr.insert("pol0", p2);

    table_on_arr.print();
    ASSERT_FALSE(table_on_arr.is_empty());
}

TEST(TestTableBSTree, test_unsorted_table_on_arr_found) {
    TableBSTree<std::string, Polynom> table_on_arr;
    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("3x^2 + 2y - 5z + 7");

    table_on_arr.insert("pol1", p1);
    table_on_arr.insert("pol2", p2);

    ASSERT_NO_THROW(table_on_arr.found("pol2"));
    EXPECT_EQ(table_on_arr.found("pol2"), p2);
}

TEST(TestTableBSTree, test_unsorted_table_on_arr_found_with_erase) {
    TableBSTree<std::string, Polynom> table_on_arr;
    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("3x^2 + 2y - 5z + 7");

    table_on_arr.insert("pol1", p1);
    table_on_arr.insert("pol2", p2);
    table_on_arr.erase("pol2");

    ASSERT_NO_THROW(table_on_arr.found("pol1"));
    EXPECT_EQ(table_on_arr.found("pol1"), p1);
}

TEST(TestTableBSTree, test_unsorted_table_on_arr_found_with_throw) {
    TableBSTree<std::string, Polynom> table_on_arr;
    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("3x^2 + 2y - 5z + 7");

    table_on_arr.insert("pol1", p1);
    table_on_arr.insert("pol2", p2);
    table_on_arr.erase("pol2");

    ASSERT_THROW(table_on_arr.found("pol2"), std::logic_error);
}

TEST(TestTableBSTree, test_insert_duplicate_key) {
    TableBSTree<std::string, Polynom> table;
    Polynom p1("x+y");
    Polynom p2("z");

    table.insert("pol1", p1);
    ASSERT_THROW(table.insert("pol1", p2), std::logic_error);
    ASSERT_EQ(table.found("pol1"), p1);
    ASSERT_NE(table.found("pol1"), p2);
}


TEST(TestTableBSTree, test_erase_with_throw) {
    TableBSTree<std::string, Polynom> table;
    ASSERT_THROW(table.erase("pol1"), std::out_of_range);
    Polynom p("x");

    table.insert("pol1", p);
    ASSERT_THROW(table.erase("pol2"), std::out_of_range);
}

TEST(TestTableBSTree, test_erase_middle_and_find_others) {
    TableBSTree<std::string, Polynom> table;
    Polynom p1("10");
    Polynom p2("20");
    Polynom p3("30");

    table.insert("1", p1);
    table.insert("2", p2);
    table.insert("3", p3);

    table.erase("1");
    ASSERT_NO_THROW(table.found("3"));
    ASSERT_THROW(table.found("4"), std::logic_error);
    ASSERT_EQ(table.found("2"), p2);
    ASSERT_EQ(table.found("3"), p3);
}

TEST(TestTableBSTree, test_clear_and_reinsert) {
    TableBSTree<std::string, Polynom> table;
    Polynom p1("1");
    Polynom p2("2");

    table.insert("a", p1);
    table.erase("a");
    ASSERT_TRUE(table.is_empty());

    table.insert("b", p2);
    ASSERT_EQ(table.found("b"), p2);
}

TEST(TestTableBSTree, test_function_print) {
    TableBSTree<std::string, Polynom> table;
    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("3x^2 + 2y - 5z + 7");
    Polynom p3("3x^20 + 5x^19 - 2x^18 + 7x^17 - 4x^16 + 9x^15");
    Polynom p4("3x^20 + 5x^19 - 2x^18 + 7x^17");

    table.insert("pol1", p1);
    table.insert("pol2", p2);
    ASSERT_THROW(table.insert("pol2", Polynom("3x^2 + 2y - 5z + 6")), std::logic_error);
    table.insert("pol89", p3);
    table.insert("pol79", p4);
    table.print();
}


TEST(TestTableBSTree, test_polynom_equality) {
    TableBSTree<Polynom, std::string> table;
    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("3x^2 + 2y - 5z + 7");
    Polynom p3("x + y - z");

    table.insert(p1, "first");
    ASSERT_THROW(table.insert(p2, "second"), std::logic_error);
    table.insert(p3, "third");

    ASSERT_EQ(table.found(p1), "first");
    ASSERT_EQ(table.found(p3), "third");
}

TEST(TestTableBSTree, test_keys_stored_in_sorted_order) {
    TableBSTree<std::string, Polynom> table;

    std::string keys_unsorted[] = { "k3", "k1", "k5", "k2", "k4" };
    Polynom values[] = {
        Polynom("3"), Polynom("1"), Polynom("5"),
        Polynom("2"), Polynom("4")
    };

    int count = 5;
    for (int i = 0; i < count; ++i) {
        table.insert(keys_unsorted[i], values[i]);
    }

    for (size_t i = 1; i < table.size(); ++i) {
        const auto& prev = table.get_key(i - 1);
        const auto& curr = table.get_key(i);
        EXPECT_LT(prev, curr);
    }
    std::string expected_order[] = { "k1", "k2", "k3", "k4", "k5" };
    for (size_t i = 0; i < table.size(); ++i) {
        EXPECT_EQ(table.get_key(i), expected_order[i]);
    }

    for (int i = 0; i < count; ++i) {
        EXPECT_EQ(table[keys_unsorted[i]], values[i]);
    }
}
TEST(TestTableBSTree, test_found_method) {
    TableBSTree<std::string, Polynom> table;

    std::string keys[] = { "k3", "k1", "k5", "k2", "k4" };
    Polynom values[] = {
        Polynom("3x + 2y"), Polynom("x + y"), Polynom("5z"),
        Polynom("2x - y"), Polynom("4x + z")
    };

    for (int i = 0; i < 5; ++i) {
        table.insert(keys[i], values[i]);
    }

    EXPECT_EQ(table.found("k1"), values[1]);
    EXPECT_EQ(table.found("k3"), values[0]);
    EXPECT_EQ(table.found("k5"), values[2]);

    EXPECT_THROW(table.found("k10"), std::logic_error);
    EXPECT_THROW(table.found("abc"), std::logic_error);
}

TEST(TestTableBSTree, test_erase_basic) {
    TableBSTree<std::string, Polynom> table;

    std::string keys[] = { "k1", "k2", "k3", "k4", "k5" };
    Polynom values[] = {
        Polynom("1x"), Polynom("2y"), Polynom("3z"),
        Polynom("4x"), Polynom("5y")
    };

    for (int i = 0; i < 5; ++i) {
        table.insert(keys[i], values[i]);
    }

    EXPECT_EQ(table.size(), 5);
    table.erase("k3");
    EXPECT_EQ(table.size(), 4);

    EXPECT_THROW(table.found("k3"), std::logic_error);

    std::string expected_order1[] = { "k1", "k2", "k4", "k5" };
    for (size_t i = 0; i < table.size(); ++i) {
        EXPECT_EQ(table.get_key(i), expected_order1[i]);
    }
}