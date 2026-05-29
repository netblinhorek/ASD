#pragma once

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <exception>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../lib_Polynom/polynom.h"

namespace bench {

using Clock = std::chrono::high_resolution_clock;
using PolyTableKey = int;
using HashTableKey = std::string;
using TableValue = Polynom;

inline double seconds(Clock::time_point start, Clock::time_point end) {
    return std::chrono::duration<double>(end - start).count();
}

inline std::string int_key(size_t i) {
    return "k" + std::to_string(i);
}

struct Timings {
    double insert_sec = 0.0;
    double search_sec = 0.0;
    double erase_sec = 0.0;
};

struct RowResult {
    std::string name;
    size_t size = 0;
    Timings times;
    Timings slowdown;
};

struct BenchmarkDataset {
    std::vector<PolyTableKey> int_keys;
    std::vector<HashTableKey> string_keys;
    std::vector<TableValue> values;
};

inline double slowdown_ratio(double t_n, double t_base) {
    if (t_base <= 0.0) return 0.0;
    return t_n / t_base;
}

inline std::string empirical_complexity(double t100, double t100000) {
    if (t100 <= 0.0 || t100000 <= 0.0) return "n/a";
    const double ratio = t100000 / t100;
    if (ratio < 300.0) return "O(n)";
    if (ratio < 30000.0) return "O(n log n)";
    return "O(n^2) or worse";
}

inline void print_table_header(int table_num, const char* title) {
    std::cout << "\nTable " << table_num << ". " << title << "\n";
    std::cout << std::string(120, '-') << "\n";
    std::cout << std::left
        << std::setw(18) << "Basic DS"
        << std::setw(10) << "Size"
        << std::setw(14) << "Insert, sec."
        << std::setw(18) << "Slowdown insert"
        << std::setw(14) << "Find, sec"
        << std::setw(18) << "Slowdown find"
        << std::setw(14) << "Erase, sec"
        << std::setw(18) << "Slowdown erase"
        << "\n";
    std::cout << std::string(120, '-') << "\n";
}

inline void print_data_row(const RowResult& row) {
    std::cout << std::left << std::fixed << std::setprecision(6)
        << std::setw(18) << row.name
        << std::setw(10) << row.size
        << std::setw(14) << row.times.insert_sec
        << std::setw(18) << row.slowdown.insert_sec
        << std::setw(14) << row.times.search_sec
        << std::setw(18) << row.slowdown.search_sec
        << std::setw(14) << row.times.erase_sec
        << std::setw(18) << row.slowdown.erase_sec
        << "\n";
}

inline void print_complexity_rows(
    const std::string& name,
    const std::string& empirical,
    const std::string& theoretical)
{
    std::cout << std::left
        << std::setw(18) << name
        << std::setw(10) << ""
        << std::setw(14) << empirical
        << std::setw(18) << ""
        << std::setw(14) << theoretical
        << "\n";
}


inline Polynom generate_random_polynom(
    std::mt19937& gen,
    size_t min_terms = 1,
    size_t max_terms = 12,
    int max_degree = 8)
{
    std::uniform_int_distribution<size_t> terms_dist(min_terms, max_terms);
    std::uniform_real_distribution<double> coeff_dist(-50.0, 50.0);
    std::uniform_int_distribution<int> degree_dist(0, max_degree);

    Polynom polynom;
    const size_t num_terms = terms_dist(gen);

    for (size_t i = 0; i < num_terms; ++i) {
        double coeff = coeff_dist(gen);
        if (std::abs(coeff) < 1e-9) {
            coeff = 1.0;
        }
        Monom m(coeff, degree_dist(gen), degree_dist(gen), degree_dist(gen));
        polynom.add_monom(m);
    }
    return polynom;
}

inline BenchmarkDataset make_dataset(size_t n, unsigned seed = 42) {
    std::mt19937 gen(seed + static_cast<unsigned>(n));
    BenchmarkDataset data;
    data.int_keys.resize(n);
    data.string_keys.resize(n);
    data.values.resize(n);

    for (size_t i = 0; i < n; ++i) {
        data.int_keys[i] = static_cast<PolyTableKey>(i);
        data.string_keys[i] = int_key(i);
        data.values[i] = generate_random_polynom(gen);
    }
    return data;
}

inline size_t hash_capacity_for(size_t n) {
    return std::max<size_t>(17, n * 4 + 1);
}

template <class Table>
struct DefaultTableFactory {
    static Table make(size_t) {
        return Table{};
    }
};

template <class Table, class Factory = DefaultTableFactory<Table>>
Timings measure_int_key_table(size_t n, size_t capacity_hint, const BenchmarkDataset& data) {
    Timings result;
    Table table = Factory::make(capacity_hint);

    auto t0 = Clock::now();
    for (size_t i = 0; i < n; ++i) {
        table.insert(data.int_keys[i], data.values[i]);
    }
    auto t1 = Clock::now();
    result.insert_sec = seconds(t0, t1);

    t0 = Clock::now();
    for (size_t i = 0; i < n; ++i) {
        volatile auto& sink = table.found(data.int_keys[i]);
        (void)sink;
    }
    t1 = Clock::now();
    result.search_sec = seconds(t0, t1);

    t0 = Clock::now();
    for (size_t i = 0; i < n; ++i) {
        table.erase(data.int_keys[i]);
    }
    t1 = Clock::now();
    result.erase_sec = seconds(t0, t1);

    return result;
}

template <class Table, class Factory>
Timings measure_string_key_table(size_t n, size_t capacity, const BenchmarkDataset& data) {
    Timings result;
    Table table = Factory::make(capacity);

    auto t0 = Clock::now();
    for (size_t i = 0; i < n; ++i) {
        table.insert(data.string_keys[i], data.values[i]);
    }
    auto t1 = Clock::now();
    result.insert_sec = seconds(t0, t1);

    t0 = Clock::now();
    for (size_t i = 0; i < n; ++i) {
        volatile auto& sink = table.found(data.string_keys[i]);
        (void)sink;
    }
    t1 = Clock::now();
    result.search_sec = seconds(t0, t1);

    t0 = Clock::now();
    for (size_t i = 0; i < n; ++i) {
        table.erase(data.string_keys[i]);
    }
    t1 = Clock::now();
    result.erase_sec = seconds(t0, t1);

    return result;
}

template <class Table, class Factory = DefaultTableFactory<Table>>
void run_int_key_benchmark(
    const std::string& name,
    const std::vector<size_t>& sizes,
    std::vector<RowResult>& out_rows,
    const std::string& theoretical_insert,
    const std::string& theoretical_search,
    const std::string& theoretical_erase)
{
    Timings base{};
    const size_t row_start = out_rows.size();

    for (size_t n : sizes) {
        const BenchmarkDataset data = make_dataset(n);
        const size_t cap = 0;

        Timings times{};
        try {
            times = measure_int_key_table<Table, Factory>(n, cap, data);
        }
        catch (const std::exception& ex) {
            std::cerr << "Benchmark failed [" << name << ", n=" << n << "]: " << ex.what() << '\n';
            throw;
        }

        RowResult row;
        row.name = name;
        row.size = n;
        row.times = times;

        if (n == sizes.front()) {
            base = times;
            row.slowdown = { 1.0, 1.0, 1.0 };
        }
        else {
            row.slowdown.insert_sec = slowdown_ratio(times.insert_sec, base.insert_sec);
            row.slowdown.search_sec = slowdown_ratio(times.search_sec, base.search_sec);
            row.slowdown.erase_sec = slowdown_ratio(times.erase_sec, base.erase_sec);
        }

        out_rows.push_back(row);
        print_data_row(row);
    }

    const auto& t100 = out_rows[row_start];
    const auto& t100k = out_rows.back();

    print_complexity_rows(
        "Fact. complexity (insert)",
        empirical_complexity(t100.times.insert_sec, t100k.times.insert_sec),
        theoretical_insert);
    print_complexity_rows(
        "Fact. complexity (find)",
        empirical_complexity(t100.times.search_sec, t100k.times.search_sec),
        theoretical_search);
    print_complexity_rows(
        "Fact. complexity (erase)",
        empirical_complexity(t100.times.erase_sec, t100k.times.erase_sec),
        theoretical_erase);

    std::cout << std::string(120, '-') << "\n";
}

template <class Table, class Factory>
void run_string_key_hash_benchmark(
    const std::string& name,
    const std::vector<size_t>& sizes,
    std::vector<RowResult>& out_rows,
    const std::string& theoretical_insert,
    const std::string& theoretical_search,
    const std::string& theoretical_erase)
{
    Timings base{};
    const size_t row_start = out_rows.size();

    for (size_t n : sizes) {
        const BenchmarkDataset data = make_dataset(n);
        const size_t cap = hash_capacity_for(n);

        Timings times = measure_string_key_table<Table, Factory>(n, cap, data);

        RowResult row;
        row.name = name;
        row.size = n;
        row.times = times;

        if (n == sizes.front()) {
            base = times;
            row.slowdown = { 1.0, 1.0, 1.0 };
        }
        else {
            row.slowdown.insert_sec = slowdown_ratio(times.insert_sec, base.insert_sec);
            row.slowdown.search_sec = slowdown_ratio(times.search_sec, base.search_sec);
            row.slowdown.erase_sec = slowdown_ratio(times.erase_sec, base.erase_sec);
        }

        out_rows.push_back(row);
        print_data_row(row);
    }

    const auto& t100 = out_rows[row_start];
    const auto& t100k = out_rows.back();

    print_complexity_rows(
        "Fact. complexity (insert)",
        empirical_complexity(t100.times.insert_sec, t100k.times.insert_sec),
        theoretical_insert);
    print_complexity_rows(
        "Fact. complexity (find)",
        empirical_complexity(t100.times.search_sec, t100k.times.search_sec),
        theoretical_search);
    print_complexity_rows(
        "Fact. complexity (erase)",
        empirical_complexity(t100.times.erase_sec, t100k.times.erase_sec),
        theoretical_erase);

    std::cout << std::string(120, '-') << "\n";
}

}  // namespace bench
