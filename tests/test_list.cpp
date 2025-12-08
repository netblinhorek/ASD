#include <gtest/gtest.h>
#include "../lib_List/list.h"
#include <unordered_set> 
#include <vector>

TEST(TestList, test_list_constructor) {
	List <int> list;
	EXPECT_TRUE(list.is_empty());
	EXPECT_EQ(list.tail(), nullptr);
	EXPECT_EQ(list.head(), nullptr);
	EXPECT_EQ(list.count(), 0);
	list.push_front(3);
	list.pop_front();
	EXPECT_TRUE(list.is_empty());
	EXPECT_EQ(list.tail(), nullptr);
	EXPECT_EQ(list.head(), nullptr);
	EXPECT_EQ(list.count(), 0);
}


TEST(TestList, test_list_push_front) {
	List <int> list;
	list.push_front(3);
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(list.count(), 1);
	EXPECT_EQ(list.head()->value, 3);
	EXPECT_EQ(list.tail()->value, 3);

	list.push_front(2);
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(list.count(), 2);
	EXPECT_EQ(list.head()->value, 2);
	EXPECT_EQ(list.tail()->value, 3);
}

TEST(TestList, test_list_count_after_pop) {
	List <int> list;
	list.push_front(3);
	list.push_front(2);
	EXPECT_FALSE(list.is_empty());
	list.pop_back();
	list.pop_front();
	EXPECT_EQ(list.count(), 0);
}
TEST(TestList, test_list_insert_at) {
	List <int> list;
	list.push_back(3);
	list.push_back(2);
	list.push_back(1);
	list.pop_front();
	list.insert(static_cast<size_t>(0), 43);
	EXPECT_EQ(list.count(), 3);
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
	list.insert(first_node, 3);

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
	EXPECT_EQ(list.count(), 2);
	EXPECT_EQ(list.head()->value, 3);
	EXPECT_EQ(list.tail()->value, 2);
}

TEST(ListIteratorTest, test_empty_list_iteration) {
	List<int> emptyList;

	EXPECT_FALSE(emptyList.begin() != emptyList.end());
}

TEST(ListIteratorTest, test_read_iterator) {
	List<int> list;
	list.push_back(10);
	list.push_back(20);
	list.push_back(30);

	List<int>::Iterator it = list.begin();
	EXPECT_EQ(*it, 10);

	++it;
	EXPECT_EQ(*it, 20);

	it++;
	EXPECT_EQ(*it, 30);
}

TEST(ListIteratorTest, test_write_iterator) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	int value = 100;
	for (auto it = list.begin(); it != list.end(); ++it) {
		*it = value;
		value += 100;
	}

	auto it = list.begin();
	EXPECT_EQ(*it, 100);

	++it;
	EXPECT_EQ(*it, 200);

	++it;
	EXPECT_EQ(*it, 300);

	++it;
	EXPECT_EQ(it, list.end());
	ASSERT_THROW(it++, std::invalid_argument);
	ASSERT_THROW(++it, std::invalid_argument);

}

TEST(ListHareAndTurtleTest, test_hare_and_turtle) {
	List<int> empty_list;
	ASSERT_FALSE(empty_list.has_loop_floyd());

	List<int> list_no_loop;
	for (int i = 0; i < 14; i++) {
		list_no_loop.push_back(i);
	}

	ASSERT_FALSE(list_no_loop.has_loop_floyd());
}


TEST(ListHareAndTurtleTest, test_hare_and_turtle_with_floyd) {
	List<int> list_with_loop;

	for (int i = 0; i < 5; i++) {
		list_with_loop.push_back(i);
	}

	list_with_loop.create_loop(2);
	ASSERT_TRUE(list_with_loop.has_loop_floyd());

	
	list_with_loop.remove_loop_if_exists();

	ASSERT_FALSE(list_with_loop.has_loop_floyd());
	auto it = list_with_loop.begin();
	EXPECT_EQ(*it, 0);
	++it;
	EXPECT_EQ(*it, 1);
	++it;
	EXPECT_EQ(*it, 2);
	++it;
	EXPECT_EQ(*it, 3);
	++it;
	EXPECT_EQ(*it, 4);
	++it;
	EXPECT_EQ(it, list_with_loop.end());
}
TEST(ListIteratorCycleTest, test_pointer_reversal_loop) {
	List<int> list;
	ASSERT_FALSE(list.has_loop_pointer_reversal());

	for (int i = 0; i < 14; i++) {
		list.push_back(i);
	}
	ASSERT_FALSE(list.has_loop_pointer_reversal());

	list.create_loop(0);

	ASSERT_TRUE(list.has_loop_pointer_reversal());
}


TEST(ListDistanceMethodTest, test_distance_method_no_loop) {
	List<int> list_no_loop;

	list_no_loop.push_back(1);
	list_no_loop.push_back(2);
	list_no_loop.push_back(3);
	ASSERT_FALSE(list_no_loop.has_loop_distance());

	list_no_loop.clear();
	for (int i = 0; i < 14; i++) {
		list_no_loop.push_back(i);
	}

	ASSERT_FALSE(list_no_loop.has_loop_distance());
}

TEST(ListDistanceMethodTest, test_distance_method_with_loop) {
	List<int> list_with_loop;

	for (int i = 0; i < 5; i++) {
		list_with_loop.push_back(i);
	}

	list_with_loop.create_loop(2);
	ASSERT_TRUE(list_with_loop.has_loop_distance());

	list_with_loop.remove_loop_if_exists();
	ASSERT_FALSE(list_with_loop.has_loop_distance());
}