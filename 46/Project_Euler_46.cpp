#include <iostream>
#include <cmath>
#include <vector>

bool isPrime(int n)
{
    if (n % 2 == 0) return false;

    for (int i {3}; i <= static_cast<int>(sqrt(n)); i += 2)
    {
        if (n % i == 0) return false;
    }
    return true;
}

int generateNextPrime(int start)
{
    int n {start + 2};
    while (!isPrime(n)) n += 2;

    return n;
}

int generateNextComposite(int start) //Odd
{
    int n {start + 2};
    while (isPrime(n)) n += 2;

    return n;
}

bool isDSquare(int n)
{
    if (n % 2 != 0) return false;
    n /= 2;

    int i {1};
    while(i * i < n) ++i;

    return i*i == n;
}

int main()
{

    std::vector<int> primes {2, 3};
    int currentComposite {7};
    bool foundNumber {false};
    while (foundNumber == false)
    {
        currentComposite = generateNextComposite(currentComposite);
        while(primes.back() < currentComposite)
        {
            primes.push_back(generateNextPrime(primes.back()));
        }
        foundNumber = true;
        for (int i {0}; i < primes.size() - 1; ++i)
        {
            if(isDSquare(currentComposite - primes[i])) foundNumber = false;
        }
    }

    std::cout << currentComposite << '\n';
    return 0;
}