#include <iostream>
#include <cmath>
#include <string>
#include <string_view>
#include <algorithm>

bool isPrime(int n)
{
    if (n < 2)      return false;
    if (n == 2)     return true;
    if (n % 2 == 0) return false;
    
    for (int i {3}; i <= static_cast<int>(sqrt(n)); ++i)
    {
        if (n % i == 0) return false;
    }

    return true;
}

bool isPrimePermutation(int n)
{
    if (isPrime(n))
    {

        std::string iString{std::to_string(n)};
        std::string original {iString};
        int currentPermutation {};
        int secPermutation {};
        while (std::next_permutation(iString.begin(), iString.end()))
        {
            currentPermutation = std::stoi(iString);
            if (isPrime(currentPermutation))
            {
                secPermutation = 2 * currentPermutation - n;
                std::string compare {std::to_string(secPermutation)};
                if (isPrime(secPermutation) && std::is_permutation(original.begin(), original.end(), compare.begin(), compare.end())) 
                {
                    std::cout << original << '\n';
                    std::cout << currentPermutation << '\n';
                    std::cout << compare << '\n';
                    return true;
                }
            }

        }
    }
    return false;
}


int main()
{
    for (int i {1001}; i < 9999; i += 2)
    {
        isPrimePermutation(i);
    }

    return 0;

}