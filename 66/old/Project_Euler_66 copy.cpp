#include <iostream>
#include <array>
#include <algorithm>
#include <cmath>

inline bool isSolution(int d, long long x2, long long y2)
{
    return x2 - d * y2 == 1;
}

int main()
{
    constexpr int arraySize {100'000'000};
    long long* squareList {new long long[arraySize]};
    for(long long i {1}; i <= arraySize; ++i)
    {
        squareList[i-1] = i * i;
    }

    long long maxX {0};
    int maxD {0};
    for(int d {2}; d <= 1000; ++d)
    {
        if (std::find(squareList, squareList + arraySize, d) != squareList + arraySize) continue;

        for (int yIndex{0}; yIndex < arraySize; ++yIndex)
        {
            long long y2{squareList[yIndex]};

            if (std::binary_search(squareList, squareList + arraySize, d * y2 + 1))
            {
                long long x2 {*std::find(squareList, squareList + arraySize, d * y2 + 1)};
                if (x2 > maxX)
                {
                    maxX = x2;
                    maxD = d;
                }
                goto nextD;
            }
        }

        std::cout << "Solution not found for " << d << '\n';
    nextD:
    ;
    }
    std::cout << sqrt(maxX) << '\n';
    std::cout << maxX << '\n';
    std::cout << maxD << '\n';
    
    return 0;
}