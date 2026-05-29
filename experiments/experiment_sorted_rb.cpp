#include "experiment_bench.h"

#include "../lib_TableRBTree/table_rbtree.h"

#include <vector>

namespace {

using bench::run_int_key_benchmark;
using bench::TableValue;

const std::vector<size_t> kSizes = { 100, 1000, 10000, 100000 };

}  // namespace

void bench_sorted_rb(std::vector<bench::RowResult>& rows) {
    run_int_key_benchmark<TableRBTree<int, TableValue>>(
        "RB-tree (sorted)", kSizes, rows,
        "O(log n)", "O(log n)", "O(log n)");
}
