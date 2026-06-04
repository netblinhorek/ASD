#include "experiment_bench.h"
#include "../lib_UnsortedTableOnArr/unsorted_table_on_arr.h"
#include <vector>

namespace {

    using bench::run_int_key_benchmark;
    using bench::TableValue;

    const std::vector<size_t> kSizes = bench::kBenchmarkSizes;

}  

void bench_unsorted_arr(std::vector<bench::RowResult>& rows) {
    run_int_key_benchmark<UnsortedTableM<std::string, TableValue>>(
        "Vector (unsorted)",
        kSizes,
        rows,
        "O(n)",
        "O(n)",
        "O(n)"
    );
}