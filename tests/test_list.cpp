#include <gtest/gtest.h>
#include "../lib_List/list.h"

TEST(TestList, test_list_constructor) {
	List <int> list;
	EXPECT_TRUE(list.is_empty());
	EXPECT_EQ(list.tail(), nullptr);
	EXPECT_EQ(list.head(), nullptr);
}
TEST(TestList, test_list_push_front) {
	List <int> list;
	list.push_front(3);
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(list.head()->value, 3);
	EXPECT_EQ(list.tail()->value, 3);

	list.push_front(2);
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(list.head()->value, 2);
	EXPECT_EQ(list.tail()->value, 3);
}
TEST(TestList, test_list_insert_at) {
	List <int> list;
	list.push_back(3);
	list.push_back(2);
	list.push_back(1);
	list.pop_front();
	list.insert_at(0, 43);
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(list.head()->value, 43);
	EXPECT_EQ(list.tail()->value, 1);
}
TEST(TestList, test_insert_after_middle) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(4);

	Node<int>* first_node = list.head(); 
	list.insert_after(first_node, 3);

	EXPECT_EQ(list.head()->value, 1);
	EXPECT_EQ(list.head()->next->value, 3);
	EXPECT_EQ(list.head()->next->next->value, 2);
	EXPECT_EQ(list.tail()->value, 4);
}

TEST(TestList, test_list_push_back) {
	List<int> list;

	list.push_back(1);
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(list.head()->value, 1);
	EXPECT_EQ(list.tail()->value, 1);

	list.push_back(2);
	EXPECT_EQ(list.head()->value, 1);
	EXPECT_EQ(list.tail()->value, 2);
}

TEST(TestList, test_list_pop_front) {
	List <int> list;
	list.push_back(3);
	list.push_back(2);
	list.push_back(1);
	list.pop_front();
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(list.head()->value, 2);
	EXPECT_EQ(list.tail()->value, 1);
}
TEST(TestList, test_erase_by_node_middle) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);

	Node<int>* node_to_delete = list.head()->next->next; 
	list.erase(node_to_delete);

	EXPECT_EQ(list.head()->value, 1);
	EXPECT_EQ(list.head()->next->value, 2);
	EXPECT_EQ(list.tail()->value, 4);
}
TEST(TestList, test_list_pop_back) {
	List <int> list;
	list.push_back(3);
	list.push_back(2);
	list.push_back(1);
	list.pop_back();
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(list.head()->value, 3);
	EXPECT_EQ(list.tail()->value, 2);
}