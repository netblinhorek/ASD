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

	++it;
	EXPECT_EQ(*it, 30);
}

TEST(ListIteratorTest, test_write_iterator) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);


	List<int>::Iterator it = list.begin();
	*it = 100;
	EXPECT_EQ(*it, 100);

	++it;
	*it = 200;
	EXPECT_EQ(*it, 200);
}

TEST(ListHareAndTurtleTest, test_hare_and_turtle) {
	List<int> empty_list;
	ASSERT_THROW(empty_list.is_looped_the_first(empty_list), std::logic_error);

	List<int> list_no_loop;
	for (int i = 0; i < 14; i++) {
		list_no_loop.push_back(i);
	}
	ASSERT_NO_THROW(list_no_loop.is_looped_the_first(list_no_loop));
	ASSERT_FALSE(list_no_loop.is_looped_the_first(list_no_loop));

	List<int> list_with_loop;
	for (int i = 0; i < 14; i++) {
		list_with_loop.push_back(i);
	}
	list_with_loop.create_loop(5); 
	ASSERT_NO_THROW(list_with_loop.is_looped_the_first(list_with_loop));
	ASSERT_TRUE(list_with_loop.is_looped_the_first(list_with_loop));
}

TEST(ListIteratorCycleTest, test_iterator_cycle) {
	List<int> list_no_loop;
	ASSERT_THROW(list_no_loop.is_looped_the_second(list_no_loop), std::logic_error);

	for (int i = 0; i < 14; i++) {
		list_no_loop.push_back(i);
	}

	List<int> list_no_loop_copy = list_no_loop;
	ASSERT_FALSE(list_no_loop_copy.is_looped_the_second(list_no_loop_copy));

	List<int> list_with_loop;
	for (int i = 0; i < 14; i++) {
		list_with_loop.push_back(i);
	}
	list_with_loop.create_loop(5);

	List<int> list_with_loop_copy = list_with_loop;
	ASSERT_TRUE(list_with_loop_copy.is_looped_the_second(list_with_loop_copy));
}
TEST(ListFindLoopTest, test_find_loop) {

	List<int> empty_list;
	ASSERT_THROW(empty_list.find_loop(empty_list), std::logic_error);

	List<int> list_no_loop;
	for (int i = 0; i < 10; i++) {
		list_no_loop.push_back(i);
	}
	ASSERT_EQ(list_no_loop.find_loop(list_no_loop), nullptr);

	List<int> list_with_loop;
	for (int i = 0; i < 10; i++) {
		list_with_loop.push_back(i);
	}
	list_with_loop.create_loop(5);
	Node<int>* loop_start_node = list_with_loop.find_loop(list_with_loop);
	ASSERT_NE(loop_start_node, nullptr);
	ASSERT_EQ(loop_start_node->value, 5);

	List<int> list_loop_at_head;
	list_loop_at_head.push_back(1);
	list_loop_at_head.push_back(2);
	list_loop_at_head.create_loop(0);
	Node<int>* loop_head_node = list_loop_at_head.find_loop(list_loop_at_head);
	ASSERT_NE(loop_head_node, nullptr);
	ASSERT_EQ(loop_head_node->value, 1);
}