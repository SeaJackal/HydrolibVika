#include <benchmark/benchmark.h>

#include <algorithm>
#include <cstddef>
#include <random>
#include <vector>

#include "hydrolib_fixed_point.hpp"

namespace
{
using Fixed = hydrolib::math::FixedPoint<16>;

template <typename T>
void BM_MultiplyAdd(benchmark::State &state)
{
    std::mt19937 generator(42);
    std::uniform_real_distribution<double> distribution(-100.0, 100.0);
    std::vector<T> values(static_cast<std::size_t>((state.range(0) / 6) * 6));
    std::generate(values.begin(), values.end(),
                  [&]() { return T(distribution(generator)); });

    std::size_t index = 0;

    for (auto _ : state)
    {
        auto result = values[index] * values[index + 1] +
                      values[index + 2] * values[index + 3] +
                      values[index + 4] * values[index + 5];
        benchmark::DoNotOptimize(result);

        index += 6;
        if (index + 6 > values.size())
        {
            index = 0;
        }
    }
}

void BM_Dot(benchmark::State &state)
{
    std::mt19937 generator(42);
    std::uniform_real_distribution<double> distribution(-100.0, 100.0);
    std::vector<Fixed> values(
        static_cast<std::size_t>((state.range(0) / 6) * 6));
    std::ranges::generate(values,
                          [&]() { return Fixed(distribution(generator)); });

    std::size_t index = 0;

    for (auto _ : state)
    {
        auto result = Fixed::Dot(
            std::tuple{values[index], values[index + 2], values[index + 4]},
            std::tuple{values[index + 1], values[index + 3],
                       values[index + 5]});
        benchmark::DoNotOptimize(result);

        index += 6;
        if (index + 6 > values.size())
        {
            index = 0;
        }
    }
}

BENCHMARK_TEMPLATE(BM_MultiplyAdd, double)
    ->Arg(1000)
    ->Arg(100000)
    ->Arg(10000000)
    ->ArgName("size");

BENCHMARK_TEMPLATE(BM_MultiplyAdd, float)
    ->Arg(1000)
    ->Arg(100000)
    ->Arg(10000000)
    ->ArgName("size");

BENCHMARK_TEMPLATE(BM_MultiplyAdd, Fixed)
    ->Arg(1000)
    ->Arg(100000)
    ->Arg(10000000)
    ->ArgName("size");

BENCHMARK(BM_Dot)->Arg(1000)->Arg(100000)->Arg(10000000)->ArgName("size");
} // namespace

BENCHMARK_MAIN();
