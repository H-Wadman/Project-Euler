#include <iostream>
#include <string>
#include <cmath>

bool stringContainsChar(std::string_view s, char c)
{
    for (int i {0}; i < s.size(); ++i)
    {
        if (s[i] == c) return true;
    }
    return false;
}

void test_stringContainsChar()
{
    assert (stringContainsChar("1234", '1'));
    assert (stringContainsChar("4321", '1'));
    assert (!stringContainsChar("2345", '1'));
}

bool isPandigital(int n)
{
    std::string_view s{std::to_string(n)};
    std::string_view numbers {std::to_string(987654321 % static_cast<int>(pow(10, s.size())))};

    for (int i {0}; i < s.size(); ++i)
    {
        if(!stringContainsChar(s, numbers[i])) return false;
    }

    return true;
}

bool isPrime(int n) //Only implemented for primes > 3
{
    if (n % 2 == 0) return false;
    for (int i {3}; i <= static_cast<int>(sqrt(n)); i += 2) if (n % i == 0) return false;
    return true;
}

void test_isPandigital()
{
    assert (isPandigital(1234));
    assert (isPandigital(2143));
    assert (!isPandigital(2345));
}

int main()
{
    test_stringContainsChar();
    test_isPandigital();

    for (int i {987'654'321}; i > 0; i -= 2)
    {
        if (isPandigital(i) && isPrime(i))
        {
            std::cout << i << '\n';
            break;
        }
    }

    return 0;

}