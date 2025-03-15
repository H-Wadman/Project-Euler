#include <array>
#include <cassert>
#include <iostream>
#include <numeric>
#include <print>
#include <unordered_map>


#include "optdoc.hpp"

#include "doctest/doctest.h"

int gen_triples(const int m, const int n, const int k)
{
    using cint = const int;
    auto a{[](cint m, cint n, cint k) { return k * (m * m - n * n); }};

    auto b{[](cint m, cint n, cint k) { return k * (2 * m * n); }};

    auto c{[](cint m, cint n, cint k) { return k * (m * m + n * n); }};

    return a(m, n, k) + b(m, n, k) + c(m, n, k);
}

inline bool violate_constraints(const int n, const int m)
{
    return std::gcd(m, n) != 1 || (n % 2 == 1 && m % 2 == 1);
}

int solve_problem(const int limit)
{
    using sum   = int;
    using count = int;
    std::unordered_map<sum, count> res{};

    for (int m{2}; m < limit; ++m) {
        //Value of a + b + c if n == 1. If too large we're done
        if (2 * (m * m + m) > limit) { break; }

        for (int n{1}; n < m; ++n) {
            auto pyth_sum{gen_triples(m, n, 1)};
            if (pyth_sum > limit) { break; }
            if (violate_constraints(n, m)) { continue; }

            int k{2};
            while (pyth_sum <= limit) {
                ++res[pyth_sum];
                pyth_sum = gen_triples(m, n, k);

                ++k;
            }
        }
    }

    return std::accumulate(res.begin(), res.end(), int{},
                           [](const int acc, const std::pair<int, int> p) {
                               //assert(acc < 1'000'000'000);
                               return acc + ((p.second == 1) ? 1 : 0);
                           });
}

TEST_SUITE("solution")
{
    TEST_CASE("lower bound") { CHECK(solve_problem(48) == 190); }

    TEST_CASE("accumulate")
    {
        std::unordered_map<int, int> map{};
        map[120] = 3;

        CHECK(std::accumulate(map.begin(), map.end(), int{},
                              [](const int acc, const std::pair<int, int> p) {
                                  return acc + ((p.second == 1) ? p.first : 0);
                              }) == 0);
    }
}

#ifdef DOCTEST_CONFIG_DISABLE

int main()
{
    std::println("{}", solve_problem(1'500'000));

    return 0;
}

#endif
