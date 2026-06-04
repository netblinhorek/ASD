#include "experiment_bench.h"

#include "../lib_TableAVLTree/table_avltree.h"

#include <vector>

namespace {

using bench::run_int_key_benchmark;
using bench::TableValue;

const std::vector<size_t> kSizes = bench::kBenchmarkSizes;

}  

void bench_sorted_avl(std::vector<bench::RowResult>& rows) {
    run_int_key_benchmark<TableAVLTree<std::string, TableValue>>(
        "AVL (sorted)", kSizes, rows,
        "O(log n)", "O(log n)", "O(log n)");
}
