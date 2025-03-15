#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdint>


bool isWellFormed(std::vector<int> t)
{
    return !(t[t.size()-1] > 9);
}

std::vector<int> form(std::vector<int> v)
{
    int digit {0};
    for (int i {0}; i < v.size()-1; i++)
    {
        digit = v[i] / 10;
        v[i] -= digit * 10;
        v[i+1] += digit;
    }

    while(!isWellFormed(v))
    {
        digit = v[v.size()-1] / 10;
        v[v.size()-1] -= digit * 10;
        v.push_back(digit);
    }
    
    return v;
}

void printNumber(std::vector<int> v)
{
    for (int i {static_cast<int>(v.size()) - 1}; i >= 0; i--)
    {
        std::cout << v[i];
    }
    std::cout << '\n';
}

int main()
{
    std::vector<int> fibStor {1};
    std::vector<int> fibLiten {1};
    int fibCounter {2};

    while (fibStor.size() < 1000)
    {
        std::vector<int> temp {fibStor};

        for (int i {0}; i < fibLiten.size(); i++)
        {
            fibStor[i] += fibLiten[i];
        }

        fibStor = form(fibStor);
        fibLiten = temp;
        ++fibCounter;
    }

    //printNumber(fibStor);
    std::cout << fibCounter;

    return 0;
}