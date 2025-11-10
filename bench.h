#pragma once

#include <random>
#include <benchmark/benchmark.h>

#include "exp.h"

constexpr auto seed = 42;

template <std::floating_point T>
std::vector<T> make_data(std::size_t size, double min = -50, double max = 50)
{
    std::default_random_engine eng{seed};
    std::uniform_real_distribution<double> dis(min, max);
    std::vector<T> data(size);
    for (auto& x : data)
        x = dis(eng);
    return data;
}

void inner_loop(auto const& data, auto& output, auto exp)
{
    for (auto i = 0ul; i < data.size(); ++i) {
        output[i] = exp(data[i]);
    }
    benchmark::DoNotOptimize(output);
}

template <typename T>
void BM_exp(benchmark::State& state, auto inner_loop)
{
    auto width = state.range(0);
    auto data = make_data<T>(width);
    auto output = data;
    for (auto _ : state) {
        inner_loop(data, output);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}

extern "C" {

[[gnu::noinline]] inline void inner_loop_float(
    std::vector<float> const& data,
    std::vector<float>& output)
{
    inner_loop(data, output, [](auto x) { return std::exp(x); });
}

[[gnu::noinline]] inline void inner_loop_float_fast(
    std::vector<float> const& data,
    std::vector<float>& output)
{
    inner_loop(data, output, [](auto x) { return fast_exp(x); });
}

[[gnu::noinline]] inline void inner_loop_float_very_fast(
    std::vector<float> const& data,
    std::vector<float>& output)
{
    inner_loop(data, output, [](auto x) { return very_fast_exp(x); });
}

[[gnu::noinline]] inline void inner_loop_double(
    std::vector<double> const& data,
    std::vector<double>& output)
{
    inner_loop(data, output, [](auto x) { return std::exp(x); });
}

[[gnu::noinline]] inline void inner_loop_double_as_float(
    std::vector<double> const& data,
    std::vector<double>& output)
{
    inner_loop(data, output, [](auto x) {
        return std::exp(static_cast<float>(x));
    });
}

[[gnu::noinline]] inline void inner_loop_double_fast(
    std::vector<double> const& data,
    std::vector<double>& output)
{
    inner_loop(data, output, [](auto x) { return fast_exp(x); });
}

[[gnu::noinline]] inline void inner_loop_double_very_fast(
    std::vector<double> const& data,
    std::vector<double>& output)
{
    inner_loop(data, output, [](auto x) { return very_fast_exp(x); });
}
}
