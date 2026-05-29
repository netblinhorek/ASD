#include "experiment_bench.h"

#include "../lib_SortedTableOnArr/sorted_table_on_arr.h"

#include <vector>

namespace {

using bench::run_int_key_benchmark;
using bench::TableValue;

const std::vector<size_t> kSizes = { 100, 1000, 10000, 100000 };

}  // namespace

void bench_sorted_arr(std::vector<bench::RowResult>& rows) {
    run_int_key_benchmark<SortedTableM<int, TableValue>>(
        "Vector (sorted)", kSizes, rows,
        "O(n)", "O(log n)", "O(n)");
}
