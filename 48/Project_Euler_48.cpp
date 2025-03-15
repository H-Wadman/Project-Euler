#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>


bool isPrime(std::int64_t n)
{
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (std::int64_t i {3}; i <= static_cast<std::int64_t>(sqrt(n)); i += 2)
    {
        if (n % i == 0) return false;
    }
    return true;
}

std::vector<std::int64_t> primeFactors(std::int64_t p)
{
    if (isPrime(p)) return {p};
    if (p < 2) return {-1};
    std::vector<std::int64_t> factors {};
    while (!isPrime(p))
    {
        if (p % 2 == 0)
        {
            factors.push_back(2);
            p /= 2;
        }
        else
        {
            for (std::int64_t i {3}; i <= static_cast<std::int64_t>(sqrt(p)); i += 2)
            {
                if (p % i == 0)
                {
                    factors.push_back(i);
                    p /= i;
                    break;
                }
            }
        }
    }
    factors.push_back(p);
    return factors;
}

inline std::vector<std::int64_t> lastDigits(std::vector<std::int64_t> v)
{
    for (std::int64_t i {0}; i < v.size(); ++i)
    {
        v[i] = v[i] % 10'000'000'000;
    }
    return v;
}

std::int64_t beräknaProdukt(std::vector<std::int64_t> v)
{
    std::int64_t produkt {1};

    for (std::int64_t a : v)
    {
        if (a != 0) 
        {
            produkt *= a;
            produkt %= 10'000'000'000;
        }

    }
    return produkt % 10'000'000'000;
}

std::int64_t powI(std::int64_t k, std::int64_t i)
{
    std::int64_t result {1};
    for (int j {1}; j <= i; ++j)
    {
        result *= k;
        result %= 10'000'000'000;
    }
    return result;
}

int main()
{
    std::int64_t sum {1}; //Alla tal som har primtalsprodukt 1 tas bort, 1 själv läggs till manuellt

    for (int i {2}; i <= 1000; ++i)
    {
        std::int64_t k {beräknaProdukt(primeFactors(i))};
        std::cout << "Sum: " << sum << '\n';
        sum += static_cast<std::int64_t>(powI(k,i)) % 10'000'000'000;
        std::cout << "Add: " << static_cast<std::int64_t>(powI(k,i)) % 10'000'000'000 << '\n';
        sum %= 10'000'000'000;
    }

    std::cout << sum << '\n';

    return 0;
}