#include <iostream>


// Will sum all multiples of n < k and return it.

int sumOfMultiples(int n, int k)
{
    int sum = 0;
    int currentNumber = n;

    while ( currentNumber < k )
    {
        sum = sum + currentNumber;
        currentNumber = currentNumber + n;
    }

    return sum;
}


int main()
{

    int sum = 0;

    sum = sumOfMultiples(3, 1000);
    sum = sum + sumOfMultiples(5, 1000);
    sum = sum - sumOfMultiples(15, 1000);

    std::cout << sum << std::endl;


    return 0;
}