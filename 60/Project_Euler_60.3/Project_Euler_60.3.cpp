#include <iostream>
#include <vector>
#include <array>

using ull = unsigned long long;

std::vector<int> sums {};

ull mulmod(ull a, ull b, ull modulo)
{
    #ifdef __GNUC__
    return ((unsigned __int128)a * b) % modulo;
    #endif

    a %= modulo;
    b %= modulo;

    if (a <= 0xFFFFFF && b <= 0xFFFFFF) return (a * b) % modulo;

    if(b > a) std::swap(a, b);

    ull result {0};
    while(a > 0 && b > 0)
    {
        //If b is odd
        if(b & 1)
        {
            result += a;
            if(result >= modulo) 
                result -= modulo;
            //Normally b--, men aja bitshift sen
        }

        //If b is even
        a <<= 1;
        if (a >= modulo)
        {
            a -= modulo;
        }

        b >>= 1;
    }

    return result;
}

ull powmod(ull base, ull exponent, ull modulo)
{
    ull result {1};
    while (exponent > 0)
    {
        //Odd
        if (exponent & 1) result = mulmod(result, base, modulo);


        base = mulmod(base, base, modulo);
        exponent >>= 1;
    }
    return result;
}

bool isPrime(ull p)
{
    constexpr uint bitmaskPrimes2to31 = (1 <<2 ) | (1 << 3) | (1 << 5) 
        | (1 << 7) | (1 << 11) | (1 << 13) 
        | (1 << 17) | (1 << 19) | (1 << 23)
        | (1 << 29);


    if(p < 31) return (bitmaskPrimes2to31 & (1 << p)) != 0;

    if(p % 2 == 0 || p % 3 == 0 || p % 5 == 0 || p % 7 == 0 || p % 11 == 0 || p % 13 == 0 || p % 17 == 0)
        return false;

    if(p < 17*19) return true;

    constexpr uint STOP {0};
    constexpr std::array<uint, 2> testAgainst1 {377687, STOP};
    constexpr std::array<uint, 3> testAgainst2 {31, 73, STOP};
    constexpr std::array<uint, 4> testAgainst3 {2, 7, 61, STOP};
    //These two test cases work up to 2^32
    constexpr std::array<uint, 5> testAgainst4 {2, 13, 23, 1662803, STOP};
    constexpr std::array<uint, 8> testAgainst7 {2, 325, 9375, 28178, 450775, 9780504, 1795265022, STOP};


    const uint* testAgainst {testAgainst7.data()};
    if(p < 5329) testAgainst = testAgainst1.data();
    else if (p < 9080191) testAgainst = testAgainst2.data();
    else if (p < 4759123141ULL) testAgainst = testAgainst3.data();
    else if (p < 1222004669633ULL) testAgainst = testAgainst4.data();

    ull d = p - 1;
    d >>= 1;
    uint shift {0};
    while((d & 1) == 0)
    {
        ++shift;
        d >>= 1;
    }
    
    do
    {
        ull x {powmod(*testAgainst++, d, p)};
        if(x == 1 || x == p - 1) continue;

        bool maybePrime {false};
        for (uint r {0}; r < shift; ++r)
        {
            x = powmod(x, 2, p);
            if(x == 1) return false;
            if (x == p - 1)
            {
                maybePrime = true;
                break;
            }
        }

        if(!maybePrime) return false;
    } while(*testAgainst != STOP);

    return true;
} 

ull merge(ull a, ull b)
{
    int factor {10};
    while(factor < b)
    {
        factor *= 10;
    }
    
    return factor*a + b;
}

bool match(ull a, ull b)
{
    return (isPrime(merge(a, b)) && isPrime(merge(b, a)));
}

void checkQuintuple(uint first, const std::vector<uint>& candidates)
{
    for(std::size_t index2 {0}; index2 < candidates.size(); ++index2)
    {
        for(std::size_t index3 {index2 + 1}; index3 < candidates.size(); ++index3)
        {
            if(!match(candidates[index2], candidates[index3])) continue;

            for(std::size_t index4 {index3 + 1}; index4 < candidates.size(); ++index4)
            {
                if(!match(candidates[index2], candidates[index4]) ||
                !match(candidates[index3], candidates[index4]))
                    continue;
                for(std::size_t index5 {index4 + 1}; index5 < candidates.size(); ++index5)
                {
                    if(match(candidates[index2], candidates[index5]) &&
                       match(candidates[index3], candidates[index5]) &&
                       match(candidates[index4], candidates[index5]))
                    {
                        sums.push_back(first + candidates[index2] + candidates[index3] + 
                                       candidates[index4] + candidates[index5]);
                    }
                }
            }
        }
    }
}


int main()
{
    //Number of primes that we will sieve
    constexpr uint maxPrime {20'000};
    //Number of primes we're searching for
    //constexpr uint size {5};

    //Will contain all primes that are possible candidates
    std::vector<uint> primes {};
    primes.reserve(2261);

    for(uint i {3}; i < maxPrime; i += 2)
    {
        bool isPrime {true};
        for (auto a : primes)
        {
            if (a * a > i)  break;
            if(i % a == 0) 
            {
                isPrime = false;
                break;
            }
        }
        if(isPrime) primes.push_back(i);

    }

    for(std::size_t i {0}; i < primes.size(); ++i)
    {
        uint smallPrime = primes[i];

        if (smallPrime == 5) continue;
        std::vector<uint> candidates {};
        for (std::size_t j {i + 1}; j < primes.size(); ++j)
        {
            uint largePrime = primes[j];
            if(match(smallPrime, largePrime))
            {
                candidates.push_back(largePrime);
            }
        }
        
        checkQuintuple(smallPrime, candidates);

    }

    std::sort(sums.begin(), sums.end());
    std::cout << sums.size() << '\n';
    for(auto s : sums)
    {
        std::cout << s << '\n';
    }
}