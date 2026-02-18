#include <gtest/gtest.h>
#include "../lib_UnsortedTableOnArr/unsorted_table_on_arr.h"
#include "../lib_Polynom/polynom.h"
#define EPSILON 0.000001


TEST(TestUnsortedOnArr, test_unsorted_table_on_arr_empty) {
	UnsortedTableM <std::string, std::string> table_on_arr;
	ASSERT_TRUE(table_on_arr.is_empty());
	ASSERT_TRUE(table_on_arr.is_tab_ended());
	ASSERT_EQ(table_on_arr.get_size(), 0);
}

TEST(TestUnsortedOnArr, test_unsorted_table_on_arr_insert) {
	UnsortedTableM <std::string, std::string> table_on_arr;
	table_on_arr.insert("pol1", "3x^2 + 2y - 5z + 7");
	table_on_arr.insert("pol2", "3x^2 + 2y - 5z + 7");
	ASSERT_EQ(table_on_arr.get_size(), 2);
}

TEST(TestUnsortedOnArr, test_unsorted_table_on_arr_erase) {
	UnsortedTableM <std::string, std::string> table_on_arr;
	table_on_arr.insert("pol1", "3x^2 + 2y - 5z + 7");
	table_on_arr.insert("pol2", "3x^2 + 2y - 5z + 7");
	table_on_arr.erase("pol2");
	ASSERT_EQ(table_on_arr.get_size(), 1);
}

TEST(TestUnsortedOnArr, test_unsorted_table_on_arr_found) {
	UnsortedTableM <std::string, std::string> table_on_arr;
	table_on_arr.insert("pol1", "3x^2 + 2y - 5z + 7");
	table_on_arr.insert("pol2", "3x^2 + 2y - 5z + 7");
	ASSERT_NO_THROW(table_on_arr.found("pol2"));
}

TEST(TestUnsortedOnArr, test_unsorted_table_on_arr_found_with_erase) {
	UnsortedTableM <std::string, std::string> table_on_arr;
	table_on_arr.insert("pol1", "3x^2 + 2y - 5z + 7");
	table_on_arr.insert("pol2", "3x^2 + 2y - 5z + 7");
	table_on_arr.erase("pol2");
	ASSERT_NO_THROW(table_on_arr.found("pol1")); 
}

TEST(TestUnsortedOnArr, test_unsorted_table_on_arr_found_with_throw) {
	UnsortedTableM <std::string, std::string> table_on_arr;
	table_on_arr.insert("pol1", "3x^2 + 2y - 5z + 7");
	table_on_arr.insert("pol2", "3x^2 + 2y - 5z + 7");
	table_on_arr.erase("pol2");
	ASSERT_THROW(table_on_arr.found("pol2"), std::logic_error);
}
TEST(TestUnsortedOnArr, test_insert_duplicate_key) {
	UnsortedTableM<std::string, std::string> table;
	table.insert("pol1", "x+y");
	table.insert("pol1", "z");
	ASSERT_EQ(table.get_size(), 1);
	ASSERT_EQ(table.found("pol1"), "z"); 
}

TEST(TestUnsortedOnArr, test_iteration_full_cycle) {
	UnsortedTableM<std::string, int> table;
	table.insert("a", 1);
	table.insert("b", 2);

	int sum = 0;
	int count = 0;
	for (table.reset(); !table.is_tab_ended(); table.go_next()) {
		sum += table.get_value();
		count++;
	}
	ASSERT_EQ(sum, 3);
	ASSERT_EQ(count, 2);
}

TEST(TestUnsortedOnArr, test_erase_non_existent) {
	UnsortedTableM<std::string, std::string> table;
	table.insert("pol1", "x");
	ASSERT_NO_THROW(table.erase("pol2"));
	ASSERT_EQ(table.get_size(), 1);
}

TEST(TestUnsortedOnArr, test_erase_middle_and_found_others) {
	UnsortedTableM<std::string, int> table;
	table.insert("1", 10);
	table.insert("2", 20);
	table.insert("3", 30);

	table.erase("1"); 
	ASSERT_EQ(table.get_size(), 2);
	ASSERT_NO_THROW(table.found("3")); 
	ASSERT_EQ(table.found("2"), 20);
}

TEST(TestUnsortedOnArr, test_clear_and_reinsert) {
	UnsortedTableM<std::string, int> table;
	table.insert("a", 1);
	table.erase("a");
	ASSERT_TRUE(table.is_empty());

	table.insert("b", 2);
	ASSERT_EQ(table.get_size(), 1);
	ASSERT_EQ(table.found("b"), 2);
}



TEST(TestUnsortedOnArr, test_get_key_and_value_throw) {
    UnsortedTableM<std::string, int> table;

    EXPECT_TRUE(table.is_tab_ended());
    EXPECT_EQ(table.get_size(), 0);

    EXPECT_THROW(table.get_key(), std::out_of_range);
    EXPECT_THROW(table.get_value(), std::out_of_range);
}

TEST(TestUnsortedOnArr, test_is_tab_ended) {
    UnsortedTableM<std::string, int> table;
    table.insert("key1", 100);

    table.reset();
    EXPECT_FALSE(table.is_tab_ended());
    EXPECT_EQ(table.get_key(), "key1");
    EXPECT_EQ(table.get_value(), 100);

    table.go_next();
    EXPECT_TRUE(table.is_tab_ended());
}


TEST(TestUnsortedOnArr, test_is_tab_ended_false) {
    UnsortedTableM<std::string, int> table;
    table.insert("key1", 100);
    table.insert("key2", 200);

    table.reset();
    EXPECT_EQ(table.get_key(), "key1");
    table.go_next();
    EXPECT_EQ(table.get_key(), "key2");
    EXPECT_FALSE(table.is_tab_ended());

    table.reset();
	EXPECT_EQ(table.get_key(), "key1");
	EXPECT_FALSE(table.is_tab_ended());
}

TEST(TestUnsortedOnArr, test_reset) {
    UnsortedTableM<std::string, int> table;

    table.reset();
    EXPECT_TRUE(table.is_tab_ended());

    table.insert("key1", 100);
    table.reset();
    EXPECT_FALSE(table.is_tab_ended());

    table.go_next();
    EXPECT_TRUE(table.is_tab_ended());

    EXPECT_NO_THROW(table.go_next());
    EXPECT_TRUE(table.is_tab_ended());
}


TEST(TestUnsortedOnArr, test_function_print) {
	UnsortedTableM<std::string, std::string> table;
	table.insert("pol1", "3x^2 + 2y - 5z + 7");
	table.insert("pol2", "3x^2 + 2y - 5z + 7");
	table.insert("pol2", "3x^2 + 2y - 5z + 6");
	table.insert("pol2", "3x^2 + 67898x + 2y - 5z + 7");
	table.insert("pol89", "3x^20 + 5x^19 - 2x^18 + 7x^17 - 4x^16 + 9x^15");
		
	table.print(std::cout);
}