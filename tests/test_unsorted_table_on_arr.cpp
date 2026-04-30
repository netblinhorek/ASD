#include <gtest/gtest.h>
#include "../lib_UnsortedTableOnArr/unsorted_table_on_arr.h"
#include "../lib_Polynom/polynom.h"
#define EPSILON 0.000001

TEST(TestUnsortedOnArr, test_unsorted_table_on_arr_empty) {
    UnsortedTableM<std::string, Polynom> table_on_arr;
    table_on_arr.print();
    ASSERT_TRUE(table_on_arr.is_empty());
}

TEST(TestUnsortedOnArr, test_unsorted_table_on_arr_erase) {
    UnsortedTableM<std::string, Polynom> table_on_arr;
    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("3x^2 + 2y - 5z + 7");

    table_on_arr.insert("pol1", p1);
    table_on_arr.insert("pol2", p2);
    table_on_arr.erase("pol2");

    ASSERT_FALSE(table_on_arr.is_empty());
}

TEST(TestUnsortedOnArr, test_unsorted_table_on_arr_found) {
    UnsortedTableM<std::string, Polynom> table_on_arr;
    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("3x^2 + 2y - 5z + 7");

    table_on_arr.insert("pol1", p1);
    table_on_arr.insert("pol2", p2);

    ASSERT_NO_THROW(table_on_arr.found("pol2"));
    EXPECT_EQ(table_on_arr.found("pol2"), p2);
}

TEST(TestUnsortedOnArr, test_unsorted_table_on_arr_found_with_erase) {
    UnsortedTableM<std::string, Polynom> table_on_arr;
    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("3x^2 + 2y - 5z + 7");

    table_on_arr.insert("pol1", p1);
    table_on_arr.insert("pol2", p2);
    table_on_arr.erase("pol2");

    ASSERT_NO_THROW(table_on_arr.found("pol1"));
    EXPECT_EQ(table_on_arr.found("pol1"), p1);
}

TEST(TestUnsortedOnArr, test_unsorted_table_on_arr_found_with_throw) {
    UnsortedTableM<std::string, Polynom> table_on_arr;
    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("3x^2 + 2y - 5z + 7");

    table_on_arr.insert("pol1", p1);
    table_on_arr.insert("pol2", p2);
    table_on_arr.erase("pol2");

    ASSERT_THROW(table_on_arr.found("pol2"), std::logic_error);
}

TEST(TestUnsortedOnArr, test_insert_duplicate_key) {
    UnsortedTableM<std::string, Polynom> table;
    Polynom p1("x+y");
    Polynom p2("z");

    table.insert("pol1", p1);
    ASSERT_THROW(table.insert("pol1", p2), std::logic_error);
    ASSERT_EQ(table.found("pol1"), p1);
    ASSERT_NE(table.found("pol1"), p2);
}

TEST(TestUnsortedOnArr, test_erase_with_throw) {
    UnsortedTableM<std::string, Polynom> table;
    ASSERT_THROW(table.erase("pol1"), std::out_of_range);
    Polynom p("x");

    table.insert("pol1", p);
    ASSERT_THROW(table.erase("pol2"), std::out_of_range);
}

TEST(TestUnsortedOnArr, test_erase_middle_and_find_others) {
    UnsortedTableM<std::string, Polynom> table;
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
    table.print();
}

TEST(TestUnsortedOnArr, test_clear_and_reinsert) {
    UnsortedTableM<std::string, Polynom> table;
    Polynom p1("1");
    Polynom p2("2");

    table.insert("a", p1);
    table.erase("a");
    ASSERT_TRUE(table.is_empty());

    table.insert("b", p2);
    ASSERT_EQ(table.found("b"), p2);
}

TEST(TestUnsortedOnArr, test_function_print) {
    UnsortedTableM<std::string, Polynom> table;
    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("3x^2 + 2y - 5z + 7");
    Polynom p3("3x^20 + 5x^19 - 2x^18 + 7x^17 - 4x^16 + 9x^15");

    table.insert("pol1", p1);
    table.insert("pol2", p2);
    ASSERT_THROW(table.insert("pol2", Polynom("3x^2 + 2y - 5z + 6")), std::logic_error);
    table.insert("pol89", p3);

    table.print();
}


TEST(TestUnsortedOnArr, test_polynom_equality) {
    UnsortedTableM<Polynom, std::string> table;
    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("3x^2 + 2y - 5z + 7");  
    Polynom p3("x + y - z");           

    table.insert(p1, "first");
    ASSERT_THROW(table.insert(p2, "second"), std::logic_error);  
    table.insert(p3, "third");

    ASSERT_EQ(table.found(p1), "first");
    ASSERT_EQ(table.found(p3), "third");
}

TEST(TestUnsortedOnArr, test_operator_bracket_simple) {
    UnsortedTableM<std::string, Polynom> table;

    std::string keys[] = { "k1", "k2", "k3" };
    Polynom values[] = { Polynom("x+1"), Polynom("2y"), Polynom("z-5") };

    for (int i = 0; i < 3; ++i) {
        table.insert(keys[i], values[i]);
    }

    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(table[keys[i]], values[i]);
    }
}
