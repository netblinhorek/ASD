#include "experiment_bench.h"

#include "../lib_TableTree/table_tree.h"

#include <vector>

namespace {

using bench::run_int_key_benchmark;
using bench::TableValue;

const std::vector<size_t> kSizes = { 100, 1000, 10000, 100000 };

}  // namespace

void bench_unsorted_tree(std::vector<bench::RowResult>& rows) {
    run_int_key_benchmark<TableTree<int, TableValue>>(
        "Tree", kSizes, rows,
        "O(n)", "O(n)", "O(n)");
}
