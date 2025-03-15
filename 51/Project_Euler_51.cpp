#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>

bool isPrime(int n)
{
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (int i {3}; i <= sqrt(n); i += 2)
    {
        if (n % i == 0) return false;
    }
    return true;
}

std::string createMask(int digits, int n)
{
    std::string result {};

    for (int i {1}; i <= n; ++i)
    {
        result += '*';
    }
    for (int i{1}; i <= digits - n; ++i)
    {
        result += '-';
    }
    return result;
}

int nPrimeReplacements(std::string mask)
{
    int count {0};
    int startNumber {0};
    if (mask[0] == '*') startNumber = 1;

    for (int i {startNumber}; i <= 9; ++i)
    {
        std::string current {mask};
        for (int j {0}; j < mask.size(); ++j)
        {
            if (current[j] == '*') current[j] = static_cast<char>(i + 48);
        }
        if (isPrime(std::stoi(current))) ++count;

    }

    return count;
}

void printLowestPrime(const std::string& mask)
{
    std::string copy {mask};
    int start {0};
    if (mask[0] == '*') start = 1;
    for (int i {start}; i <= 9; ++i)
    {
        copy = mask;
        for (int j {0}; j < mask.size(); ++j)
        {
            if (copy[j] == '*') copy[j] = static_cast<char>(i + 48);
        }
        if (isPrime(std::stoi(copy)))
        {
            std::cout << std::stoi(copy) << '\n';
            goto finished;
        }
    }
finished:
    ;
}

int maxPrimes(int n, int printValue)
{
    int nDigits {static_cast<int>(log10(n)) + 1};
    std::string nString {std::to_string(n)};

    int maxCount {0};
    for (int i {1}; i <= nDigits; ++i)
    {
        std::string mask {createMask(nDigits, i)};
        do
        {
            std::string current {nString};
            for (int j {0}; j < nDigits; ++j)
            {
                if (mask[j] == '*') current[j] = '*';
            }
            int k = nPrimeReplacements(current);
            if(k > maxCount) maxCount = k;

            if (k == printValue) 
            {
                printLowestPrime(current);
                goto found;
            }

        } while (std::next_permutation(mask.begin(), mask.end()));
        
    }
found:
    return maxCount;
}


int main()
{

    int i {3};
    while (true)
    {
        if(maxPrimes(i, 8) == 8) break;
        i += 2;
    }

    return 0;
}