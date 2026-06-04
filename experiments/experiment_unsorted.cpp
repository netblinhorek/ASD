#include "experiment_bench.h"
#include "experiment_hash_factory.h"

#include "../lib_TableHashC/table_hash_c.h"
#include "../lib_TableHashOA/table_hash_ao.h"

#include <iostream>
#include <vector>

namespace {

    using bench::HashTableFactory;
    using bench::run_string_key_hash_benchmark;
    using bench::TableValue;

    const std::vector<size_t> kSizes = bench::kBenchmarkSizes;

    void run_linear_and_hash(std::vector<bench::RowResult>& rows) {
        run_string_key_hash_benchmark<
            HashTableC<std::string, TableValue>,
            HashTableFactory<HashTableC<std::string, TableValue>>>(
                "Hash (chaining)", kSizes, rows,
                "O(1) avg.", "O(1) avg.", "O(1) avg.",
                bench::hash_capacity_chain);

        run_string_key_hash_benchmark<
            HashTableAO<std::string, TableValue>,
            HashTableFactory<HashTableAO<std::string, TableValue>>>(
                "Hash (open addr.)", kSizes, rows,
                "O(1) avg.", "O(1) avg.", "O(1) avg.",
                bench::hash_capacity_open);
    }

}  // namespace

void bench_unsorted_arr(std::vector<bench::RowResult>& rows);
void bench_unsorted_list(std::vector<bench::RowResult>& rows);
void bench_unsorted_tree(std::vector<bench::RowResult>& rows);

void run_unsorted_experiments() {
    std::cout << "The results of experiments with the unsorted table are shown in Table 1, "
        << "with the sorted table - in Table 2.\n";

    bench::print_table_header(
        1,
        "Efficiency comparison of various data storage methods as an unsorted table");

    std::vector<bench::RowResult> rows;
    bench_unsorted_arr(rows);
    bench_unsorted_list(rows);
    run_linear_and_hash(rows);
    bench_unsorted_tree(rows);
}