#include <iostream>
#include <sstream>
#include <string_view>
#include <cmath>

int removeFirstDigit(int n)
{
    int length {static_cast<int>(log10(n))};
    int size {n / static_cast<int>(pow(10, length))};
    return n - size * static_cast<int>(pow(10, length));
}

int removeLastDigit(int n)
{
    return (n - n % 10) / 10;
}

bool isPrime(int p)
{
    if (p == 1)     return false;
    if (p == 2)     return true;
    if (p % 2 == 0) return false;
    for (int i {3}; i <= static_cast<int>(sqrt(p)); i += 2)    
    { 
        if (p % i == 0) return false;
    }
    return true;
}

bool isTruncatablePrime(int p)
{
    if (!isPrime(p)) return false;
    int p2 {p};
    while (true)
    {
        p = removeLastDigit(p);
        p2 = removeFirstDigit(p2);
        if (p2 == 0) return true;
        if((!isPrime(p)) || (!isPrime(p2))) return false;
    }
}

int main()
{   
    int sum {0};
    int primesFound {0};
    for(int i {10}; primesFound < 11; ++i)
    {
        if (isTruncatablePrime(i)) 
        {
            ++primesFound;
            std::cout << i << ' ';
            sum += i;
        }
    }
    std::cout << '\n' << sum << '\n';

    return 0;
}