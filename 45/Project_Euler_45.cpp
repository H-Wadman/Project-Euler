#include <iostream>
#include <vector>


int main()
{
    

    int currentHex {};
    int n {144};
    int k {n};
    int currentPent {k * (3*k - 1) / 2};
    while (true)
    {
        currentHex = n * (2*n - 1);
        while(currentPent < currentHex)
        {
            //Adds the next pentagonal
            currentPent += 3 * k + 1;
            ++k;
        }
        if(currentPent == currentHex) break;
        else ++n;
    }

    std::cout << currentHex << '\n';

    return 0;
}