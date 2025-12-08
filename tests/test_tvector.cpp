#include <gtest/gtest.h>
#include "tvector.h"
#include <iostream>
#include <cassert>
#include <iostream>
#include <string>
#include <sstream>  
#include <stdexcept> 
#include <cstdio>
#include <Windows.h>
#include <chrono>
#include <fcntl.h>
#include <io.h>
#define EPSILON 0.000001

TEST(TestTVector, test_default_constructor_size_and_capacity) {
    TVector<int> vec;
    ASSERT_EQ(vec.size(), 0);
    ASSERT_EQ(vec.capacity(), 0);
}


TEST(TestTVector, test_size_constructor_size_and_capacity) {
    const size_t test_size = 5;
    TVector<int> vec(test_size);
    ASSERT_EQ(vec.size(), test_size);
    ASSERT_GE(vec.capacity(), test_size);
}


TEST(TestTVector, test_size_constructor_default_initialization) {
    TVector<int> vec(2);
    ASSERT_EQ(vec[0], 0);  
    ASSERT_EQ(vec[1], 0);
}

TEST(TestTVector, test_constructor_zero_size) {
    TVector<int> vec(0);
    ASSERT_EQ(vec.size(), 0);
    ASSERT_GE(vec.capacity(), 0);
}

TEST(TestTVector, test_constructor_with_array) {
    int arr[] = { 1, 2, 3, 4, 5 };
    TVector<int> vec(arr, 5);

    ASSERT_EQ(vec.size(), 5);
    ASSERT_EQ(vec[0], 1);
    ASSERT_EQ(vec[4], 5);
}


TEST(TestTVector, test_copy_constructor_size_and_capacity) {
    TVector<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    TVector<int> copy(original);
    ASSERT_EQ(copy.size(), original.size());
    ASSERT_EQ(copy.capacity(), original.capacity());
}


TEST(TestTVector, test_copy_constructor_elements) {
    TVector<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    TVector<int> copy(original);
    ASSERT_EQ(copy[0], original[0]);
    ASSERT_EQ(copy[1], original[1]);
    ASSERT_EQ(copy[2], original[2]);

    copy[0] = 100;
    ASSERT_NE(copy[0], original[0]);
}


TEST(TestTVector, test_basic_operations) {
    int arr[] = { 1, 2, 3, 4, 5 };
    TVector<int> vec(arr, 5);

    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec.get(0), 1);
    EXPECT_EQ(vec.get(4), 5);
}

TEST(TestTVector, test_get_set_operations) {
    TVector<int> vec(3);
    vec.set(0, 10);
    vec.set(1, 20);
    vec.set(2, 30);

    EXPECT_EQ(vec.get(0), 10);
    EXPECT_EQ(vec.get(1), 20);
    EXPECT_EQ(vec.get(2), 30);

    EXPECT_THROW(vec.get(5), std::out_of_range);
    EXPECT_THROW(vec.set(5, 100), std::out_of_range);
}

TEST(TestTVector, test_copy_constructor) {
    int arr[] = { 1, 2, 3 };
    TVector<int> vec1(arr, 3);
    TVector<int> vec2(vec1);

    EXPECT_EQ(vec2.size(), 3);
    EXPECT_EQ(vec2.get(0), 1);
    EXPECT_EQ(vec2.get(1), 2);
    EXPECT_EQ(vec2.get(2), 3);
}

TEST(TestTVector, test_assignment_operator_self_assignment) {
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v = v;
    ASSERT_EQ(v.size(), 2);
    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[1], 2);
}

TEST(TestTVector, test_emplace) {
    TVector<std::string> v;
    v.push_back("world");

    ASSERT_EQ(v.size(), 1);
    ASSERT_EQ(v[0], "world");

    v.emplace(0, "hello"); 

    ASSERT_EQ(v.size(), 2);
    ASSERT_EQ(v[0], "hello");
    ASSERT_EQ(v[1], "world");
}

TEST(TestTVector, test_pop_back_changes_state) {
    TVector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    size_t old_capacity = v.capacity();
    v.pop_back(); 
    ASSERT_EQ(v.size(), 2);
    ASSERT_EQ(v.capacity(), old_capacity);
    ASSERT_EQ(v[1], 20);
}

TEST(TestTVector, test_out_of_range_access_empty) {
    TVector<int> v;
    ASSERT_THROW(v[0], std::out_of_range);
    v.push_back(1);
    ASSERT_THROW(v[1], std::out_of_range);
}

TEST(TestTVector, test_clear_behavior) {
    TVector<int> v;

    for (int i = 0; i < 100; ++i) {
        v.push_back(i);
    }
    v.clear();
    ASSERT_EQ(v.size(), 0);
    ASSERT_GE(v.capacity(), STEP_OF_CAPACITY);

    v.push_back(3);
    ASSERT_EQ(v.size(), 1);
    ASSERT_EQ(v[0], 3);
}


