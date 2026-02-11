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

TEST(TestUnsortedOnArr, test_erase_middle_and_find_others) {
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