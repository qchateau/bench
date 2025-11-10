#include "bench.h"

void BM_FM_exp_float(benchmark::State& state)
{
    BM_exp<float>(state, [](auto const& data, auto& output) {
        inner_loop_float(data, output);
    });
}
BENCHMARK(BM_FM_exp_float)->RangeMultiplier(2)->Range(1, 256);

void BM_FM_exp_float_fast(benchmark::State& state)
{
    BM_exp<float>(state, [](auto const& data, auto& output) {
        inner_loop_float_fast(data, output);
    });
}
BENCHMARK(BM_FM_exp_float_fast)->RangeMultiplier(2)->Range(1, 256);

void BM_FM_exp_float_very_fast(benchmark::State& state)
{
    BM_exp<float>(state, [](auto const& data, auto& output) {
        inner_loop_float_very_fast(data, output);
    });
}
BENCHMARK(BM_FM_exp_float_very_fast)->RangeMultiplier(2)->Range(1, 256);

void BM_FM_exp_double(benchmark::State& state)
{
    BM_exp<double>(state, [](auto const& data, auto& output) {
        inner_loop_double(data, output);
    });
}
BENCHMARK(BM_FM_exp_double)->RangeMultiplier(2)->Range(1, 256);

void BM_FM_exp_double_as_float(benchmark::State& state)
{
    BM_exp<double>(state, [](auto const& data, auto& output) {
        inner_loop_double_as_float(data, output);
    });
}
BENCHMARK(BM_FM_exp_double_as_float)->RangeMultiplier(2)->Range(1, 256);

void BM_FM_exp_double_fast(benchmark::State& state)
{
    BM_exp<double>(state, [](auto const& data, auto& output) {
        inner_loop_double_fast(data, output);
    });
}
BENCHMARK(BM_FM_exp_double_fast)->RangeMultiplier(2)->Range(1, 256);

void BM_FM_exp_double_very_fast(benchmark::State& state)
{
    BM_exp<double>(state, [](auto const& data, auto& output) {
        inner_loop_double_very_fast(data, output);
    });
}
BENCHMARK(BM_FM_exp_double_very_fast)->RangeMultiplier(2)->Range(1, 256);
