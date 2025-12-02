#include <gtest/gtest.h>
#include "../lib_Double_List/double_list.h"

TEST(TestDoubleList, test_double_list_constructor) {
    Double_List <int> double_list;
    EXPECT_TRUE(double_list.is_empty());
    EXPECT_EQ(double_list.tail(), nullptr);
    EXPECT_EQ(double_list.head(), nullptr);

    EXPECT_THROW(double_list.pop_front(), std::logic_error);
    EXPECT_THROW(double_list.pop_back(), std::logic_error);
    EXPECT_THROW(double_list.erase_at(0), std::logic_error);
}

TEST(TestDoubleList, test_double_list_push_front) {
    Double_List <int> double_list;
    double_list.push_front(3);
    EXPECT_FALSE(double_list.is_empty());
    EXPECT_EQ(double_list.head()->value, 3);
    EXPECT_EQ(double_list.tail()->value, 3);

    double_list.push_front(2);
    EXPECT_FALSE(double_list.is_empty());
    EXPECT_EQ(double_list.head()->value, 2);
    EXPECT_EQ(double_list.tail()->value, 3);

    EXPECT_THROW(double_list.insert_at(10, 5), std::out_of_range);
}

TEST(TestDoubleList, test_double_list_insert_at) {
    Double_List <int> double_list;
    double_list.push_back(3);
    double_list.push_back(2);
    double_list.push_back(1);
    double_list.pop_front();
    double_list.insert_at(0, 43);
    EXPECT_FALSE(double_list.is_empty());
    EXPECT_EQ(double_list.head()->value, 43);
    EXPECT_EQ(double_list.tail()->value, 1);

    EXPECT_THROW(double_list.insert_at(5, 10), std::out_of_range);
    EXPECT_THROW(double_list.insert_after(nullptr, 5), std::invalid_argument);
    EXPECT_THROW(double_list.insert_before(nullptr, 5), std::invalid_argument);
}

TEST(TestDoubleList, test_double_list_insert_after_middle) {
    Double_List <int> double_list;
    double_list.push_back(1);
    double_list.push_back(2);
    double_list.push_back(4);

    Node<int>* first_node = double_list.head();
    double_list.insert_after(first_node, 3);

    EXPECT_EQ(double_list.head()->value, 1);
    EXPECT_EQ(double_list.head()->next->value, 3);
    EXPECT_EQ(double_list.head()->next->next->value, 2);
    EXPECT_EQ(double_list.tail()->value, 4);

    EXPECT_THROW(double_list.erase_at(10), std::out_of_range);
}

TEST(TestDoubleList, test_double_list_push_back) {
    Double_List <int> double_list;

    double_list.push_back(1);
    EXPECT_FALSE(double_list.is_empty());
    EXPECT_EQ(double_list.head()->value, 1);
    EXPECT_EQ(double_list.tail()->value, 1);

    double_list.push_back(2);
    EXPECT_EQ(double_list.head()->value, 1);
    EXPECT_EQ(double_list.tail()->value, 2);

    EXPECT_THROW(double_list.erase(nullptr), std::logic_error);
}

TEST(TestDoubleList, test_double_list_pop_front) {
    Double_List <int> double_list;

    EXPECT_THROW(double_list.pop_front(), std::logic_error);

    double_list.push_back(3);
    double_list.push_back(2);
    double_list.push_back(1);
    double_list.pop_front();
    EXPECT_FALSE(double_list.is_empty());
    EXPECT_EQ(double_list.head()->value, 2);
    EXPECT_EQ(double_list.tail()->value, 1);

    double_list.pop_front();
    double_list.pop_front();
    EXPECT_TRUE(double_list.is_empty());
    EXPECT_EQ(double_list.head(), nullptr);
    EXPECT_EQ(double_list.tail(), nullptr);
    EXPECT_THROW(double_list.pop_front(), std::logic_error);
}

TEST(TestDoubleList, test_double_list_erase_by_node_middle) {
    Double_List <int> double_list;

    EXPECT_THROW(double_list.erase_at(0), std::logic_error);

    double_list.push_back(1);
    double_list.push_back(2);
    double_list.push_back(3);
    double_list.push_back(4);

    Node<int>* node_to_delete = double_list.head()->next->next;
    double_list.erase(node_to_delete);

    EXPECT_EQ(double_list.head()->value, 1);
    EXPECT_EQ(double_list.head()->next->value, 2);
    EXPECT_EQ(double_list.tail()->value, 4);

    EXPECT_THROW(double_list.erase(nullptr), std::logic_error);
}

