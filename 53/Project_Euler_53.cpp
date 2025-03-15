#include <iostream>
#include <cstdint>

std::int64_t factorial(int n)
{
    std::int64_t result {1};
    while (n > 0)
    {
        result *= n;
        --n;
    }
    return result;
}

std::int64_t combination(int n, int k)
{
    int max {(n - k > k) ? n - k : k};
    int min {n - max};
    std::int64_t result {1};
    while (n > max)
    {
        result *= n;
        --n;
    }
    result /= factorial(min);
    
    return result;
}

int cnKExceeds(int n, std::int64_t limit)
{
    for (int i {0}; i <= n; ++i)
    {
        if (combination(n, i) > limit) return i;
    }
    return -1;
}

int exceeds(int n, int k)
{
    if (k == -1) return 0;

    if (n % 2 == 0) 
    {
        return n - 2*k + 1;
    }
    else
    {
        return (n + 1 - 2 * k);
    }
}

int main()
{
    int sum {0};
    for (int n (1); n <= 100; ++n)
    {
        sum += exceeds(n, cnKExceeds(n, 1'000'000));
    }

    std::cout << sum << '\n';

    return 0;
}