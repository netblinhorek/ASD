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

TEST(TestTVector, test_default_constructor_size) {
    TVector<int> vec;
    ASSERT_EQ(vec.size(), 0);
}

TEST(TestTVector, test_default_constructor_capacity) {
    TVector<int> vec;
    ASSERT_EQ(vec.capacity(), 0);
}

TEST(TestTVector, test_size_constructor_size) {
    const size_t test_size = 5;
    TVector<int> vec(test_size);
    ASSERT_EQ(vec.size(), test_size);
}

TEST(TestTVector, test_size_constructor_capacity) {
    const size_t test_size = 5;
    TVector<int> vec(test_size);
    ASSERT_GE(vec.capacity(), test_size);
}

TEST(TestTVector, test_size_constructor_default_initialization) {
    const size_t test_size = 5;
    TVector<int> vec(test_size);
    for (size_t i = 0; i < test_size; ++i) {
        ASSERT_EQ(vec[i], int()) << "Element at index " << i << " not default initialized";
    }
}

TEST(TestTVector, test_size_constructor_element_assignment) {
    const size_t test_size = 5;
    TVector<int> vec(test_size);
    for (size_t i = 0; i < test_size; ++i) {
        vec[i] = static_cast<int>(i);
        ASSERT_EQ(vec[i], static_cast<int>(i)) << "Failed to set element at index " << i;
    }
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

TEST(TestTVector, test_constructor_with_empty_array) {
    TVector<int> vec(nullptr, 0);

    ASSERT_EQ(vec.size(), 0);
    ASSERT_TRUE(vec.is_empty());
}

TEST(TestTVector, test_copy_constructor_size) {
    TVector<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    TVector<int> copy(original);
    ASSERT_EQ(copy.size(), original.size());
}

TEST(TestTVector, test_copy_constructor_capacity) {
    TVector<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    TVector<int> copy(original);
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
}

TEST(TestTVector, test_copy_constructor_independence) {
    TVector<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    TVector<int> copy(original);
    copy[0] = 100;
    ASSERT_NE(copy[0], original[0]);
}
TEST(TestTVector, test_destructor_with_elements) {
    TVector<int>* v = new TVector<int>();
    v->push_back(1);
    v->push_back(2);
    ASSERT_NO_THROW(delete v); 
}

TEST(TestTVector, test_destructor_empty) {
    TVector<int>* v = new TVector<int>();
    ASSERT_NO_THROW(delete v);
}
TEST(TestTVector, BasicOperations) {
    int arr[] = { 1, 2, 3, 4, 5 };
    TVector<int> vec(arr, 5);

    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec.get(0), 1);
    EXPECT_EQ(vec.get(4), 5);
}

TEST(TestTVector, GetSetOperations) {
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
}

TEST(TestTVector, test_out_of_range_access_index_1) {
    TVector<int> v;
    v.push_back(1);
    ASSERT_THROW(v[1], std::out_of_range);
}

TEST(TestTVector, test_out_of_range_access_at) {
    TVector<int> v;
    v.push_back(1);
    ASSERT_THROW(v.at(1), std::out_of_range);
}

TEST(TestTVector, test_assignment_operator_size) {
    TVector<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    TVector<int> copy;
    copy = original;
    ASSERT_EQ(copy.size(), original.size());
}

TEST(TestTVector, test_assignment_operator_capacity) {
    TVector<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    TVector<int> copy;
    copy = original;
    ASSERT_EQ(copy.capacity(), original.capacity());
}

TEST(TestTVector, test_assignment_operator_elements) {
    TVector<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    TVector<int> copy;
    copy = original;
    ASSERT_EQ(copy[0], original[0]);
    ASSERT_EQ(copy[1], original[1]);
    ASSERT_EQ(copy[2], original[2]);
}
TEST(TestTVector, test_clear_memory_management) {
    TVector<int> v;
    for (int i = 0; i < 100; ++i) {
        v.push_back(i);
    }
    v.clear();

    ASSERT_EQ(v.size(), 0);
    ASSERT_GE(v.capacity(), STEP_OF_CAPACITY);
}

TEST(TestTVector, test_clear_then_reuse) {
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.clear();

    v.push_back(3);
    ASSERT_EQ(v.size(), 1);
    ASSERT_EQ(v[0], 3);
}

