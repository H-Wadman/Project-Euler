#include <iostream>
#include <cmath>


// Checks if primeTest is divisible by two or any uneven numbers less than or equal to the square root of primeTest
bool isPrime(long primeTest)
{
    int n = 3;
    float root = sqrt(primeTest);

    if ( primeTest % 2 == 0 )
    {
        return false;
    }

    while ( n <= root )
    {
        if ( primeTest % n == 0 )
        {
            return false;
        }
        n = n+2;
    }

    return true;

}

long largestPrimeFactor(long k)
{
    long max = k;
    k = sqrt(max) / 1;
    while ( k > 1 )
    {
        if (isPrime(k) && max % k == 0 )
        {
            return k;
        }
        else
        {
            k--;
        }
    }

    return 0;
}

int main()
{

    std::cout << largestPrimeFactor(600851475143) << std::endl;
    
    return 0;

}