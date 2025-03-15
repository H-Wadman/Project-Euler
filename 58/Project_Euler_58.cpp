#include <iostream>
#include<vector>
#include <cmath>

void addCorners(int DRvalue, int size, std::vector<int>& v)
{
    for(int i {1}; i <= 4; ++i)
    {
        v.push_back(DRvalue + i * (size + 1));
    }
}

bool isPrime(int n)
{   
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for(int i {3}; i <= sqrt(n); ++i)
    {
        if (n % i == 0) return false;
    }

    return true;
}

int primeCorners(const std::vector<int>& v)
{
    int count {0};
    for(std::size_t i {v.size() - 4}; i < v.size(); ++i)
    {
        if (isPrime(v[i])) ++count;
    }

    return count;
}



int main()
{
    int squareSize {3};
    std::vector<int> cornerNumbers {3, 5, 7, 9};
    int numOfPrimes {3};

    
    while(static_cast<float>(numOfPrimes) / (static_cast<float>(cornerNumbers.size()) + 1.0f)> 0.1)
    {
        addCorners(cornerNumbers.back(), squareSize, cornerNumbers);
        numOfPrimes += primeCorners(cornerNumbers);
        squareSize += 2;
    }
    
    std::cout << squareSize << '\n';

    return 0;
}