TEST(TestTVector, test_push_back_size) {
    TVector<int> v;
    v.push_back(42);
    ASSERT_EQ(static_cast<size_t>(1), v.size());
}

TEST(TestTVector, test_push_back_element) {
    TVector<int> v;
    v.push_back(42);
    ASSERT_EQ(42, v[0]);
}

TEST(TestTVector, test_push_front_element) {
    TVector<int> v;
    v.push_back(1);
    v.push_front(2);
    ASSERT_EQ(2, v[0]);
    ASSERT_EQ(1, v[1]);
}
TEST(TestTVector, test_insert) {
    TVector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.insert(2, 1);

    ASSERT_EQ(static_cast<size_t>(3), v.size());
    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(2, v[1]);
    ASSERT_EQ(3, v[2]);
}
TEST(TestTVector, test_insert_beginning) {
    TVector<int> v;
    v.push_back(2);
    v.push_back(3);
    v.insert(1, 0);

    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[1], 2);
    ASSERT_EQ(v[2], 3);
}

TEST(TestTVector, test_insert_end) {
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.insert(3, 2);

    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v[2], 3);
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

TEST(TestTVector, test_pop_back) {
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.pop_back();

    ASSERT_EQ(static_cast<size_t>(1), v.size());
    ASSERT_EQ(1, v[0]);
}
TEST(TestTVector, test_pop_front_empty) {
    TVector<int> v;
    ASSERT_THROW(v.pop_front(), std::out_of_range);
}

TEST(TestTVector, test_pop_back_empty) {
    TVector<int> v;
    ASSERT_THROW(v.pop_back(), std::out_of_range);
}

TEST(TestTVector, test_erase_empty) {
    TVector<int> v;
    ASSERT_THROW(v.erase(0), std::out_of_range);
}

TEST(TestTVector, test_erase_out_of_range) {
    TVector<int> v;
    v.push_back(1);

    ASSERT_THROW(v.erase(1), std::out_of_range);
}

TEST(TestTVector, test_erase_range_empty) {
    TVector<int> v;
    ASSERT_THROW(v.erase_range(0, 1), std::out_of_range);
}

TEST(TestTVector, test_erase_range_invalid) {
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);

    ASSERT_THROW(v.erase_range(1, 2), std::out_of_range);
}
TEST(TestTVector, test_front_empty) {
    TVector<int> v;
    ASSERT_THROW(v.front(), std::out_of_range);
}
TEST(TestTVector, test_back_empty) {
    TVector<int> v;
    ASSERT_THROW(v.back(), std::out_of_range);
}

TEST(TestTVector, test_front_back_single_element) {
    TVector<int> v;
    v.push_back(42);

    ASSERT_EQ(v.front(), 42);
    ASSERT_EQ(v.back(), 42);
}

TEST(TestTVector, test_at_out_of_range) {
    TVector<int> v;
    v.push_back(1);

    ASSERT_THROW(v.at(1), std::out_of_range);
    ASSERT_THROW(v.at(100), std::out_of_range);
}
TEST(TestTVector, test_pop_front) {
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.pop_front();

    ASSERT_EQ(static_cast<size_t>(1), v.size());
    ASSERT_EQ(2, v[0]);
}

TEST(TestTVector, test_erase) {
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.erase(1);

    ASSERT_EQ(static_cast<size_t>(2), v.size());
    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(3, v[1]);
}

TEST(TestTVector, test_erase_front) {
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.erase_front(2);

    ASSERT_EQ(static_cast<size_t>(1), v.size());
    ASSERT_EQ(3, v[0]);
}

TEST(TestTVector, test_erase_back) {
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.erase_back(2);

    ASSERT_EQ(static_cast<size_t>(1), v.size());
    ASSERT_EQ(1, v[0]);
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


TEST(TestTVector, test_assign_size) {
    TVector<int> v;
    v.assign(3, 7);
    ASSERT_EQ(static_cast<size_t>(3), v.size());
}

TEST(TestTVector, test_assign_first_element) {
    TVector<int> v;
    v.assign(3, 7);
    ASSERT_EQ(7, v[0]);
}

TEST(TestTVector, test_assign_second_element) {
    TVector<int> v;
    v.assign(3, 7);
    ASSERT_EQ(7, v[1]);
}

TEST(TestTVector, test_assign_third_element) {
    TVector<int> v;
    v.assign(3, 7);
    ASSERT_EQ(7, v[2]);
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
        ASSERT_EQ(states[i], State::busy) << "Element at index " << i << " should be busy";
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
}

TEST(TestTVector, test_operator_neq) {
    TVector<int> v1, v2;
    v1.push_back(1);
    v2.push_back(2);
    ASSERT_TRUE(v1 != v2);
}
TEST(TestTVector, test_find_first_not_found) {
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);

    ASSERT_EQ(find_first(v, 3), -1);
}

