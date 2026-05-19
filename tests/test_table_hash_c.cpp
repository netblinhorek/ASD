#include <gtest/gtest.h>
#include "../lib_TableHashC/table_hash_c.h"
#include "../lib_Polynom/polynom.h"
#define EPSILON 0.000001

TEST(TestHashTableC, test_unsorted_table_on_tree_empty) {
    HashTableC<std::string, Polynom> table_ao;
    table_ao.print();
    ASSERT_TRUE(table_ao.is_empty());
}

TEST(TestHashTableC, test_unsorted_table_on_tree_erase) {
    HashTableC<std::string, Polynom> table_on_tree;
    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("3x^2 + 2y - 5z + 7");

    table_on_tree.insert("pol1", p1);
    table_on_tree.insert("pol2", p2);
    table_on_tree.erase("pol2");

    ASSERT_FALSE(table_on_tree.is_empty());
}

TEST(TestHashTableC, test_unsorted_table_on_tree_found) {
    HashTableC<std::string, Polynom> table_on_tree;
    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("3x^2 + 2y - 5z + 7");

    table_on_tree.insert("pol1", p1);
    table_on_tree.insert("pol2", p2);

    ASSERT_NO_THROW(table_on_tree.found("pol2"));
    EXPECT_EQ(table_on_tree.found("pol2"), p2);
}

TEST(TestHashTableC, test_unsorted_table_on_tree_found_with_erase) {
    HashTableC<std::string, Polynom> table_on_tree;
    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("3x^2 + 2y - 5z + 7");

    table_on_tree.insert("pol1", p1);
    table_on_tree.insert("pol2", p2);
    table_on_tree.erase("pol2");

    ASSERT_NO_THROW(table_on_tree.found("pol1"));
    EXPECT_EQ(table_on_tree.found("pol1"), p1);
}

TEST(TestHashTableC, test_unsorted_table_on_tree_found_with_throw) {
    HashTableC<std::string, Polynom> table_on_tree;
    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("3x^2 + 2y - 5z + 7");

    table_on_tree.insert("pol1", p1);
    table_on_tree.insert("pol2", p2);
    table_on_tree.erase("pol2");

    ASSERT_THROW(table_on_tree.found("pol2"), std::logic_error);
}

TEST(TestHashTableC, test_insert_duplicate_key) {
    HashTableC<std::string, Polynom> table;
    Polynom p1("x+y");
    Polynom p2("z");

    table.insert("pol1", p1);
    ASSERT_THROW(table.insert("pol1", p2), std::logic_error);
    ASSERT_EQ(table.found("pol1"), p1);
    ASSERT_NE(table.found("pol1"), p2);
}

TEST(TestHashTableC, test_erase_with_throw) {
    HashTableC<std::string, Polynom> table;
    ASSERT_THROW(table.erase("pol1"), std::logic_error);
    Polynom p("x");
}

TEST(TestHashTableC, test_erase_middle_and_find_others) {
    HashTableC<std::string, Polynom> table;
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
}

TEST(TestHashTableC, test_clear_and_reinsert) {
    HashTableC<std::string, Polynom> table;
    Polynom p1("1");
    Polynom p2("2");

    table.insert("a", p1);
    table.erase("a");
    ASSERT_TRUE(table.is_empty());

    table.insert("b", p2);
    ASSERT_EQ(table.found("b"), p2);
}

TEST(TestHashTableC, test_function_print) {
    HashTableC<std::string, Polynom> table;
    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("3x^2 + 2y - 5z + 7");
    Polynom p3("3x^20 + 5x^19 - 2x^18 + 7x^17 - 4x^16 + 9x^15");

    table.insert("pol1", p1);
    table.insert("pol2", p2);
    ASSERT_THROW(table.insert("pol2", Polynom("3x^2 + 2y - 5z + 6")), std::logic_error);
    table.insert("pol89", p3);

    table.print();
}

TEST(TestHashTableC, test_full_table_with_collisions_and_deletions) {
    HashTableC<std::string, Polynom> table(10);

    for (int i = 0; i < 10; i++) {
        std::string key = "key_" + std::to_string(i);
        std::string poly_str = std::to_string(i) + "x^2 + " + std::to_string(i) + "x";
        EXPECT_NO_THROW(table.insert(key, Polynom(poly_str)));
    }

    EXPECT_EQ(table.size(), 10);

    EXPECT_NO_THROW(table.erase("key_2"));
    EXPECT_NO_THROW(table.erase("key_5"));
    EXPECT_NO_THROW(table.erase("key_8"));

    EXPECT_EQ(table.size(), 7);

    EXPECT_NO_THROW(table.insert("new_key_2", Polynom("222x^2 + 222x")));
    EXPECT_NO_THROW(table.insert("new_key_5", Polynom("555x^2 + 555x")));
    EXPECT_NO_THROW(table.insert("new_key_8", Polynom("888x^2 + 888x")));

    EXPECT_EQ(table.found("new_key_2"), Polynom("222x^2 + 222x"));
    EXPECT_EQ(table.found("new_key_5"), Polynom("555x^2 + 555x"));
    EXPECT_EQ(table.found("new_key_8"), Polynom("888x^2 + 888x"));

    EXPECT_THROW(table.found("key_2"), std::logic_error);
    EXPECT_THROW(table.found("key_5"), std::logic_error);
    EXPECT_THROW(table.found("key_8"), std::logic_error);

    EXPECT_EQ(table.found("key_0"), Polynom("0x^2 + 0x"));
    EXPECT_EQ(table.found("key_1"), Polynom("1x^2 + 1x"));
    EXPECT_EQ(table.found("key_3"), Polynom("3x^2 + 3x"));
    EXPECT_EQ(table.found("key_4"), Polynom("4x^2 + 4x"));
    EXPECT_EQ(table.found("key_6"), Polynom("6x^2 + 6x"));
    EXPECT_EQ(table.found("key_7"), Polynom("7x^2 + 7x"));
    EXPECT_EQ(table.found("key_9"), Polynom("9x^2 + 9x"));

}

TEST(TestHashTableC, test_operator_bracket_simple) {
    HashTableC<std::string, Polynom> table;

    std::string keys[] = { "k1", "k3", "k2" };
    Polynom values[] = { Polynom("x+1"), Polynom("2y"), Polynom("z-5") };

    for (int i = 0; i < 3; ++i) {
        table.insert(keys[i], values[i]);
    }

    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(table[keys[i]], values[i]);
    }
}
TEST(TestHashTableC, test_collision_handling) {
    HashTableC<std::string, Polynom> table_on_tree(5);

    Polynom p1("3x^2 + 2y - 5z + 7");
    Polynom p2("x^3 + 4y^2 - z + 2");
    Polynom p3("2x^4 - 3y + 5z^2 - 1");
    Polynom p4("xy + yz - zx + 10");

    table_on_tree.insert("pol", p1);
    table_on_tree.insert("lop", p2);
    table_on_tree.insert("olp", p3);
    table_on_tree.insert("key4", p4);

    EXPECT_EQ(table_on_tree.found("pol"), p1);
    EXPECT_EQ(table_on_tree.found("lop"), p2);
    EXPECT_EQ(table_on_tree.found("olp"), p3);
    EXPECT_EQ(table_on_tree.found("key4"), p4);
}