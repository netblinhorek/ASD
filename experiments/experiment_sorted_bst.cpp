#include "experiment_bench.h"

#include "../lib_TableBSTree/table_bstree.h"

#include <vector>

namespace {

using bench::run_int_key_benchmark;
using bench::TableValue;

const std::vector<size_t> kSizes = { 100, 1000, 10000, 100000 };

}  // namespace

void bench_sorted_bst(std::vector<bench::RowResult>& rows) {
    run_int_key_benchmark<TableBSTree<int, TableValue>>(
        "BST (sorted)", kSizes, rows,
        "O(log n) avg.", "O(log n) avg.", "O(log n) avg.");
}