TEST(TestDoubleList, test_double_list_pop_back) {
    Double_List <int> double_list;

    EXPECT_THROW(double_list.pop_back(), std::logic_error);

    double_list.push_back(3);
    double_list.push_back(2);
    double_list.push_back(1);
    double_list.pop_back();
    EXPECT_FALSE(double_list.is_empty());
    EXPECT_EQ(double_list.head()->value, 3);
    EXPECT_EQ(double_list.tail()->value, 2);

    double_list.pop_back();
    double_list.pop_back();
    EXPECT_TRUE(double_list.is_empty());
    EXPECT_EQ(double_list.head(), nullptr);
    EXPECT_EQ(double_list.tail(), nullptr);
    EXPECT_THROW(double_list.pop_back(), std::logic_error);
}

TEST(TestDoubleListIterator, test_double_list_read_iterator) {
	Double_List <int> double_list;
	double_list.push_back(10);
	double_list.push_back(20);
	double_list.push_back(30);

	Double_List<int>::Iterator it = double_list.begin();
	EXPECT_EQ(*it, 10);

	++it;
	EXPECT_EQ(*it, 20);

	++it;
	EXPECT_EQ(*it, 30);
}

TEST(TestDoubleListIterator, test_double_list_write_iterator) {
	Double_List <int> double_list;
	double_list.push_back(1);
	double_list.push_back(2);
	double_list.push_back(3);


	Double_List <int>::Iterator it = double_list.begin();
	*it = 100;
	EXPECT_EQ(*it, 100);

	++it;
	*it = 200;
	EXPECT_EQ(*it, 200);
}

TEST(TestDoubleList, test_double_list_size_management) {
    Double_List<int> double_list;
    EXPECT_TRUE(double_list.is_empty());

    double_list.push_front(1);
    EXPECT_FALSE(double_list.is_empty());

    double_list.push_back(2);
    double_list.push_back(3);

    double_list.pop_front();
    EXPECT_FALSE(double_list.is_empty());

    double_list.pop_back();
    double_list.pop_back();
    EXPECT_TRUE(double_list.is_empty());
}

TEST(TestDoubleList, test_double_list_insert_at_beginning) {
    Double_List<int> double_list;
    double_list.push_back(2);
    double_list.push_back(3);

    double_list.insert_at(0, 1);
    EXPECT_EQ(double_list.head()->value, 1);
    EXPECT_EQ(double_list.head()->next->value, 2);
    EXPECT_EQ(double_list.tail()->value, 3);
}

TEST(TestDoubleList, test_double_list_insert_at_end) {
    Double_List<int> double_list;
    double_list.push_back(1);
    double_list.push_back(2);

    double_list.insert_at(2, 3);
    EXPECT_EQ(double_list.head()->value, 1);
    EXPECT_EQ(double_list.head()->next->value, 2);
    EXPECT_EQ(double_list.tail()->value, 3);
}

TEST(TestDoubleList, test_double_list_insert_at_middle) {
    Double_List<int> double_list;
    double_list.push_back(1);
    double_list.push_back(3);

    double_list.insert_at(1, 2);
    EXPECT_EQ(double_list.head()->value, 1);
    EXPECT_EQ(double_list.head()->next->value, 2);
    EXPECT_EQ(double_list.tail()->value, 3);
}

TEST(TestDoubleList, test_double_list_insert_before_head) {
    Double_List<int> double_list;
    double_list.push_back(2);
    double_list.push_back(3);

    Node<int>* head_node = double_list.head();
    double_list.insert_before(head_node, 1);

    EXPECT_EQ(double_list.head()->value, 1);
    EXPECT_EQ(double_list.head()->next->value, 2);
    EXPECT_EQ(double_list.tail()->value, 3);
}

TEST(TestDoubleList, test_double_list_insert_after_tail) {
    Double_List<int> double_list;
    double_list.push_back(1);
    double_list.push_back(2);

    Node<int>* tail_node = double_list.tail();
    double_list.insert_after(tail_node, 3);

    EXPECT_EQ(double_list.head()->value, 1);
    EXPECT_EQ(double_list.head()->next->value, 2);
    EXPECT_EQ(double_list.tail()->value, 3);
}

TEST(TestDoubleList, test_double_list_erase_head) {
    Double_List<int> double_list;
    double_list.push_back(1);
    double_list.push_back(2);
    double_list.push_back(3);

    Node<int>* head_node = double_list.head();
    double_list.erase(head_node);

    EXPECT_EQ(double_list.head()->value, 2);
    EXPECT_EQ(double_list.tail()->value, 3);
}

