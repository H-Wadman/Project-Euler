#include <iostream>
#include <vector>

int sumVec(std::vector<int> t)
{
    int sum {0};
    for (int i {0}; i < t.size(); i++)
    {
        sum += t[i];
    }
    return sum;
}

bool isInVec(int a, std::vector<int> t)
{
    for (int i {0}; i < t.size(); i++)
    {
        if(t[i] == a) return true;
    }
    return false;
}

int sumProperDivisors(int n)
{
    std::vector <int> divisors;
    for (int i {1}; i < n; i++)
    {
        if (n % i == 0)
        {
            if (!isInVec(i, divisors))
            {
                divisors.push_back(i);
            }
        }
    }

    return sumVec(divisors);
}

bool isAmicable(int n)
{
    int p {sumProperDivisors(n)};
    if ((n == sumProperDivisors(p)) && (n != p)) return true;
    return false;
}

void printVec(std::vector<int> t)
{
    for (int i {0}; i < t.size(); i++)
    {
        std::cout << t[i] << '\n';
    }
}

int main()
{
    std::vector<int> amicableNumbers;
    for (int i {1}; i < 10'000; i++)
    {
        if(isAmicable(i)) amicableNumbers.push_back(i);
    }
    std::cout << sumVec(amicableNumbers) << '\n';

    return 0;
}