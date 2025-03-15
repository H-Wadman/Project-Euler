#include <iostream>
#include <vector>
#include <cmath>

int sumList(std::vector<int>& v, int start, int end)
{
    int sum {0};
    for (int i {start}; i <= end; ++i) sum += v[i];
    return sum;
}

bool isPrime(int n)
{
    if (n < 2)      return false;
    if (n == 2)     return true;
    if (n % 2 == 0) return false;
    
    for (int i {3}; i <= static_cast<int>(sqrt(n)); i += 2)
    {
        if (n % i == 0) return false;
    }

    return true;
}

int generateNextPrime(int previous)
{
    int p {previous + 1};
    while (true)
    {
        if (isPrime(p)) return p;
        ++p;
    }
}

std::vector<int> generatePrimeList(int limit)
{
    std::vector<int> primes {2};
    while (sumList(primes, 0, primes.size() - 1) < limit)
    {
        primes.push_back(generateNextPrime(primes.back()));
    }
    return primes;
}

int main()
{
    constexpr int ceiling {1'000'000};
    std::vector<int> primeList {generatePrimeList(ceiling)};
    int limit {static_cast<int>(primeList.size())};


    int currentSum {0};
    for (int i {limit}; i > 0; --i)
    {
        for (int j {limit - i}; j >= 0; --j)
        {
            currentSum = 0;
            for (int k {0}; k < i; ++k)
            {
                currentSum += primeList[j+k];
            }
            if(isPrime(currentSum) && currentSum < 1'000'000) 
            {
                std::cout <<  currentSum << '\n';
                goto finished;
            }
        }
        
    }
finished:
    return 0;
}