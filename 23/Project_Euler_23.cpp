#include <iostream>

/**Sums all the proper divisors of a number
 * @param n an integer
 * @return the sum of all proper divisors of n
**/
int sumOfDivisors(int n)
{
    int tempSum {0};
    for (int i {1}; i <= n / 2; i++)
    {
        if (n % i == 0)
        {
            tempSum += i;
        }
    }
    return tempSum;
}

/**Checks if a number is abundant (if the sum of its divisors are larger than itself)
  * @param n a positive natural number
  * @return true if n's integers are larger than n, false otherwise
 **/
bool isAbundant(int n)
{
    return (sumOfDivisors(n) > n);
}

/**Returns true if a number can be written as a sum of abundant numbers
 * @param n a positive natural number
 * @return true if n can be written as a sum of two abundant numbers, false otherwise
**/
bool isSumOfAbundantNumbers(int n)
{
    for (int j {1}; j <= n/2; j++)
    {
        if (isAbundant(j) && isAbundant(n-j))
        {
            return true;
        }
    }

    return false;
}

/**Prints the sum of all numbers who cannot be written as a sum of abundant numbers
 * @return 0 if everything goes as planned :)
**/
int main()
{
    
    // Will hold the sum of all numbers that cannot be written as a sum of abundant numbers
    int nonAbundantSum {0};
    //Will decide up to which number we will check summability of abundant numbers
    constexpr int abundantLimit = 28123;

    for (int i {1}; i <= abundantLimit; i++)
    {
        if(!isSumOfAbundantNumbers(i))
        {
            nonAbundantSum += i;
        }
    }
    std::cout << nonAbundantSum << '\n';

    return 0;
}