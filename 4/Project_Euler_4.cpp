#include <iostream>
#include <cmath>
using namespace std;

int numberOfDigits(int i)
{
    return ( (log10(i) + 1) / 1);
}


// Tests if an integer is a palindrome
bool isPalindrome(int p)
{
    int mirrorP { 0 };

    //Inverts the order of p and puts it into mirrorP
    int numberOfDigitsTest { numberOfDigits(p) };

    if ( numberOfDigits(p) == 5 )
    {
        mirrorP = (( p / 10000 ) + 10 * (( p / 1000 ) % 10) + 100 * (( p / 100 ) % 10) + 1000 * (( p / 10) % 10) + 10000 * ( p % 10));
    }
    else
    {
        mirrorP = ( p / 100000 ) + 10 * (( p / 10000) % 10) + 100 * (( p / 1000 ) % 10) + 1000 * (( p / 100) % 10) + 10000 * (( p / 10) % 10) + 100000 * ( p % 10 );
    }

    return (p == mirrorP);

}


/** Finds the largest 3-digit divisor of a 5 digit number such that the quoitient is also a 3-digit number
 * @param r the numerator
 * @return the largest 3 digit divisor of r for which the quotient is also 3 digits
 **/
int largestDivisor(int r)
{
    int q { 999 };

    while ( (r % q != 0) && q > 100)
    {
        q--;
    }

    if ( q <= 100 || r / q > 1000 )
    {
        return 0;
    }

    return q;
    
}

int main()
{

    int n { 998001 };
    bool condition { false };
    int divisor{ 0 };

    while ( condition == false)
    {
        if ( isPalindrome(n)  && largestDivisor(n) != 0 )
        {
            condition = true;
        }
        else
        {
            n--;
        }
        
    }
 
    std::cout << n << endl << largestDivisor(n);

   

}