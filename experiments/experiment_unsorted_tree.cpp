#include "experiment_bench.h"

#include "../lib_TableTree/table_tree.h"

#include <vector>

namespace {

    using bench::FillOrder;
    using bench::run_int_key_benchmark;
    using bench::TableValue;

    const std::vector<size_t> kSizes = bench::kBenchmarkSizes;

}  

void bench_unsorted_tree(std::vector<bench::RowResult>& rows) {
    run_int_key_benchmark<TableTree<std::string, TableValue>>(
        "Tree", kSizes, rows,
        "O(n)", "O(n)", "O(n)",
        FillOrder::AsGenerated);
}