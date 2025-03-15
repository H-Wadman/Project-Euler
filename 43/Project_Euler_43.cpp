#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
#include <string>

std::vector<int> listDigits(std::int_fast64_t n)
{
    int size {static_cast<int>(log10(n))};
    std::vector<int> result {};
    /*
    for (int i {0}; i <= size; ++i)
    {
        result.push_back(n / static_cast<int>(pow(10, size - i)));
        n -= result[i] * static_cast<int>(pow(10, size - i));
    }
    */
    for (int i {0}; i <= size; ++i)
    {
        int x = static_cast<int>(pow(10, size - i));
        result.push_back(n / x);
        n -= result[i] * x;
    }
    

   return result;
}

void test_listDigits()
{
    std::vector<int> test {1,2,3};
    assert(listDigits(123) == test);
    assert(listDigits(321) != test);
    assert(listDigits(3210) != test);
}

bool inVector(std::vector<int> v, int n)
{
    for (int a : v) if (a == n) return true;
    return false;
}

bool isPandigital(std::int_fast64_t n) //Only implemented for digits 0-9
{
    std::vector<int> digits {listDigits(n)};
    if (digits.size() != 10) return false;
    for (int i {0}; i <= 9; i++)
    {
        if(!inVector(digits, i)) return false;
    }
    return true;
}

void test_isPandigital()
{
    assert (isPandigital(1234567890));
    assert (!isPandigital(123456789));
    assert (!isPandigital(123456780));
}

//A 10 digit number
std::vector<int> divideInThrees(std::string s)
{
    
    std::vector<int> v {};
    for (int i {0}; i <= 7; ++i)
    {
        v.push_back(std::stoi((s.substr(i, 3))));
    }
    return v;
}

void test_divideInThrees()
{
    std::vector<int> test {divideInThrees("1234567890")};
    assert(test[0] == 123);
    assert(test[1] == 234);
    assert(test[2] == 345);
    assert(test[7] == 890);
}

int main()
{
    test_listDigits();
    test_isPandigital();
    test_divideInThrees();

    std::vector<int> primes {1, 2, 3, 5, 7, 11, 13, 17};
    std::string permutations {"0123456789"};
    std::int64_t sum {0};
    do
    {   
        std::int64_t i {std::stoll(permutations)};
        if (static_cast<int>(log10(i)) != 9) continue;
        std::vector<int> threes{divideInThrees(permutations)};
        for (int j{1}; j <= 7; ++j)
        {
            if (threes[j] % primes[j] != 0) goto nextNumber;
        }
        std::cout << i << '\n';
        sum += i;

        nextNumber:
            ;
    } while (std::next_permutation(permutations.begin(), permutations.end()));

    

    std::cout << sum << '\n';

    return 0;
}