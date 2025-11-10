#include "bench.h"

void BM_exp_float_libmvec(benchmark::State& state)
{
    BM_exp<float>(state, [](auto const& data, auto& output) {
        inner_loop_float(data, output);
    });
}
BENCHMARK(BM_exp_float_libmvec)->RangeMultiplier(2)->Range(1, 256);

void BM_exp_double_libmvec(benchmark::State& state)
{
    BM_exp<double>(state, [](auto const& data, auto& output) {
        inner_loop_double(data, output);
    });
}
BENCHMARK(BM_exp_double_libmvec)->RangeMultiplier(2)->Range(1, 256);

void BM_exp_double_as_float_libmvec(benchmark::State& state)
{
    BM_exp<double>(state, [](auto const& data, auto& output) {
        inner_loop_double_as_float(data, output);
    });
}
BENCHMARK(BM_exp_double_as_float_libmvec)->RangeMultiplier(2)->Range(1, 256);
