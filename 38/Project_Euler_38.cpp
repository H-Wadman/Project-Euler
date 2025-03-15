#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>

std::vector<int> listDigits(int n)
{
    int size {static_cast<int>(log10(n))};
    std::vector<int> result {};

    for (int i {size}; i >= 0; --i)
    {
        int currentSize {static_cast<int>(pow(10, i))};
        result.push_back(n / currentSize);
        n -= result[size - i] * currentSize;
    }
    return result;
}
/*
void test_listDigits()
{
    std::vector<int> test {1,2,3};
    assert(listDigits(123) == test);
    assert(listDigits(321) != test);
}
*/
std::int64_t concatenateInt(int a, int b)
{
    int size {static_cast<int>(log10(b)) + 1};

    return a * static_cast<int>(pow(10, size)) + b;
}

/*
void test_contatenateInt()
{
    assert (concatenateInt(123,345) == 123345);
    assert (concatenateInt(10, 10) == 1010);
}
*/

bool inList(std::vector<int> v, int e)
{
    for (int i {0}; i < v.size(); ++i)
    {
        if (v[i] == e) return true;
    }
    return false;
}

bool isPandigital(int n)
{
    std::vector<int> digits {listDigits(n)};
    if (digits.size() != 9) return false;
    for (int i {1}; i <= 9; ++i)
    {
        if (!inList(digits, i)) return false;
    }
    return true;
}

int main()
{
    /*
    test_listDigits();
    test_contatenateInt();
    */
    
    for (std::int_fast64_t i {493827160}; i >= 1; --i)
    {
        int nDigits {static_cast<int>(log10(i)) + 1};
        if (nDigits >= 5) continue;
        else
        {
            std::int_fast64_t current {i};
            for (int j {2}; j <= 9 / nDigits; ++j)
            {
                current = concatenateInt(current, i * j);
            }
            if (isPandigital(current))
            {
                std::cout << current << '\n';
                break;
            }
        }
    }
    

    return 0;
}