TEST(TestTVector, test_push_front_element) {
    TVector<int> v;
    v.push_back(1);
    v.push_front(2);
    ASSERT_EQ(2, v[0]);
    ASSERT_EQ(1, v[1]);
}

TEST(TestTVector, test_insert_at_different_positions) {
    TVector<int> v;

    v.insert(1, 0);  
    ASSERT_EQ(v.size(), 1);
    ASSERT_EQ(v[0], 1);

    v.insert(3, 1);  
    ASSERT_EQ(v.size(), 2);
    ASSERT_EQ(v[1], 3);
}


TEST(TestTVector, test_insert_out_of_range) {
    TVector<int> v;
    v.push_back(1);

    ASSERT_THROW(v.insert(2, 5), std::out_of_range);
}

TEST(TestTVector, test_insert_range_beginning) {
    TVector<int> v;
    v.push_back(3);
    v.push_back(4);

    int values[] = { 1, 2 };
    v.insert_range(0, values, 2);

    ASSERT_EQ(v.size(), 4);
    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[1], 2);
    ASSERT_EQ(v[2], 3);
    ASSERT_EQ(v[3], 4);
}

TEST(TestTVector, test_remove_from_empty_vector) {
    TVector<int> v;
    ASSERT_THROW(v.pop_front(), std::out_of_range);
    ASSERT_THROW(v.pop_back(), std::out_of_range);
    ASSERT_THROW(v.erase(0), std::out_of_range);
    ASSERT_THROW(v.erase_range(0, 1), std::out_of_range);
}

TEST(TestTVector, test_front_back_methods) {
    TVector<int> v;

    ASSERT_THROW(v.front(), std::out_of_range);
    ASSERT_THROW(v.back(), std::out_of_range);

    v.push_back(42);
    ASSERT_EQ(v.front(), 42);
    ASSERT_EQ(v.back(), 42);

    v.push_back(100);
    ASSERT_EQ(v.front(), 42);
    ASSERT_EQ(v.back(), 100);
}

TEST(TestTVector, test_at_out_of_range) {
    TVector<int> v;
    v.push_back(1);

    ASSERT_THROW(v.at(1), std::out_of_range);
    ASSERT_THROW(v.at(100), std::out_of_range);
}

TEST(TestTVector, test_erase_until_empty) {
    TVector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3); 

    v.erase_back(1);
    ASSERT_EQ(v.size(), 2);
    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[1], 2);

    v.erase(1);
    ASSERT_EQ(v.size(), 1);
    ASSERT_EQ(v[0], 1);

    v.erase_front(1);
    ASSERT_EQ(v.size(), 0);
    ASSERT_TRUE(v.is_empty());
}

TEST(TestTVector, test_erase_range) {
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.erase_range(1, 2);
    ASSERT_EQ(static_cast<size_t>(2), v.size());  
    ASSERT_EQ(1, v[0]);                           
    ASSERT_EQ(4, v[1]);                           
}

TEST(TestTVector, test_assign_first_element) {
    TVector<int> v;
    v.assign(3, 7);
    ASSERT_EQ(static_cast<size_t>(3), v.size());
    ASSERT_EQ(7, v[0]);
    ASSERT_EQ(7, v[1]);
}


TEST(TestTVector, test_at_element) {
    TVector<int> v;
    v.push_back(5);
    ASSERT_EQ(5, v.at(0));
}

TEST(TestTVector, test_shrink_to_fit_capacity) {
    TVector<int> v;
    for (int i = 0; i < 10; ++i) v.push_back(i);
    v.shrink_to_fit();
    ASSERT_EQ(v.size(), v.capacity());
}

TEST(TestTVector, test_reserve_increases_capacity) {
    TVector<int> v;
    size_t old_capacity = v.capacity();
    v.reserve(old_capacity + 10);
    ASSERT_GT(v.capacity(), old_capacity);
    ASSERT_EQ(v.size(), 0);
}

TEST(TestTVector, test_resize_grow) {
    TVector<int> v;
    v.push_back(1);
    v.resize(5, 9);
    ASSERT_EQ(static_cast<size_t>(5), v.size());
    ASSERT_EQ(9, v[4]);
}

TEST(TestTVector, test_resize_to_zero) {
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.resize(0);
    ASSERT_EQ(v.size(), 0);
    ASSERT_TRUE(v.is_empty());
}

TEST(TestTVector, test_states_after_construction) {
    TVector<int> vec(3);
    const State* states = vec.states();

    for (size_t i = 0; i < 3; ++i) {
        ASSERT_EQ(states[i], State::busy) << "Element at index " <<
            i << " should be busy";
    }
}

TEST(TestTVector, test_resize_with_default_value) {
    TVector<int> v;
    v.resize(5, 42);
    ASSERT_EQ(v.size(), 5);
    for (size_t i = 0; i < 5; ++i) {
        ASSERT_EQ(v[i], 42);
    }
}

TEST(TestTVector, test_shrink_to_fit_empty) {
    TVector<int> v;
    v.shrink_to_fit();
    ASSERT_EQ(v.size(), 0);
    ASSERT_EQ(v.capacity(), 0);
}

