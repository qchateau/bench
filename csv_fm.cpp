#include <cmath>

void exp_fastmath(float const* x, std::size_t size, float* out)
{
    for (auto i = 0ul; i < size; ++i)
        out[i] = std::exp(x[i]);
}

void exp_fastmath(double const* x, std::size_t size, double* out)
{
    for (auto i = 0ul; i < size; ++i)
        out[i] = std::exp(x[i]);
}
