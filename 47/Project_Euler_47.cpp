#include <iostream>
#include <vector>
#include <cmath>

bool isPrime(int n)
{
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (int i {3}; i <= static_cast<int>(sqrt(n)); i += 2)
    {
        if (n % i == 0) return false;
    }
    return true;
}

std::vector<int> primeFactors(int p)
{
    if (isPrime(p)) return {p};
    if (p < 2) return {-1};
    std::vector<int> factors {};
    while (!isPrime(p))
    {
        if (p % 2 == 0)
        {
            if (factors.size() == 0)
            {
                factors.push_back(2);
            }
            p /= 2;
        }
        else
        {
            for (int i {3}; i <= static_cast<int>(sqrt(p)); i += 2)
            {
                if (p % i == 0)
                {
                    if (factors.size() == 0) factors.push_back(i);
                    else if(factors.back() != i) factors.push_back(i);
                    p /= i;
                    break;
                }
            }
        }
    }
    if (factors.size() != 0 && factors.back() != p) factors.push_back(p);
    return factors;
}



int main()
{
    int current {1};
    while (true)
    {
        if (primeFactors(current).size() == 4 && primeFactors(current+1).size() == 4 && primeFactors(current+2).size() == 4 && primeFactors(current+3).size() == 4)
        {
            std::cout << current << '\n';
            /* std::vector<int> t1 {primeFactors(current)};
            std::vector<int> t2 {primeFactors(current+1)};
            std::vector<int> t3 {primeFactors(current+2)};

            for (int e : t1) std::cout << e << ' ';
            std::cout << '\n';
            for (int e : t2) std::cout << e << ' ';
            std::cout << '\n';
            for (int e : t3) std::cout << e << ' ';
            std::cout << '\n'; */
            break;
        }
        ++current;
    }
    
    return 0;
}