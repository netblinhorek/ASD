#include "experiment_bench.h"

#include <vector>

void bench_sorted_arr(std::vector<bench::RowResult>& rows);
void bench_sorted_bst(std::vector<bench::RowResult>& rows);
void bench_sorted_avl(std::vector<bench::RowResult>& rows);
void bench_sorted_rb(std::vector<bench::RowResult>& rows);

void run_sorted_experiments() {
    bench::print_table_header(
        2,
        "Efficiency comparison of data storage as a sorted table");

    std::vector<bench::RowResult> rows;
    bench_sorted_arr(rows);
    bench_sorted_bst(rows);
    bench_sorted_avl(rows);
    bench_sorted_rb(rows);
}
