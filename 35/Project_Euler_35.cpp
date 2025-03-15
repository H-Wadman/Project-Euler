#include <iostream>
#include <cmath>
#include <vector>

std::vector<int> listDigits(int n)
{
    int size {static_cast<int> (log10(n))};
    std::vector<int> result {};

    for (int i {size}; i >= 0; --i)
    {
        int temp {n / static_cast<int>(pow(10, i))};
        n -= temp * static_cast<int>(pow(10, i));
        result.push_back(temp);
    }
    return result;
}

void test_listDigits()
{
    std::vector<int> v1 {1, 2, 3};
    assert (listDigits(123) == v1);
    assert (listDigits(1233) != listDigits(123));
    assert (listDigits(321) != v1);
}

int offset(int n)
{
    std::vector<int> digits {listDigits(n)};
    int size {static_cast<int>(digits.size())};

    int result {0};
    for (int i {1}; i < digits.size(); ++i)
    {
        result += digits[i] * static_cast<int>(pow(10, size - i));
    }
    result += digits[0];

    return result;
}

void test_offset()
{
    assert (offset(1) == 1);
    assert (offset(123) == 231);
    assert (offset(123) != 312);
}

bool isPrime(int n)
{
    if (n == 1) return false;

    if (n == 2) return true;
    else if (n % 2 == 0) return false;


    
    for (int i {3}; i <= static_cast<int>(sqrt(n)); i += 2)
    {
        if (n % i == 0) return false;
    }

    return true;
}

bool inVector(std::vector<int> v, int p)
{
    for (int i {0}; i < v.size(); ++i)
    {
        if (v[i] == p) return true;
    }
    return false;
}

bool isCircularPrime(int n)
{
    if(inVector(listDigits(n), 0)) return false;
    int size {static_cast<int>(log10(n))};
    for (int j{0}; j <= size; ++j)
    {
        if (!isPrime(n)) return false;
        n = offset(n);
    }

    return true;
}

int main()
{
    test_listDigits();
    test_offset();

    std::vector<int> circularPrimes {2};
    for (int i {1}; i < 1'000'000; i += 2)
    {
        if (isCircularPrime(i)) circularPrimes.push_back(i);
    }
    for (int i {0}; i < circularPrimes.size(); ++i)
    {
        std::cout << circularPrimes[i] << '\n';
    }
    std::cout << '\n';
    
    std::cout << circularPrimes.size();

    return 0;
}