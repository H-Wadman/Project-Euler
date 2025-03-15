#include <iostream>
#include <cmath>
#include <cstdint>
#include <vector>

/**Returns a list of all the digits of a number
 * @param n - the number to be checked
 * @return a vector containing all the digits of the number
**/
std::vector<int> listDigits(int n)
{
    using std::vector;
    const int numberOfDigits {static_cast<int>(log10(n)) + 1};
    vector<int> digits (numberOfDigits);

    for (int i {0}; i < numberOfDigits; i++)
    {
        digits[i] = n / static_cast<int>(pow(10, numberOfDigits - i - 1));
        n -= digits[i] * static_cast<int>(pow(10, numberOfDigits - i - 1));
    }
    
    return digits;
}



/**Checks if a number is equal to the sum of its digits raised to the fifth power
 * @param n - a number to be checked
 * @return true if n can be expressed as the sum described above, false otherwise
**/
bool is5PowSum(int n)
{
    std::vector<int> digits = listDigits(n);


    for (int i {0}; i < digits.size(); i++)
    {
        digits[i] = static_cast<int>(pow(digits[i], 5));
    }
    std::int64_t sum {0};
    for (int i {0}; i < digits.size(); i++)
    {
        sum += digits[i];
    }

    if (n == sum)
    {
        return true;
    }

    return false;
}


int main()
{
    std::cout << '\n';
    constexpr int limit {295245}; // The highest number possible, all other numbers will be too big to be reached

    std::int_least32_t sum {0};
    for (int i {2}; i <= limit; i++)
    {
        if (is5PowSum(i))
        {
            std::cout << i << '\n';
            sum += i;
        }
    }

    std::cout << "The sum of these numbers are: " << sum << '\n';

    return 0;
}