TEST(TestTVector, test_find_last_not_found) {
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);

    ASSERT_EQ(find_last(v, 3), -1);
}

TEST(TestTVector, test_find_elems_not_found) {
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);

    int* result = find_elems(v, 3);
    ASSERT_EQ(result[0], -1);
    delete[] result;
}

TEST(TestTVector, test_find_elems_multiple) {
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(1);
    v.push_back(3);
    v.push_back(1);

    int* result = find_elems(v, 1);
    ASSERT_EQ(result[0], 0);
    ASSERT_EQ(result[1], 2);
    ASSERT_EQ(result[2], 4);
    delete[] result;
}
TEST(TestTVector, test_find_first_existing) {
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(1);
    ASSERT_EQ(0, find_first(v, 1));
}

TEST(TestTVector, test_find_first_another_element) {
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(1);
    ASSERT_EQ(1, find_first(v, 2));
}

TEST(TestTVector, test_find_last_existing) {
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(1);
    ASSERT_EQ(2, find_last(v, 1));
}

TEST(TestTVector, test_find_last_another_element) {
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(1);
    ASSERT_EQ(1, find_last(v, 2));
}
TEST(TestTVector, test_find_elems) {
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(1);
    ASSERT_EQ(2, find_last(v, 1));
    ASSERT_EQ(1, find_last(v, 2));

}
TEST(TestTVector, test_find_elems_idxs) {
    TVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(1);
    int* idxs = find_elems(v, 1);
    ASSERT_EQ(0, idxs[0]);
    ASSERT_EQ(2, idxs[1]);
    delete[] idxs;

}
TEST(TestTVector, test_swap) {
    int a = 1, b = 2;
    swap(&a, &b);

    ASSERT_EQ(2, a);
    ASSERT_EQ(1, b);

}
TEST(TestTVector, test_randomize) {
    TVector<int> v;
    for (int i = 0; i < 10; ++i) v.push_back(i);
    randomize(v);

    int sum = 0;
    for (size_t i = 0; i < v.size(); ++i) sum += v[i];

    ASSERT_EQ(static_cast<size_t>(10), v.size());
    ASSERT_EQ(45, sum);
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

TEST(TestTVector, test_complex_sequence) {
    TVector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    ASSERT_EQ(static_cast<size_t>(3), v.size());
    ASSERT_EQ(10, v[0]);
    ASSERT_EQ(20, v[1]);
    ASSERT_EQ(30, v[2]);
    v.erase(1);

    ASSERT_EQ(static_cast<size_t>(2), v.size());
    ASSERT_EQ(10, v[0]);
    ASSERT_EQ(30, v[1]);
    v.erase_front(1);

    ASSERT_EQ(static_cast<size_t>(1), v.size());
    ASSERT_EQ(30, v[0]);
    v.erase_back(1);

    ASSERT_EQ(static_cast<size_t>(0), v.size());
    ASSERT_TRUE(v.is_empty());
}

TEST(TestTVector, test_erase_back_empty_vector) {
    TVector<int> v;
    ASSERT_THROW(v.erase_back(1), std::out_of_range);
}

TEST(TestTVector, test_push_front_after_operations) {
    TVector<int> v;

    v.push_front(100);
    v.push_front(200);

    ASSERT_EQ(static_cast<size_t>(2), v.size());
    ASSERT_EQ(200, v[0]);
    ASSERT_EQ(100, v[1]);
}


TEST(TestTVector, test_states_after_push_back) {
    TVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);

    const State* states = vec.states();
    ASSERT_EQ(states[0], State::busy);
    ASSERT_EQ(states[1], State::busy);
}

