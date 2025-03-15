#include <iostream>
#include <cmath>

bool isPrime(long p)
{
    double primeLimit { sqrt(p) };

    if (p <= 1)
    {
        return false;
    }
    else if (p == 2)
    {
        return true;
    }
    else
    {
        for ( int i = 3; i <= primeLimit; i += 2 )
        {
            if ( p % i == 0 )
            {
                return false;
            }
        }

        return true;
    }
}

int main()
{
    
    int primeCounter    { 1 };   // Will keep track of how many primes we've found and printed. Starts at 1 due to 2
                                // already being checked. We don't want to have to test all even numbers for prime status.

    long primeCandidate { 3 }; // The integer getting checked for prime status

    while ( primeCounter < 10001)
    {
        if ( isPrime(primeCandidate) )
        {
            std::cout << primeCandidate << std::endl;
            primeCounter++;
        }
        
        primeCandidate += 2;

    }

    return 0;
}