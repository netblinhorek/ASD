#include <gtest/gtest.h>
#include "../lib_UnsortedTableOnList/unsorted_table_on_list.h"
#include "../lib_Polynom/polynom.h"
#define EPSILON 0.000001

TEST(TestUnsortedOnList, test_unsorted_table_on_arr_empty) {
    UnsortedTableL<std::string, Polynom> table_on_arr;
    ASSERT_TRUE(table_on_arr.is_empty());
}

TEST(TestUnsortedOnList, test_unsorted_table_on_arr_erase) {
    UnsortedTableL<std::string, Polynom> table_on_arr;
    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("3x^2 + 2y - 5z + 7");

    table_on_arr.insert("pol1", p1);
    table_on_arr.insert("pol2", p2);
    table_on_arr.erase("pol2");

    ASSERT_FALSE(table_on_arr.is_empty());
}

TEST(TestUnsortedOnList, test_unsorted_table_on_arr_found) {
    UnsortedTableL<std::string, Polynom> table_on_arr;
    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("3x^2 + 2y - 5z + 7");

    table_on_arr.insert("pol1", p1);
    table_on_arr.insert("pol2", p2);

    ASSERT_NO_THROW(table_on_arr.found("pol2"));
    EXPECT_EQ(table_on_arr.found("pol2"), p2);
}

TEST(TestUnsortedOnList, test_unsorted_table_on_arr_found_with_erase) {
    UnsortedTableL<std::string, Polynom> table_on_arr;
    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("3x^2 + 2y - 5z + 7");

    table_on_arr.insert("pol1", p1);
    table_on_arr.insert("pol2", p2);
    table_on_arr.erase("pol2");

    ASSERT_NO_THROW(table_on_arr.found("pol1"));
    EXPECT_EQ(table_on_arr.found("pol1"), p1);
}

TEST(TestUnsortedOnList, test_unsorted_table_on_arr_found_with_throw) {
    UnsortedTableL<std::string, Polynom> table_on_arr;
    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("3x^2 + 2y - 5z + 7");

    table_on_arr.insert("pol1", p1);
    table_on_arr.insert("pol2", p2);
    table_on_arr.erase("pol2");

    ASSERT_THROW(table_on_arr.found("pol2"), std::logic_error);
}

TEST(TestUnsortedOnList, test_insert_duplicate_key) {
    UnsortedTableL<std::string, Polynom> table;
    Polynom p1("x+y");
    Polynom p2("z");

    table.insert("pol1", p1);
    ASSERT_THROW(table.insert("pol1", p2), std::logic_error);
    ASSERT_EQ(table.found("pol1"), p1);
    ASSERT_NE(table.found("pol1"), p2);
}

TEST(TestUnsortedOnList, test_erase_non_existent) {
    UnsortedTableL<std::string, Polynom> table;
    Polynom p("x");

    table.insert("pol1", p);
    ASSERT_NO_THROW(table.erase("pol2"));
}

TEST(TestUnsortedOnList, test_erase_middle_and_find_others) {
    UnsortedTableL<std::string, Polynom> table;
    Polynom p1("10");
    Polynom p2("20");
    Polynom p3("30");

    table.insert("1", p1);
    table.insert("2", p2);
    table.insert("3", p3);

    table.erase("1");
    ASSERT_NO_THROW(table.found("3"));
    ASSERT_EQ(table.found("2"), p2);
    ASSERT_EQ(table.found("3"), p3);
}

TEST(TestUnsortedOnList, test_clear_and_reinsert) {
    UnsortedTableL<std::string, Polynom> table;
    Polynom p1("1");
    Polynom p2("2");

    table.insert("a", p1);
    table.erase("a");
    ASSERT_TRUE(table.is_empty());

    table.insert("b", p2);
    ASSERT_EQ(table.found("b"), p2);
}

TEST(TestUnsortedOnList, test_function_print) {
    UnsortedTableL<std::string, Polynom> table;
    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("3x^2 + 2y - 5z + 7");
    Polynom p3("3x^20 + 5x^19 - 2x^18 + 7x^17 - 4x^16 + 9x^15");

    table.insert("pol1", p1);
    table.insert("pol2", p2);
    ASSERT_THROW(table.insert("pol2", Polynom("3x^2 + 2y - 5z + 6")), std::logic_error);
    table.insert("pol89", p3);

    table.print();
}


TEST(TestUnsortedOnList, test_polynom_equality) {
    UnsortedTableL<Polynom, std::string> table;
    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("3x^2 + 2y - 5z + 7");
    Polynom p3("x + y - z");

    table.insert(p1, "first");
    ASSERT_THROW(table.insert(p2, "second"), std::logic_error);
    table.insert(p3, "third");

    ASSERT_EQ(table.found(p1), "first");
    ASSERT_EQ(table.found(p3), "third");
}

TEST(TestUnsortedOnList, test_operator_bracket_simple) {
    UnsortedTableL<std::string, Polynom> table;

    std::string keys[] = { "k1", "k2", "k3" };
    Polynom values[] = { Polynom("x+1"), Polynom("2y"), Polynom("z-5") };

    for (int i = 0; i < 3; ++i) {
        table.insert(keys[i], values[i]);
    }

    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(table[keys[i]], values[i]);
    }
}