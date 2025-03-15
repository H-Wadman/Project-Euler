#include <iostream>
#include <vector>
#include "boost/multiprecision/cpp_int.hpp"
#include <cmath>

using int256_t = boost::multiprecision::checked_int256_t;

std::vector<int> canonicalForm(unsigned int s)
{
    std::vector<int> res {};
    int m {0};
    int d {1};
    int a {static_cast<int>(sqrt(s))};
    int a_0 {a};

    do
    {
        res.push_back(a);

        m = d * a - m;
        d = (s - m * m) / d;
        a = (a_0 + m) / d;
    } while (a != 2 * a_0);
    res.push_back(a);

    return res;
}

boost::multiprecision::cpp_rational sqrtExpansion(std::vector<int> canon, int precision)
{
    using namespace boost::multiprecision;
    if (canon.size() == 0) throw std::invalid_argument("bruh");
    //??
    if (canon.size() == 1 || precision == 0) return canon[0];

    cpp_rational start {1, canon[(precision - 1) % (canon.size() - 1) + 1]};
    for (int i {precision - 1}; i > 0; --i)
    {
        start = 1 / (start + canon[(i - 1) % (canon.size() - 1) + 1]);
    }

    return start + canon[0];
}

inline bool isSolution(boost::multiprecision::cpp_rational sol, int256_t d)
{
    return numerator(sol) * numerator(sol) == denominator(sol) * denominator(sol) * d + 1;
}

bool isSquare(int256_t n)
{
    int256_t rt {static_cast<int256_t>(std::floor(sqrt(n).convert_to<float>()))};
    return rt * rt == n;
}

int main()
{
    using namespace boost::multiprecision;

    cpp_int maxX {0};
    cpp_int maxD {0};

    for (int i {2}; i <= 1000; ++i)
    {
        if (isSquare(i))
            continue;
        
        std::vector<int> canon {canonicalForm(i)};
        cpp_rational sol {canon[0]};
        int prec {1};
        while(!isSolution(sol, i))
        {
            sol = sqrtExpansion(canon, prec);
            ++prec;
        }

        if (numerator(sol) > maxX)
        {
            maxX = numerator(sol);
            maxD = i;
        }
    }

    std::cout << "D: " << maxD << '\n';
    std::cout << "x: " << maxX << '\n';
    return 0;
}