#include "experiment_bench.h"

#include "../lib_TableRBTree/table_rbtree.h"

#include <vector>

namespace {

using bench::run_int_key_benchmark;
using bench::TableValue;

const std::vector<size_t> kSizes = bench::kBenchmarkSizes;

}  

void bench_sorted_rb(std::vector<bench::RowResult>& rows) {
    run_int_key_benchmark<TableRBTree<std::string, TableValue>>(
        "RB-tree (sorted)", kSizes, rows,
        "O(log n)", "O(log n)", "O(log n)");
}
