#include <utility>
#include <iostream>
#include <cmath>
#include <numeric>
#include "boost/multiprecision/cpp_int.hpp"
#include <array>

using int256_t = boost::multiprecision::int256_t;

consteval int pow2(int n)
{
    return static_cast<int>(pow(2, n));
}

consteval std::array<int, 8> powersOfTwo(int n)
{
    std::array<int, 8> res;
    for (int i {0}; i < n; ++i)
    {
        res[0] = pow2(i);
    }

    return res;
}

/* int256_t gcd(int256_t u, int256_t v)
{
    if (u == 0) return v;
    if (v == 0) return u;


    int shift {std::countr_zero(u | v)};
    
    u >>= std::countr_zero(u);
    v >>= std::countr_zero(v);

    while (true)
    {
        if (u > v) std::swap(u, v);
        v -= u;

        if (v == 0)
        {
            return u << shift;
        }

        v >>= std::countr_zero(v);
    }

} */

std::pair<int256_t, int256_t> nextStep(std::pair<int256_t, int256_t> p, int n)
{
    std::pair<int256_t, int256_t> res {std::make_pair(p.second, n * p.second + p.first)};
/*     int256_t common {gcd(res.first, res.second)};
    if (common != 1)
    {
        res.first /= common;
        res.second /= common;
    } */

    return res;
}

inline int eDigit(int k)
{
    if (k % 3 == 1)
    {
        return (k / 3 + 1) * 2;
    }
    else return 1;
}

template <typename T, typename U>
std::ostream& operator<<(std::ostream& out, std::pair<T, U> p)
{
    out << '<' << p.first << ", " << p.second << '>';
    return out;
}

int main()
{
    using namespace boost::multiprecision;
    constexpr int start {100};
    static_assert(start > 0);
    std::pair<int256_t, int256_t> e {1, eDigit(start - 2)};
    std::cout << e << '\n';

    for(int i {start - 3}; i >= 0; --i)
    {
        e = nextStep(e, eDigit(i));
    }
    e.first += 2 * e.second;
    std::cout << cpp_rational{e.first, e.second} << '\n';

    return 0;
}