#pragma once

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <exception>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

#include "../lib_Polynom/polynom.h"

namespace bench {

    using Clock = std::chrono::high_resolution_clock;
    using HashTableKey = std::string;
    using TableValue = Polynom;

    inline const std::vector<size_t> kBenchmarkSizes = { 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    inline constexpr size_t kMaxBenchmarkSize = 105000;
    inline constexpr unsigned kBenchmarkSeed = 42;
    inline constexpr double kMaxCollisionRate = 0.10;

    inline constexpr size_t kRandomOperationCount = 10;
    inline constexpr size_t kRandomTrialCount = 10;

    inline size_t benchmark_trial_count(size_t) {
        return kRandomTrialCount;
    }

    inline void log_benchmark_progress(
        const std::string& name,
        size_t n,
        size_t trial_count)
    {
        std::cerr << "  [" << name << "] n=" << n << ", trials=" << trial_count << "...\n"
            << std::flush;
    }

    inline double seconds(Clock::time_point start, Clock::time_point end) {
        return std::chrono::duration<double>(end - start).count();
    }

    inline size_t hash_string(const std::string& key, size_t capacity) {
        if (capacity == 0) {
            return 0;
        }
        size_t hash = 0;
        for (unsigned char c : key) {
            hash = (hash * 31 + c) % capacity;
        }
        return hash;
    }

    inline double collision_rate(const std::vector<HashTableKey>& keys, size_t capacity) {
        if (keys.empty() || capacity == 0) {
            return 0.0;
        }
        std::vector<size_t> bucket_count(capacity, 0);
        size_t colliding_keys = 0;
        for (const auto& key : keys) {
            const size_t bucket = hash_string(key, capacity);
            if (bucket_count[bucket] > 0) {
                ++colliding_keys;
            }
            ++bucket_count[bucket];
        }
        return static_cast<double>(colliding_keys) / static_cast<double>(keys.size());
    }

    inline size_t hash_capacity_chain(size_t n) {
        return std::max<size_t>(17, n * 9 / 2 + 1);
    }

    inline size_t hash_capacity_open(size_t n) {
        return std::max<size_t>(17, n * 8 + 1);
    }

    inline char random_key_char(std::mt19937& rng) {
        static constexpr char kPool[] =
            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        std::uniform_int_distribution<size_t> dist(0, sizeof(kPool) - 2);
        return kPool[dist(rng)];
    }

    inline constexpr size_t kMinKeyLength = 3;
    inline constexpr size_t kMaxKeyLength = 40;

    inline std::string make_random_key(std::mt19937& rng) {
        std::uniform_int_distribution<size_t> len_dist(kMinKeyLength, kMaxKeyLength);
        const size_t len = len_dist(rng);
        std::string key;
        key.reserve(len);
        for (size_t i = 0; i < len; ++i) {
            key.push_back(random_key_char(rng));
        }
        return key;
    }

    inline void generate_unique_string_keys(
        std::vector<HashTableKey>& keys,
        size_t count,
        std::mt19937& rng)
    {
        keys.clear();
        keys.reserve(count);
        std::unordered_set<std::string> used;
        used.reserve(count * 2);

        while (keys.size() < count) {
            std::string key = make_random_key(rng);
            if (used.insert(key).second) {
                keys.push_back(std::move(key));
            }
        }
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

    struct RandomOpTrialTimings {
        double fill_sec = 0.0;
        double insert_ops_sec_sum = 0.0;
        double find_ops_sec_sum = 0.0;
        double erase_ops_sec_sum = 0.0;
        size_t insert_ops_count = 0;
        size_t find_ops_count = 0;
        size_t erase_ops_count = 0;
    };

    struct RandomOpRowResult {
        std::string name;
        size_t size = 0;
        size_t trial_count = kRandomTrialCount;
        size_t fill_key_count = 0;
        double initial_fill_sec = 0.0;
        double fill_sec_avg = 0.0;
        double experiment_sec_avg = 0.0;
        double avg_op_sec_mean = 0.0;
        std::array<RandomOpTrialTimings, kRandomTrialCount> trials{};
    };

    struct BenchmarkDataset {
        std::vector<HashTableKey> string_keys;
        std::vector<TableValue> values;
    };

    enum class FillOrder {
        AsGenerated,
        SortedByKey,
    };

    template <class Table, class Factory>
    class TableBenchSession {
    public:
        Table table;
        size_t loaded_through = 0;
        std::vector<size_t> active;
        size_t next_key_index = 0;

        explicit TableBenchSession(size_t capacity_hint = 0)
            : table(Factory::make(capacity_hint)) {
        }

        double grow_to(size_t n, const BenchmarkDataset& master, FillOrder order) {
            if (n <= loaded_through) {
                return 0.0;
            }

            const size_t begin = loaded_through;
            std::vector<size_t> indices;
            indices.reserve(n - begin);
            for (size_t i = begin; i < n; ++i) {
                indices.push_back(i);
            }
            if (order == FillOrder::SortedByKey) {
                std::sort(indices.begin(), indices.end(), [&](size_t a, size_t b) {
                    return master.string_keys[a] < master.string_keys[b];
                    });
            }

            size_t report_step = 0;
            if (n >= 10000) {
                report_step = 10000;
            }

            auto t0 = Clock::now();
            size_t inserted = 0;
            for (size_t idx : indices) {
                try {
                    table.insert(master.string_keys[idx], master.values[idx]);
                    active.push_back(idx);
                }
                catch (const std::logic_error&) {
                }
                ++inserted;
                if (report_step > 0 && inserted % report_step == 0) {
                    std::cerr << "    fill progress: " << (begin + inserted) << " / " << n << "\n"
                        << std::flush;
                }
            }
            auto t1 = Clock::now();

            loaded_through = n;
            next_key_index = std::max(next_key_index, n);

            if (begin == 0) {
                active.clear();
                active.reserve(n);
                for (size_t i = 0; i < n; ++i) {
                    active.push_back(i);
                }
            }
            return seconds(t0, t1);
        }
    };

    inline double slowdown_ratio(double t_n, double t_base) {
        if (t_base <= 0.0) {
            return 0.0;
        }
        return t_n / t_base;
    }
    inline std::string empirical_complexity(double t100, double t100000) {
        if (t100 <= 0.0 || t100000 <= 0.0) {
            return "n/a";
        }
        const double ratio = t100000 / t100;

        // Для O(1) или O(log n) время растет крайне слабо, отношение будет в пределах единиц
        if (ratio < 10.0) {
            return "O(1) / O(log n)";
        }
        // Для O(n) при увеличении объема в 1000 раз отношение должно быть около 1000 (с запасом)
        if (ratio < 3000.0) {
            return "O(n)";
        }
        // Если время выросло драматически сильнее, то это квадратичная зависимость
        return "O(n^2) or worse";
    }

    inline Timings timings_from_random_ops(const RandomOpRowResult& row, size_t /*n*/) {
        Timings times;

        double insert_rand_sum = 0.0;
        double find_sum = 0.0;
        double erase_sum = 0.0;
        size_t insert_rand_count = 0;
        size_t find_count = 0;
        size_t erase_count = 0;

        size_t trials = kRandomTrialCount;
        if (row.trial_count > 0) {
            trials = row.trial_count;
        }

        for (size_t i = 0; i < trials; ++i) {
            const RandomOpTrialTimings& trial = row.trials[i];
            insert_rand_sum += trial.insert_ops_sec_sum;
            find_sum += trial.find_ops_sec_sum;
            erase_sum += trial.erase_ops_sec_sum;
            insert_rand_count += trial.insert_ops_count;
            find_count += trial.find_ops_count;
            erase_count += trial.erase_ops_count;
        }

        if (insert_rand_count > 0) {
            times.insert_sec = insert_rand_sum / static_cast<double>(insert_rand_count);
        }
        else {
            times.insert_sec = 0.0;
        }

        if (find_count > 0) {
            times.search_sec = find_sum / static_cast<double>(find_count);
        }
        else {
            times.search_sec = 0.0;
        }

        if (erase_count > 0) {
            times.erase_sec = erase_sum / static_cast<double>(erase_count);
        }
        else {
            times.erase_sec = 0.0;
        }

        return times;
    }

    inline void print_table_header(int table_num, const char* title) {
        std::cout << "\nTable " << table_num << ". " << title << "\n";
        std::cout << "(10 trials per size; one table per structure, grows by size; "
            << "fill only new keys; 10 random ops per trial on the same table; "
            << "slowdown = ratio to previous size)\n";
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
        std::cout << std::string(120, '-') << "\n" << std::flush;
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
            << "\n"
            << std::flush;
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

    inline void print_random_ops_table_header(int table_num, const char* title) {
        std::cout << "\nTable " << table_num << ". " << title << "\n";
        std::cout << "(one table per size: fill n once; each trial: 10 random ops on the same table; "
            << "avg op = experiment_time/10; table shows means over trials)\n";
        std::cout << std::string(120, '-') << "\n";
        std::cout << std::left
            << std::setw(18) << "Basic DS"
            << std::setw(10) << "Size"
            << std::setw(16) << "Fill avg, sec."
            << std::setw(18) << "Exp avg, sec."
            << std::setw(18) << "Avg op mean, sec."
            << "\n";
        std::cout << std::string(120, '-') << "\n";
    }

    inline void print_random_ops_row(const RandomOpRowResult& row) {
        std::cout << std::left << std::fixed << std::setprecision(6)
            << std::setw(18) << row.name
            << std::setw(10) << row.size
            << std::setw(16) << row.fill_sec_avg
            << std::setw(18) << row.experiment_sec_avg
            << std::setw(18) << row.avg_op_sec_mean
            << "\n";

        std::cout << std::left << std::setw(18) << ""
            << std::setw(10) << ""
            << "  trials (exp, sec):";
        size_t trials = kRandomTrialCount;
        if (row.trial_count > 0) {
            trials = row.trial_count;
        }
        for (size_t i = 0; i < trials; ++i) {
            const RandomOpTrialTimings& trial = row.trials[i];
            const double experiment = trial.insert_ops_sec_sum
                + trial.find_ops_sec_sum + trial.erase_ops_sec_sum;
            std::cout << ' ' << experiment;
        }
        std::cout << "\n";

        std::cout << std::left << std::setw(18) << ""
            << std::setw(10) << ""
            << "  trials (avg op):";
        for (size_t i = 0; i < trials; ++i) {
            const RandomOpTrialTimings& trial = row.trials[i];
            const double experiment = trial.insert_ops_sec_sum
                + trial.find_ops_sec_sum + trial.erase_ops_sec_sum;
            std::cout << ' ' << (experiment / static_cast<double>(kRandomOperationCount));
        }
        std::cout << "\n";
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

    inline BenchmarkDataset make_master_dataset(
        size_t max_n = kMaxBenchmarkSize,
        unsigned seed = kBenchmarkSeed)
    {
        BenchmarkDataset data;
        data.string_keys.reserve(max_n);
        data.values.reserve(max_n);

        const size_t chain_cap = hash_capacity_chain(max_n);
        double chain_rate = 0.0;
        unsigned key_seed = seed;

        std::cerr << "Generating benchmark dataset (" << max_n << " keys)...\n" << std::flush;

        for (int attempt = 0; attempt < 64; ++attempt) {
            std::mt19937 key_gen(key_seed + static_cast<unsigned>(attempt));
            generate_unique_string_keys(data.string_keys, max_n, key_gen);
            chain_rate = collision_rate(data.string_keys, chain_cap);
            if (chain_rate >= kMaxCollisionRate) {
                break;
            }
        }

        if (chain_rate < kMaxCollisionRate) {
            std::cerr << "Warning: collision rate below 10% at chain capacity ("
                << chain_cap << "): " << (chain_rate * 100.0) << "%\n";
        }

        std::mt19937 value_gen(seed);
        for (size_t i = 0; i < max_n; ++i) {
            data.values.push_back(generate_random_polynom(value_gen));
            if ((i + 1) % 20000 == 0) {
                std::cerr << "  " << (i + 1) << " polynoms generated\n" << std::flush;
            }
        }

        size_t min_key_len = data.string_keys.front().size();
        size_t max_key_len = min_key_len;
        for (const auto& key : data.string_keys) {
            min_key_len = std::min(min_key_len, key.size());
            max_key_len = std::max(max_key_len, key.size());
        }

        std::cerr << "Benchmark dataset ready. Hash collisions at chain capacity ("
            << chain_cap << "): " << std::fixed << std::setprecision(3)
            << (chain_rate * 100.0) << "%"
            << " (key lengths: " << min_key_len << "-" << max_key_len << " chars)\n";

        if (chain_rate > kMaxCollisionRate + 0.05) {
            std::cerr << "Warning: collision rate well above 10% at chain capacity.\n";
        }

        return data;
    }

    inline const BenchmarkDataset& master_dataset() {
        static const BenchmarkDataset dataset = make_master_dataset();
        return dataset;
    }

    inline BenchmarkDataset dataset_prefix(size_t n) {
        const BenchmarkDataset& master = master_dataset();
        if (n > master.string_keys.size()) {
            throw std::out_of_range("Benchmark size exceeds master dataset");
        }

        BenchmarkDataset data;
        data.string_keys.assign(master.string_keys.begin(), master.string_keys.begin() + static_cast<std::ptrdiff_t>(n));
        data.values.assign(master.values.begin(), master.values.begin() + static_cast<std::ptrdiff_t>(n));
        return data;
    }

    inline BenchmarkDataset make_dataset(size_t n, unsigned /*seed*/ = kBenchmarkSeed) {
        return dataset_prefix(n);
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

    template <class Table>
    RandomOpTrialTimings run_random_ops_on_table(
        Table& table,
        std::vector<size_t>& active,
        size_t& next_key_index,
        const BenchmarkDataset& data,
        std::mt19937& rng)
    {
        RandomOpTrialTimings trial;
        std::uniform_int_distribution<int> op_dist(0, 2);

        for (size_t op_num = 0; op_num < kRandomOperationCount; ++op_num) {
            bool done = false;
            for (int attempt = 0; attempt < 16 && !done; ++attempt) {
                const int op = op_dist(rng);
                try {
                    if (op == 0) { // Insert
                        if (next_key_index >= data.string_keys.size()) {
                            continue;
                        }
                        const size_t key_index = next_key_index++;
                        auto t0 = Clock::now();
                        table.insert(data.string_keys[key_index], data.values[key_index]);
                        auto t1 = Clock::now();
                        trial.insert_ops_sec_sum += seconds(t0, t1);
                        ++trial.insert_ops_count;
                        active.push_back(key_index);
                        done = true;
                    }
                    else if (op == 1) { // Find
                        if (active.empty()) {
                            continue;
                        }
                        std::uniform_int_distribution<size_t> index_dist(0, active.size() - 1);
                        const size_t pos = index_dist(rng);
                        const size_t key_index = active[pos];
                        if (key_index >= data.string_keys.size()) {
                            continue;
                        }
                        auto t0 = Clock::now();
                        volatile auto& sink = table.found(data.string_keys[key_index]);
                        (void)sink;
                        auto t1 = Clock::now();
                        trial.find_ops_sec_sum += seconds(t0, t1);
                        ++trial.find_ops_count;
                        done = true;
                    }
                    else { // Erase
                        if (active.empty()) {
                            continue;
                        }
                        std::uniform_int_distribution<size_t> index_dist(0, active.size() - 1);
                        const size_t pos = index_dist(rng);
                        const size_t key_index = active[pos];
                        if (key_index >= data.string_keys.size()) {
                            continue;
                        }
                        auto t0 = Clock::now();
                        table.erase(data.string_keys[key_index]);
                        auto t1 = Clock::now();
                        trial.erase_ops_sec_sum += seconds(t0, t1);
                        ++trial.erase_ops_count;
                        active[pos] = active.back();
                        active.pop_back();
                        done = true;
                    }
                }
                catch (const std::exception&) {
                    continue;
                }
            }
            if (!done) {
                throw std::runtime_error("Failed to execute random operation on table");
            }
        }
        return trial;
    }

    template <class Table, class Factory = DefaultTableFactory<Table>>
    RandomOpRowResult measure_with_table_session(
        TableBenchSession<Table, Factory>& session,
        size_t n,
        const BenchmarkDataset& master,
        size_t trial_count,
        FillOrder fill_order)
    {
        RandomOpRowResult result;
        result.size = n;
        result.trial_count = trial_count;

        size_t fill_key_count = 0;
        if (n > session.loaded_through) {
            fill_key_count = n - session.loaded_through;
        }
        result.fill_key_count = fill_key_count;

        std::cerr << "    fill keys " << session.loaded_through << " -> " << n
            << " (" << result.fill_key_count << " inserts)...\n"
            << std::flush;
        result.initial_fill_sec = session.grow_to(n, master, fill_order);
        result.fill_sec_avg = result.initial_fill_sec;

        for (size_t trial_idx = 0; trial_idx < trial_count; ++trial_idx) {
            std::cerr << "    trial " << (trial_idx + 1) << " / " << trial_count << "\n" << std::flush;
            std::mt19937 rng(static_cast<unsigned>(kBenchmarkSeed + 17 + n + trial_idx * 131));
            result.trials[trial_idx] = run_random_ops_on_table(
                session.table,
                session.active,
                session.next_key_index,
                master,
                rng);
        }

        double experiment_sum = 0.0;
        for (size_t trial_idx = 0; trial_idx < trial_count; ++trial_idx) {
            const RandomOpTrialTimings& trial = result.trials[trial_idx];
            experiment_sum += trial.insert_ops_sec_sum + trial.find_ops_sec_sum + trial.erase_ops_sec_sum;
        }
        result.experiment_sec_avg = experiment_sum / static_cast<double>(trial_count);
        result.avg_op_sec_mean = result.experiment_sec_avg / static_cast<double>(kRandomOperationCount);
        return result;
    }

    template <class Table, class Factory = DefaultTableFactory<Table>>
    void run_int_key_random_ops_benchmark(
        const std::string& name,
        const std::vector<size_t>& sizes,
        size_t capacity_hint = 0,
        FillOrder fill_order = FillOrder::SortedByKey)
    {
        TableBenchSession<Table, Factory> session(capacity_hint);
        const BenchmarkDataset& master = master_dataset();

        for (size_t n : sizes) {
            RandomOpRowResult row = measure_with_table_session<Table, Factory>(
                session, n, master, kRandomTrialCount, fill_order);
            row.name = name;
            row.size = n;
            print_random_ops_row(row);
        }

        std::cout << std::string(100, '-') << "\n" << std::flush;
    }

    template <class Table, class Factory = DefaultTableFactory<Table>>
    void run_int_key_benchmark(
        const std::string& name,
        const std::vector<size_t>& sizes,
        std::vector<RowResult>& out_rows,
        const std::string& theoretical_insert,
        const std::string& theoretical_search,
        const std::string& theoretical_erase,
        FillOrder fill_order = FillOrder::SortedByKey,
        size_t(*trials_for_size)(size_t) = benchmark_trial_count)
    {
        Timings prev_times{};
        const size_t row_start = out_rows.size();
        TableBenchSession<Table, Factory> session;
        const BenchmarkDataset& master = master_dataset();

        for (size_t n : sizes) {
            const size_t trial_count = trials_for_size(n);
            log_benchmark_progress(name, n, trial_count);

            Timings times{};
            try {
                const RandomOpRowResult random_result = measure_with_table_session<Table, Factory>(
                    session, n, master, trial_count, fill_order);
                times = timings_from_random_ops(random_result, n);
            }
            catch (const std::exception& ex) {
                std::cerr << "Benchmark failed [" << name << ", n=" << n << "]: " << ex.what() << '\n';
                throw;
            }

            RowResult row;
            row.name = name;
            row.size = n;
            row.times = times;

            if (out_rows.size() == row_start) {
                row.slowdown = { 1.0, 1.0, 1.0 };
            }
            else {
                row.slowdown.insert_sec = slowdown_ratio(times.insert_sec, prev_times.insert_sec);
                row.slowdown.search_sec = slowdown_ratio(times.search_sec, prev_times.search_sec);
                row.slowdown.erase_sec = slowdown_ratio(times.erase_sec, prev_times.erase_sec);
            }
            prev_times = times;

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

        std::cout << std::string(120, '-') << "\n" << std::flush;
    }

    template <class Table, class Factory>
    void run_string_key_hash_benchmark(
        const std::string& name,
        const std::vector<size_t>& sizes,
        std::vector<RowResult>& out_rows,
        const std::string& theoretical_insert,
        const std::string& theoretical_search,
        const std::string& theoretical_erase,
        size_t(*capacity_for)(size_t))
    {
        Timings prev_times{};
        const size_t row_start = out_rows.size();
        const size_t max_cap = capacity_for(kMaxBenchmarkSize + kRandomTrialCount * kRandomOperationCount);
        TableBenchSession<Table, Factory> session(max_cap);
        const BenchmarkDataset& master = master_dataset();

        for (size_t n : sizes) {
            const size_t trial_count = benchmark_trial_count(n);
            log_benchmark_progress(name, n, trial_count);

            const RandomOpRowResult random_result = measure_with_table_session<Table, Factory>(
                session, n, master, trial_count, FillOrder::AsGenerated);
            const Timings times = timings_from_random_ops(random_result, n);

            RowResult row;
            row.name = name;
            row.size = n;
            row.times = times;

            if (out_rows.size() == row_start) {
                row.slowdown = { 1.0, 1.0, 1.0 };
            }
            else {
                row.slowdown.insert_sec = slowdown_ratio(times.insert_sec, prev_times.insert_sec);
                row.slowdown.search_sec = slowdown_ratio(times.search_sec, prev_times.search_sec);
                row.slowdown.erase_sec = slowdown_ratio(times.erase_sec, prev_times.erase_sec);
            }
            prev_times = times;

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

        std::cout << std::string(120, '-') << "\n" << std::flush;
    }

}  