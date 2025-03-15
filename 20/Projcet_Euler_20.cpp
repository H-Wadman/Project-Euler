#include <iostream>
#include <vector>
#include <cstdint>

bool isWellFormed(std::vector<int> v)
{
    if (v[v.size() - 1] > 9)
    {
        return false;
    }
    return true;
}

int main()
{
    constexpr int factorial {100};
    std::vector<int> fib {1};

    for (int i {1}; i <= factorial; i++)
    {
        for (int j {0}; j < fib.size(); j++)
        {
            fib[j] *= i;
        }
        for (int j {0}; j < fib.size() - 1; j++)
        {
            if (fib[j] > 9)
            {
                fib[j+1] += fib[j] / 10;
                fib[j] -= fib[j] / 10 * 10;
            }
        }
        while (!isWellFormed(fib))
        {
            fib.push_back(fib[fib.size() - 1] / 10);
            fib[fib.size() - 2] -= fib[fib.size() - 2] / 10 * 10;
        }
    }

    std::int_least64_t sum {0};

    for (int i {0}; i < fib.size(); i++)
    {
        sum += fib[i];
    }

    std::cout << sum << '\n';

    return 0;
}