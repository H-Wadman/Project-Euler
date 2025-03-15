#include <iostream>
#include <cmath>

// Will check if an integer >= 3 is prime. Does not handle special cases or faulty input
bool isPrime(int p) 
{
    for(int i = 3; i <= sqrt(p); i += 2)
        {
            if(p % i == 0)
            {
                return false;
            }
        }
    return true;
}

//Sums the values of all primes under(strict) n (n > 2)
int main()
{
    int n {2000000}; //2 million
    long primeSum {2};
    
    for(int i = 3; i < n; i += 2)
    {
        if(isPrime(i))
        {
            primeSum += i;
        }
    }

    std::cout << primeSum; 
}