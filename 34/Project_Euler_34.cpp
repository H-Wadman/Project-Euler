#include <iostream>
#include <cmath>
#include <vector>
#include <cstdint>

std::vector<int> digits(int n)
{
    int size {static_cast<int>(log10(n))};
    std::vector<int> result {};

    for (int i {size}; i >= 0; --i)
    {
        int temp {n / static_cast<int>(pow(10, i))};
        result.push_back(temp);
        n -= temp * static_cast<int>(pow(10, i));
    }

    return result;
}

int factorial(int a)
{
    int x {1};
    for (int i {1}; i <= a; ++i)
    {
        x *= i;
    }
    return x;
}

bool isFactorialSum(int n)
{
    std::vector dig {digits(n)};
    std::int32_t sum {0};
    for (int i {0}; i < dig.size(); ++i)
    {
        sum += factorial(dig[i]);
    }
    return sum == n;
}

void test_isFactorialSum()
{
    assert (isFactorialSum(145));
    assert (!isFactorialSum(5));
}

int main()
{
    test_isFactorialSum();
    
    std::int64_t sum {0};
    for (int i {10}; i <= 2540160; ++i) if (isFactorialSum(i)) sum += i;
    std::cout << sum << '\n';

    return 0;
}