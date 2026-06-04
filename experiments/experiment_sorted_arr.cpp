#include "experiment_bench.h"

#include "../lib_SortedTableOnArr/sorted_table_on_arr.h"

#include <vector>

namespace {

using bench::run_int_key_benchmark;
using bench::TableValue;

const std::vector<size_t> kSizes = bench::kBenchmarkSizes;

}  

void bench_sorted_arr(std::vector<bench::RowResult>& rows) {
    run_int_key_benchmark<SortedTableM<std::string, TableValue>>(
        "Vector (sorted)", kSizes, rows,
        "O(n)", "O(log n)", "O(n)");
}
