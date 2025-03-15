#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstdint>

std::string convString(int n)
{
    std::stringstream intermediary {};
    intermediary << n;
    
    std::string result {};
    intermediary >> result;
    return result;
}

std::vector<int> convBinary(int n)
{
    std::vector<int> v (static_cast<int>(log2(n) + 1));

    for (int i {0}; i < v.size(); ++i)
    {
        int quotient = n / static_cast<int>(pow(2, v.size() - 1 - i));
        v[i] = quotient;
        n -= quotient * static_cast<int>(pow(2, v.size() - 1 - i));
    }

    return v;
}

void test_convBinary()
{
    std::vector<int> test {1,0,0,0};
    std::vector<int> test2 {1, 0, 1, 0, 1, 0};
    assert (convBinary(8) == test);
    assert (convBinary(42) == test2);
}

//Checks if a function is a decimal palindrome
bool isDecPal(int n)
{
    std::string s {convString(n)};

    for (int a {0}; a < (s.size() + 1)/2; ++a)
    {
        if (s[a] != s[s.size() - 1 - a]) return false;
    }

    return true;
}

//Checks if a function is a binary palindrome
bool isBinPal(int n)
{
    std::vector<int> v{convBinary(n)};
    {
        for (int a{0}; a < (v.size() + 1) / 2; ++a)
        {
            if (v[a] != v[v.size() - 1 - a]) return false;
        }

        return true;
    }
}

int main()
{
    test_convBinary();


    std::int_fast32_t sum {0};

    for (int i {1}; i < 1'000'000; ++i)
    {
        if (isDecPal(i) && isBinPal(i)) sum += i;
    }
    std::cout << sum << '\n';
    
    return 0;
}