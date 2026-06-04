#include "experiment_bench.h"

#include "../lib_UnsortedTableOnList/unsorted_table_on_list.h"

#include <vector>

namespace {

    using bench::run_int_key_benchmark;
    using bench::TableValue;

    const std::vector<size_t> kSizes = bench::kBenchmarkSizes;

}  

void bench_unsorted_list(std::vector<bench::RowResult>& rows) {
    run_int_key_benchmark<UnsortedTableL<std::string, TableValue>>(
        "List (unsorted)", kSizes, rows,
        "O(n)", "O(n)", "O(n)");
}