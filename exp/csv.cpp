#include "exp.h"

#include <iomanip>
#include <iostream>
#include <vector>

constexpr double min = -50;
constexpr double max = 50;
constexpr double step = 0.001;
constexpr auto max_precision{std::numeric_limits<double>::digits10 + 1};

void exp_fastmath(float const* x, std::size_t size, float* out);
void exp_fastmath(double const* x, std::size_t size, double* out);

template <typename T>
T exp_fastmath(T x)
{
    std::vector<T> data(1024);
    std::vector<T> output(1024);
    for (int i = 0; i < data.size(); ++i) {
        data[i] = i;
    }
    data[42] = x;
    exp_fastmath(data.data(), data.size(), output.data());
    return output[42];
    ;
}

int main()
{
    std::cout << "x,exp_float,exp_double,exp_fast_float,exp_very_fast_float,";
    std::cout << "exp_float_fast_math,exp_double_fast_math\n";
    for (double x = min; x < max; x += step) {
        float fx = x;
        std::cout << std::setprecision(max_precision) << x;
        std::cout << ',' << std::exp(fx);
        std::cout << ',' << std::exp(x);
        std::cout << ',' << fast_exp(fx);
        std::cout << ',' << very_fast_exp(fx);
        std::cout << ',' << exp_fastmath(fx);
        std::cout << ',' << exp_fastmath(x);
        std::cout << '\n';
    }
    std::cout << std::flush;
    return 0;
}
