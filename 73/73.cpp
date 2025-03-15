#include <cassert>
#include <iostream>
#include <numeric>
#include <print>
#include <ratio>

// lower and upper should always have a numerator of 1
using lower = std::ratio<1, 3>;
using upper = std::ratio<1, 2>;

int start_n(int d)
{
    if (std::gcd(d, lower::den) != 1) {}
    const int n{d / static_cast<int>(lower::den) +
                ((std::gcd(d, lower::den) == 1) ? 1 : 0)};
    return (d % 2 == 0 && n % 2 == 0) ? n + 1 : n;
}

void test_start_n()
{
    assert(start_n(8) == 3);
    assert(start_n(5) == 2);
    assert(start_n(7) == 3);

    std::cout << "start_n test finished\n" << std::flush;
}

inline int stop(int d) { return (d % 2 == 0) ? d / 2 : 1 + d / 2; }

int count_range(const int denom_lim)
{
    int count{0};

    for (int d{4}; d <= denom_lim; ++d) {
        int incr{(d % 2 == 0) ? 2 : 1};
        for (int n{start_n(d)}; n < stop(d); n += incr) {
            if (std::gcd(n, d) != 1) { continue; }
            else {
                ++count;
            }
        }
    }

    return count;
}

int main()
{
    test_start_n();

    std::println("{}", count_range(12'000));


    return 0;
}
