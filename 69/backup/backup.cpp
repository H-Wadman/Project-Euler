#include <bit>
#include <iostream>
#include <utility>
#include <vector>
#include <set>
#include <chrono> // for std::chrono functions
#include <algorithm>

class Timer
{
private:
	// Type aliases to make accessing nested type easier
	using Clock = std::chrono::steady_clock;
	using Second = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<Clock> m_beg { Clock::now() };

public:
	void reset()
	{
		m_beg = Clock::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
	}
};

std::vector<unsigned int> generateSieve(unsigned int size)
{
    std::vector<unsigned int> primes {{2}};
    for (unsigned int i {3}; i <= size; i += 2)
    {
        bool isPrime {true};

        for (auto p : primes)
        {
            if (p*p > i)
                break;
            
            if (i % p == 0)
            {
                isPrime = false;
                break;
            }
        }

        if (isPrime)
            primes.push_back(i);
    }

    return primes;
}

inline bool isPrime(unsigned int u, std::vector<unsigned int> sieve)
{
    return !(std::find(sieve.begin(), sieve.end(), u) == sieve.end());
}

void test_isPrime(std::vector<unsigned int> sieve)
{
    assert(!isPrime(0, sieve));
    assert(!isPrime(1, sieve));
    assert(isPrime(2, sieve));
    assert(isPrime(2, sieve));
    assert(!isPrime(4, sieve));
    assert(isPrime(5, sieve));
    assert(!isPrime(9, sieve));
}

int gcd(unsigned int u, unsigned int v)
{
    if (u == 0) return v;
    if (v == 0) return u;


    int shift {std::countr_zero(u | v)};
    
    u >>= std::countr_zero(u);
    v >>= std::countr_zero(v);

    while (true)
    {
        if (u > v) std::swap(u, v);
        v -= u;

        if (v == 0)
        {
            return u << shift;
        }

        v >>= std::countr_zero(v);
    }

}

void test_gcd()
{
    assert(gcd(2, 4) == 2);
    assert(gcd(1, 5) == 1);
    assert(gcd(36, 5) == gcd(5, 36));
    assert(gcd(6, 0) == 6);
    assert(gcd(17, 17) == 17);
}

int phi(unsigned int u)
{
    int counter {1};

    for (int i {2}; i < u; ++i)
    {
        if(gcd(u, i) == 1)
            ++counter;
    }

    return counter;
}

void test_phi()
{
    assert(phi(2u) == 1);
    assert(phi(3u) == 2);
    assert(phi(4u) == 2);
    assert(phi(5u) == 4);
    assert(phi(6u) == 2);
    assert(phi(7u) == 6);
    assert(phi(8u) == 4);
    assert(phi(9u) == 6);
    assert(phi(10u) == 4);
}

std::vector<unsigned int> primeFactors(unsigned int u, const std::vector<unsigned int>& sieve)
{
    std::vector<unsigned int> factors;
    if (u == 1 || u == 0)       return factors;
    else if (isPrime(u, sieve)) return std::vector<unsigned int>{u};
    else if (u % 2 == 0)
    {
        for (int i {0}; i < std::countr_zero(u); ++i)
            factors.push_back(2);
    
        u >>= std::countr_zero(u);

        if(u == 1) return factors;
    }
    
    int i {0};
    while(!isPrime(u, sieve))
    {
        if(u % sieve[i] == 0)
        {
            factors.push_back(sieve[i]);
            u /= sieve[i];
        }
        else ++i;
    }
    factors.push_back(u);

    return factors;
}

int phi2(unsigned int u, const std::vector<unsigned int>& sieve)
{   
    std::vector<unsigned int> factors {primeFactors(u, sieve)};
    int counter {1};
    int res {1};

    for (int i {0}; i < factors.size(); ++i)
    {

        if ( i + 1 < factors.size() && factors[i + 1] == factors[i])
            ++counter;
        else
        {
            res *= pow(factors[i], counter - 1) * (factors[i] - 1);
            counter = 1;
        }
    }

    return res;
}

int main()
{
    test_gcd();
    test_phi();

/*     float max {0.0f};
    int n {0};


    for(unsigned int u {2}; u < 10'000u; ++u)
    {
        float current {u / static_cast<float>(phi(u))}; 
        if (current > max)
        {
            max = current;
            n = u;
        }
    }

    std::cout << "Max ratio is " << max << " which is achieved for n = " << n << '\n'; */

    std::vector<unsigned int> sieve {generateSieve(1'000'000)};

    test_isPrime(sieve);


    float max {0.0f};
    int n {0};
    Timer t;
    for(unsigned int i {2u}; i <= 1'000'000u; i += 2)
    {
        if(i % 1000 == 0)
            std::cout << i << '\n';
        float current {i / static_cast<float>(phi2(i, sieve))}; 
        if (current > max)
        {
            max = current;
            n = i;
        }
    }
    std::cout << t.elapsed() << " seconds\n";

    std::cout << "Max ratio is " << max << " which is achieved for n = " << n << '\n';

    return 0;
}