TEST(TestTVector, test_states_after_pop_back) {
    TVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    vec.pop_back();
    const State* states = vec.states();

    size_t busy_count = 0;
    size_t deleted_count = 0;

    for (size_t i = 0; i < vec.capacity(); ++i) {
        if (states[i] == State::busy) busy_count++;
        if (states[i] == State::deleted) deleted_count++;
    }

    ASSERT_EQ(busy_count, 2);
    ASSERT_EQ(deleted_count, 1);
}

TEST(TestTVector, test_states_after_erase) {
    TVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    vec.erase(1);
    const State* states = vec.states();

    size_t busy_count = 0;
    for (size_t i = 0; i < vec.capacity(); ++i) {
        if (states[i] == State::busy) busy_count++;
    }

    ASSERT_EQ(busy_count, 2); 
}

TEST(TestTVector, test_states_after_clear) {
    TVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    vec.clear();
    const State* states = vec.states();

    for (size_t i = 0; i < vec.capacity(); ++i) {
        ASSERT_EQ(states[i], State::empty) << "Element at index " << i << " should be empty after clear";
    }
}

TEST(TestTVector, test_states_after_insert) {
    TVector<int> vec;
    vec.push_back(10);
    vec.push_back(30);

    vec.insert(20, 1); 
    const State* states = vec.states();

    size_t busy_count = 0;
    for (size_t i = 0; i < vec.capacity(); ++i) {
        if (states[i] == State::busy) busy_count++;
    }

    ASSERT_EQ(busy_count, 3);
}

TEST(TestTVector, test_states_after_compact) {
    TVector<int> vec;
    for (int i = 0; i < 20; ++i) {
        vec.push_back(i);
    }

    for (int i = 0; i < 10; ++i) {
        vec.pop_back();
    }

    const State* states = vec.states();

    bool has_deleted = false;
    for (size_t i = 0; i < vec.capacity(); ++i) {
        if (states[i] == State::deleted) {
            has_deleted = true;
            break;
        }
    }

    ASSERT_FALSE(has_deleted) << "After compact, there should be no deleted states";
}

TEST(TestTVector, test_states_after_resize_grow) {
    TVector<int> vec;
    vec.push_back(10);
    vec.resize(5, 0);

    const State* states = vec.states();

    for (size_t i = 0; i < 5; ++i) {
        ASSERT_EQ(states[i], State::busy) << "Element at index " << i << " should be busy after resize";
    }
}

TEST(TestTVector, test_states_after_resize_shrink) {
    TVector<int> vec;
    for (int i = 0; i < 5; ++i) {
        vec.push_back(i);
    }

    vec.resize(2);
    const State* states = vec.states();

    for (size_t i = 0; i < 2; ++i) {
        ASSERT_EQ(states[i], State::busy);
    }
    for (size_t i = 2; i < vec.capacity(); ++i) {
        ASSERT_EQ(states[i], State::empty);
    }
}

TEST(TestTVector, test_states_empty_cells_after_construction) {
    TVector<int> vec(5);

    const State* states = vec.states();
    for (size_t i = 5; i < vec.capacity(); ++i) {
        ASSERT_EQ(states[i], State::empty) << "Empty cell at index " << i << " should have empty state";
    }
}

TEST(TestTVector, test_states_after_multiple_operations) {
    TVector<int> vec;

    vec.push_back(1);
    vec.push_back(2);
    vec.pop_back();
    vec.push_back(3);
    vec.insert(4, 1);
    vec.erase(0);

    const State* states = vec.states();

    size_t busy_count = 0;
    size_t deleted_count = 0;
    size_t empty_count = 0;

    for (size_t i = 0; i < vec.capacity(); ++i) {
        switch (states[i]) {
        case State::busy: busy_count++; break;
        case State::deleted: deleted_count++; break;
        case State::empty: empty_count++; break;
        }
    }

    ASSERT_EQ(busy_count, 2);
    ASSERT_GE(empty_count, 0);
}

TEST(TestTVector, test_state_transitions) {
    TVector<int> vec;

    ASSERT_TRUE(vec.is_empty());

    vec.push_back(42);
    ASSERT_EQ(vec.states()[0], State::busy);

    vec.pop_back();
    ASSERT_EQ(vec.states()[0], State::deleted);
}