TEST(TestDoubleList, test_double_list_erase_tail) {
    Double_List<int> double_list;
    double_list.push_back(1);
    double_list.push_back(2);
    double_list.push_back(3);

    Node<int>* tail_node = double_list.tail();
    double_list.erase(tail_node);

    EXPECT_EQ(double_list.head()->value, 1);
    EXPECT_EQ(double_list.tail()->value, 2);
}

TEST(TestDoubleList, test_double_list_erase_single_element) {
    Double_List<int> double_list;
    double_list.push_back(1);

    double_list.erase_at(0);
    EXPECT_TRUE(double_list.is_empty());
    EXPECT_EQ(double_list.head(), nullptr);
    EXPECT_EQ(double_list.tail(), nullptr);
}

TEST(TestDoubleList, test_double_list_clear_operations) {
    Double_List<int> double_list;

    double_list.push_back(1);
    double_list.push_back(2);
    double_list.push_back(3);

    double_list.pop_front();
    double_list.pop_front();
    double_list.pop_front();

    EXPECT_TRUE(double_list.is_empty());
    EXPECT_EQ(double_list.head(), nullptr);
    EXPECT_EQ(double_list.tail(), nullptr);
}


TEST(DoubleListIterator, test_double_list_empty_throws_iterator) {
    Double_List<int> list;
    EXPECT_EQ(list.begin(), list.end());
    auto it1 = list.end();
    EXPECT_THROW(--it1, std::invalid_argument);
    auto it2 = list.begin();
    EXPECT_THROW(++it2, std::invalid_argument);
}

TEST(DoubleListIterator, test_double_list_prefix_increment_iteration) {
    Double_List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_EQ(list.head()->prev, nullptr);
    EXPECT_EQ(list.head()->next->prev, list.head());
    EXPECT_EQ(list.tail()->prev, list.head()->next);

    int expected = 1;
    auto it = list.begin();
    for (; it != list.end(); ++it) {
        EXPECT_EQ(*it, expected);
        expected++;
    }
    EXPECT_EQ(expected, 4); 
    EXPECT_THROW(++it, std::invalid_argument);

}

TEST(DoubleListIterator, test_double_list_postfix_increment_iteration) {
    Double_List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_EQ(list.head()->prev, nullptr);
    EXPECT_EQ(list.head()->next->prev, list.head());
    EXPECT_EQ(list.tail()->prev, list.head()->next);

    int expected = 1;
    auto it = list.begin();
    for (; it != list.end(); it++) {
        EXPECT_EQ(*it, expected);
        expected++;
    }
    EXPECT_EQ(expected, 4);
    EXPECT_THROW(it++, std::invalid_argument);
}

TEST(DoubleListIterator, test_double_list_postfix_decrement_iteration) {
    Double_List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_EQ(list.head()->prev, nullptr);
    EXPECT_EQ(list.head()->next->prev, list.head());
    EXPECT_EQ(list.tail()->prev, list.head()->next);

    int expected = 3;
    auto it = Double_List<int>::Iterator(list.tail());
    for (; it != list.begin(); it--) {
        EXPECT_EQ(*it, expected);
        expected--;
    }
    EXPECT_EQ(*it, 1);

    auto begin_it = list.begin();
    EXPECT_THROW(begin_it--, std::invalid_argument);
}

TEST(DoubleListIterator, test_double_list_prefix_decrement_iteration) {
    Double_List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_EQ(list.head()->prev, nullptr);
    EXPECT_EQ(list.head()->next->prev, list.head());
    EXPECT_EQ(list.tail()->prev, list.head()->next);

    int expected = 3;
    auto it = Double_List<int>::Iterator(list.tail());
    for (; it != list.begin(); --it) {
        EXPECT_EQ(*it, expected);
        expected--;
    }
    EXPECT_EQ(*it, 1);

    auto begin_it = list.begin();
    EXPECT_THROW(--begin_it, std::invalid_argument);
}

TEST(DoubleListIterator, test_double_list_minus_equal_iteration) {
    Double_List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    EXPECT_EQ(list.head()->prev, nullptr);
    EXPECT_EQ(list.head()->next->prev, list.head());
    EXPECT_EQ(list.tail()->prev, list.head()->next);

    int expected = 30;
    auto it = Double_List<int>::Iterator(list.tail());
    for (; it != list.begin(); it -= 1) {
        EXPECT_EQ(*it, expected);
        expected -= 10;
    }
    EXPECT_EQ(*it, 10);

    auto begin_it = list.begin();
    EXPECT_THROW(begin_it-=1, std::invalid_argument);
}
