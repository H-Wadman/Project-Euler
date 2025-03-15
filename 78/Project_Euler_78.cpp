#include <iostream>
#include <cmath>
#include <vector>
#include <cstdint>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

cpp_int p(int n)
{
    
    if (n < 0) return 0;
    static std::vector<cpp_int> previous {1, 1};
    if (n + 1 <= previous.size())
        return previous[n];

   int k {1};
   cpp_int res {0};
   int sign {-1};
   while (true)
   {
        sign = -sign;
        int cand {n - k * (3 * k - 1) / 2};
        int negCand {n + k * (3 * -k - 1) / 2};
        if (cand < 0 || negCand < 0)
        {
            if (cand >= 0)
            {
                res += sign * p(cand);
            }
            if (negCand >= 0)
            {
                res += sign * p(negCand);
            }
            if (n == previous.size())
                previous.push_back(res);
            return res;
        }
        res += sign * p(cand) + sign * p(negCand);

        k += 1;
   }

   throw (std::runtime_error("Reaching end of p-function should be impossible"));
}

int main()
{
    int n {1};

    while (p(n) % 1'000'000 != 0)
    {
        ++n;
    }
    
    std::cout << "Solution: " << n << '\n';

    return 0;
}