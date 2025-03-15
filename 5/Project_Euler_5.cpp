#include <iostream>


double sum(int k)
{
    double tempSum { 0 };

    for ( int n = 1; n <= k; n++)
    {
        tempSum += n;
    }
    return tempSum;
}

double squareSum(int k)
{
    double tempSum { 0 };

    for ( int n = 1; n <= k; n++ )
    {
        tempSum += (n * n);
    }

    return tempSum;
}

int main()
{

    std::cout << squareSum(100) << std::endl;
    
    double sumHundred { sum(100) };

    std::cout << sumHundred << std::endl << sumHundred * sumHundred << std::endl;

    std::cout << "Final solution: " << (sumHundred * sumHundred - squareSum(100) );

    return 0;
}