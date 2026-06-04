#include "experiment_bench.h"

#include "../lib_TableBSTree/table_bstree.h"

#include <vector>

namespace {

using bench::FillOrder;
using bench::run_int_key_benchmark;
using bench::TableValue;

const std::vector<size_t> kSizes = bench::kBenchmarkSizes;

}  

void bench_sorted_bst(std::vector<bench::RowResult>& rows) {
    run_int_key_benchmark<TableBSTree<std::string, TableValue>>(
        "BST (sorted)", kSizes, rows,
        "O(log n) avg.", "O(log n) avg.", "O(log n) avg.",
        FillOrder::AsGenerated);
}
