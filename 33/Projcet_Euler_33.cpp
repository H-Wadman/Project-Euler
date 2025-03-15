#include <iostream>
#include <cmath>

bool doubleEqual(double a, double b, double absEpsilon, double relEpsilon)
{
    // Check if the numbers are really close -- needed when comparing numbers near zero.
    double diff{ std::abs(a - b) };
    if (diff <= absEpsilon)
        return true;

    // Otherwise fall back to Knuth's algorithm
    return (diff <= (std::max(std::abs(a), std::abs(b)) * relEpsilon));
}

bool canFraction(int a, int b)
{
    double fraction {static_cast<double>(a) / b};
    if( a % 10 == 0 || b % 10 == 0) return false;
    if (((a % 10) == (b % 10)) && doubleEqual((static_cast<double>(a / 10) / (b / 10)), fraction, 1e-12, 1e-8))
    {
        return true;
    }
    else if (((a % 10) == (b / 10)) && doubleEqual((static_cast<double>(a / 10) / (b % 10)), fraction, 1e-12, 1e-8))
    {
        return true;
    }
    else if (((a / 10) == (b % 10)) && doubleEqual((static_cast<double>(a % 10) / (b / 10)), fraction, 1e-12, 1e-8))
    {
        return true;
    }
    else if (((a / 10) == (b / 10)) && doubleEqual((static_cast<double>(a % 10) / (b % 10)), fraction, 1e-12, 1e-8))
    {
        return true;
    }

    return false;

}

void test_canFraction()
{
    assert (canFraction(49, 98));
    assert (!canFraction(30, 50));
}

int main()
{
    test_canFraction();

    for (int i {10}; i < 100; ++i)
    {
        for (int j {10}; j < i; ++j)
        {
            if (canFraction(j, i))
            {
                std::cout << j << '/' << i << '\n';
            }
        }
    }
    return 0;
}