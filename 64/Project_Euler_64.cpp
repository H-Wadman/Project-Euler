#include <cmath>
#include <vector>
#include <iostream>

struct period
{
    int m;
    int d;
    int a;
};

inline period radicalToPeriod(int n)
{
    return period{1, n, static_cast<int>(sqrt(n))};
}

int canonicalForm(unsigned int s)
{
    int m {0};
    int d {1};
    int a {static_cast<int>(sqrt(s))};
    int a_0 {a};

    int counter {0};
    while(a != 2 * a_0)
    {
        ++counter;

        m = d * a - m;
        d = (s - m * m) / d;
        a = (a_0 + m) / d;
    }

    return counter;
}

inline bool isSquare(unsigned int n)
{   
    double f {std::floor(sqrt(n))};
    return static_cast<int>(f * f) == n;
}

int main()
{
    int counter {0};

    for (unsigned int n {2}; n <= 10'000u; ++n)
    {
        if(!isSquare(n) && canonicalForm(n) % 2 == 1)
            ++counter;
    }

    std::cout << counter << '\n';

    return 0;
}