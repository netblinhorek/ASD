#include "experiment_bench.h"
#include "experiment_hash_factory.h"

#include "../lib_UnsortedTableOnArr/unsorted_table_on_arr.h"
#include "../lib_UnsortedTableOnList/unsorted_table_on_list.h"
#include "../lib_TableHashC/table_hash_c.h"
#include "../lib_TableHashOA/table_hash_ao.h"

#include <iostream>
#include <vector>

namespace {

using bench::HashTableFactory;
using bench::run_int_key_benchmark;
using bench::run_string_key_hash_benchmark;
using bench::TableValue;

const std::vector<size_t> kSizes = { 100, 1000, 10000, 100000 };

void run_linear_and_hash(std::vector<bench::RowResult>& rows) {
    run_int_key_benchmark<UnsortedTableM<int, TableValue>>(
        "Vector", kSizes, rows, "O(1) amort.", "O(n)", "O(n)");

    run_int_key_benchmark<UnsortedTableL<int, TableValue>>(
        "List", kSizes, rows, "O(n)", "O(n)", "O(n)");

    run_string_key_hash_benchmark<
        HashTableC<std::string, TableValue>,
        HashTableFactory<HashTableC<std::string, TableValue>>>(
        "Hash (chaining)", kSizes, rows,
        "O(1) avg.", "O(1) avg.", "O(1) avg.");

    run_string_key_hash_benchmark<
        HashTableAO<std::string, TableValue>,
        HashTableFactory<HashTableAO<std::string, TableValue>>>(
        "Hash (open addr.)", kSizes, rows,
        "O(1) avg.", "O(1) avg.", "O(1) avg.");
}

}  // namespace

void bench_unsorted_tree(std::vector<bench::RowResult>& rows);

void run_unsorted_experiments() {
    std::cout << "The results of experiments with the unsorted table are shown in Table 1, "
        << "with the sorted table - in Table 2.\n";

    bench::print_table_header(
        1,
        "Efficiency comparison of various data storage methods as an unsorted table");

    std::vector<bench::RowResult> rows;
    run_linear_and_hash(rows);
    bench_unsorted_tree(rows);
}
