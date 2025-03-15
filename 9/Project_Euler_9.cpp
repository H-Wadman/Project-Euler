#include <iostream>

/**
 * Will find the pythagorean triplet a, b, c for which a + b + c = 1000 (c is the hypotenuse)
**/
int main()
{

    int a {1};
    int c {0};
    bool isFound {false}; //Will be set to true when the triple is found, to stop the search

    // Will start testing a=1 and b=1 and then test with larger and larger numbers.
    //a is incremented by 1 and then all b<=a are tested as solutions

    while (!isFound) 
    {
        for(int b = 1; b <= a; b++)
        {
            c = 1000 - a - b; // As a + b + c = 1000 the easiest is to define c this way, and then check for triple-status
            if(a*a + b*b == c*c)
            {
                isFound = true;
                std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;
                std::cout << a * b * c;
            }
        }
        a++;
    }
    

    return 0;
}