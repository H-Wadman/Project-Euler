#include <iostream>

bool isRightTriangle(int a, int b, int c)
{
    return (a * a + b * b == c * c);
}

int main()
{
    int maxP {0};
    int maxSolutions {0};
    for (int p {1}; p <= 1000; ++p)
    {
        int c {p / 2};
        int solutionsFound {0};
        for (int a {(p-c) / 2}, b {p - c - a}; c >= p / 3 + (p % 2) != 0; --c)
        {
            a = (p - c) / 2;
            b = p - a - c;
            for (; b < c; ++b, --a)
            {
                if (b < c && isRightTriangle(a, b, c)) ++solutionsFound;
            }
        }
        if (solutionsFound > maxSolutions)
        {
            maxSolutions = solutionsFound;
            maxP = p;
        }
    }

    std::cout << maxP << '\n';
    std::cout << maxSolutions << '\n';

    return 0;
}