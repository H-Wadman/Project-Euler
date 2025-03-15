#include <iostream>
#include <cmath>

bool isPrime(int n)
{
    if (n <= 1) return false;
    if (n == 2) return true;
    for (int i {3}; i < static_cast<int>(sqrt(n)); i += 2)
    {
        if (n % i == 0) return false;
    }
    return true;
}

int test_isPrime()
{
    if(isPrime(-1))     return 1;
    if(isPrime(1))      return 2;
    if(!isPrime(2))     return 3;
    if(!isPrime(3))     return 4;
    if(!isPrime(37))    return 5;
    if(isPrime(40))     return 6;

    return 0;
}

int maxConsecutivePrimes(int a, int b)
{
    int count{0};
    for (int n{0};; ++n)
    {
        int current{static_cast<int>(pow(n, 2)) + a * n + b};
        if (isPrime(current)) ++count;
        else break;
    }
    return count;
}

int main()
{
    if (test_isPrime() != 0) std::cout << test_isPrime();

    int maxConsec {0};
    int maxA {};
    int maxB {};
    for (int a {-999}; a <= 999; ++a)
    {
        for (int b {-999}; b <= 999; ++b)
        {
            int currentConsec {maxConsecutivePrimes(a,b)};
            if (currentConsec > maxConsec)
            {
                maxConsec = currentConsec;
                maxA = a;
                maxB = b;
            }
        }
    }
    std::cout << "a: " << maxA << '\n';
    std::cout << "b: " << maxB << '\n';
    std::cout << "product: " << maxA * maxB << '\n';
    return 0;
}