TEST(TestTVector, test_resize_shrink_size) {
    TVector<int> v;
    v.push_back(1);
    v.resize(5, 9);
    v.resize(2);
    ASSERT_EQ(static_cast<size_t>(2), v.size());
}

TEST(TestTVector, test_clear_size) {
    TVector<int> v;
    v.push_back(1);
    v.clear();
    ASSERT_EQ(static_cast<size_t>(0), v.size());
}

TEST(TestTVector, test_operator_eq_equal) {
    TVector<int> v1;
    TVector<int> v2;
    v1.push_back(1);
    v2.push_back(1);
    ASSERT_TRUE(v1 == v2);
}

TEST(TestTVector, test_operator_eq_not_equal) {
    TVector<int> v1;
    TVector<int> v2;
    v1.push_back(1);
    v2.push_back(2);
    ASSERT_FALSE(v1 == v2);
    ASSERT_TRUE(v1 != v2);
}


TEST(TestTVector, test_find_not_found) {
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);

    ASSERT_EQ(find_first(v, 3), -1);
    ASSERT_EQ(find_last(v, 3), -1);
}


TEST(TestTVector, test_find_first_existing) {
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(1);
    ASSERT_EQ(0, find_first(v, 1));
    ASSERT_EQ(2, find_last(v, 1));

}


TEST(TestTVector, test_swap) {
    int a = 1, b = 2;
    swap(&a, &b);

    ASSERT_EQ(2, a);
    ASSERT_EQ(1, b);
}

TEST(TestTVector, test_randomize) {
    TVector<int> v;
    v.push_front(3);
    v.push_front(2);
    v.push_front(1);
    TVector<int> original = v; 

    randomize(v);

    ASSERT_EQ(v.size(), original.size());  
    ASSERT_NE(v, original);  
}

TEST(TestTVector, test_hoara_sort) {
    TVector<int> v;
    v.push_back(3);
    v.push_back(1);
    v.push_back(2);
    hoara_sort(v);

    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(2, v[1]);
    ASSERT_EQ(3, v[2]);
}


TEST(TestTVector, test_erase_back_empty_vector) {
    TVector<int> v;
    ASSERT_THROW(v.erase_back(1), std::out_of_range);
}

TEST(TestTVector, test_states_after_operations) {
    TVector<int> vec;

    vec.push_back(10);
    vec.push_back(20);
    ASSERT_EQ(vec.states()[0], State::busy);
    ASSERT_EQ(vec.states()[1], State::busy);

    vec.push_back(30);
    vec.pop_back();
    ASSERT_EQ(vec.states()[2], State::deleted);

    vec.insert(25, 1);
    ASSERT_EQ(vec.states()[1], State::busy);

    vec.clear();
    ASSERT_EQ(vec.states()[0], State::empty);
}

TEST(TestTVectorIterator, test_iterator_increment) {
    TVector<int> empty_vec;
    auto empty_it = empty_vec.begin();
    ASSERT_EQ(empty_it, empty_vec.end());

    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    auto it = v.begin();
    ASSERT_EQ(*it, 1);
    ++it;
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 3);
    ++it;
    ASSERT_EQ(it, v.end());
}

TEST(TestTVectorIterator, test_iterator_decrement) {
    TVector<int> empty_vec;
    auto empty_it = empty_vec.begin();
    ASSERT_EQ(empty_it, empty_vec.end());

    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    auto it = v.end();
    --it;
    ASSERT_EQ(*it, 3);
    --it;
    ASSERT_EQ(*it, 2);
    --it;
    ASSERT_EQ(*it, 1);
}

TEST(TestTVectorIterator, test_iterator_minus_equal) {
    TVector<int> empty_vec;
    auto empty_it = empty_vec.begin();
    ASSERT_EQ(empty_it, empty_vec.end());

    TVector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    auto it = v.end();
    it -= 1;
    ASSERT_EQ(*it, 30);
    it -= 1;
    ASSERT_EQ(*it, 20);
    it -= 1;
    ASSERT_EQ(*it, 10);
}

TEST(TestTVectorIterator, test_iterator_postfix_increment) {
    TVector<int> empty_vec;
    auto empty_it = empty_vec.begin();
    ASSERT_EQ(empty_it, empty_vec.end());

    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    auto it = v.begin();
    ASSERT_EQ(*it, 1);
    it++;
    ASSERT_EQ(*it, 2);
    it++;
    ASSERT_EQ(*it, 3);
    it++;
    ASSERT_EQ(it, v.end());
}

TEST(TestTVectorIterator, test_iterator_postfix_decrement) {
    TVector<int> empty_vec;
    auto empty_it = empty_vec.begin();
    ASSERT_EQ(empty_it, empty_vec.end());

    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    auto it = v.end();
    it--;
    ASSERT_EQ(*it, 3);
    it--;
    ASSERT_EQ(*it, 2);
    it--;
    ASSERT_EQ(*it, 1);
}