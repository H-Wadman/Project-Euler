#include <iostream>

/** Function that returns the number of divisors a number has (including trivial ones)
 *  @param n a positive integer
 *  @return the number of divisors of n (held in counter)
 **/
int numberOfDivisors(std::int_fast32_t n)
{
    //Holds the number of divisors found. We're directly adding the trivial divisors
    //so the program doesn't have to spend time finding them
    int counter {2}; 

    
    //Since we've already added the trivial divisor n, we only need to check integers >= 2 && <= n/2
    for (int i {2}; i <= static_cast<double>(n) / 2.0; i++) 
    {
        if (n % i == 0)
        {
            counter++;
        }
    }

    return counter;
}

/** Add function. Here used to get the next triangle number given the current one (don't know how to pass by reference yet :)))
 *  @param currentTriangle a positive integer (int)
 *  @param nextTriangleTerm a positive integer (int)
 *  @return currentTriangle + nextTriangleTerm
**/
int nextTriangleNumber(int currentTriangle, int nextTriangleTerm)
{
    return currentTriangle + nextTriangleTerm;
}

int main()
{
    std::int_fast32_t currentTriangle {1};  // 1 is the first triangle term
    int nextTriangleTerm {2};       // 2 is the next natural number and thus the first term to add

    while (numberOfDivisors(currentTriangle) <= 500)
    {
        currentTriangle = nextTriangleNumber(currentTriangle, nextTriangleTerm);
        nextTriangleTerm++;
    }
    
    std::cout << currentTriangle << '\n';

}