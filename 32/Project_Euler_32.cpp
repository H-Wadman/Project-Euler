#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

std::vector<int> digits(int n)
{
    std::vector<int> result {};
    int size {static_cast<int>(std::log10(n))};
    for (int i {size}; i >= 0; --i)
    {
        result.push_back(n / static_cast<int>(pow(10, i)));
        n -= pow(10, i) * result[size-i];
    }
    return result;
}

void test_digits()
{
    assert(1 == 1 && "test");
    assert (digits(5)[0] == 5);
    assert (digits(13)[0] == 1 && digits(13)[1] == 3);
}

bool containsDuplicate (std::vector<int> v)
{
    for (int i {0}; i < v.size(); ++i)
    {
        for (int j {1}; i + j < v.size(); ++j)
        {
            if (v[i] == v[i+j]) return true;
        }
    }
    return false;
}

bool containsElement(std::vector<int> v, int a)
{
    for (int i {0}; i < v.size(); ++i)
    {
        if (v[i] == a) return true;
    }
    return false;
}



bool isPandigital(int plicand, int plier, int product)
{
    std::vector<int> plicandD   {digits(plicand)};
    std::vector<int> plierD     {digits(plier)};
    std::vector<int> productD    {digits(product)};

    for (int i {0}; i < plicandD.size(); ++i) productD.push_back(plicandD[i]);
    for (int i {0}; i < plierD.size(); ++i) productD.push_back(plierD[i]);

    return (!containsDuplicate(productD) && !containsElement(productD, 0) && productD.size() == 9);
}

int sumVector(std::vector<int> v)
{
    int sum {0};
    for (int i {0}; i < v.size(); ++i)
    {
        sum += v[i];
    }
    return sum;
}

int main()
{
    std::vector<int> products {};

    for (int i {1}; i < 10'000; ++i)
    {
        for (int j {1}; j < 10'000; ++j)
        {
            int p = i * j;
            if (((static_cast<int>(log10(i)) + static_cast<int>(log10(j)) + static_cast<int>(log10(p))) == 6) && isPandigital(i, j, p) && !containsElement(products, p))
            {
                products.push_back(p);
                std::cout << i << " * " << j << " = " << p << '\n';
            }
        }
    }

    std::cout << sumVector(products) << std::endl;


    return 0;
}