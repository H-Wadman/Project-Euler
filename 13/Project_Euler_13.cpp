#include <iostream>
#include <iomanip>


int main()
{
    double sum {0};
    double currentTerm {};

    
    for (int i {0}; i < 100; i++)
    {
        std::cin >> currentTerm;
        sum += currentTerm;
    }


    std::cout << '\n' << std::setprecision(11) << sum << '\n';

    return 0;
}