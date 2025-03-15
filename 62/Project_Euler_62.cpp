#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>

using ull = unsigned long long;

bool isCube(ull n)
{   
    ull temp {static_cast<ull>(std::cbrt(n))};
    return temp * temp * temp == n;
}

int main()
{
    bool found {false};
    ull k {1};
    
    while(!found)
    {
        ull cube{k * k * k};
        int counter {0};
        std::string s {std::to_string(cube)};
        do
        {   
            if(s[0] != 0 && isCube(std::stoull(s))) ++counter;
            
        } while(std::next_permutation(s.begin(), s.end()));

        if(counter == 5)
        {
            std::cout << "Solution: " << cube << " k: " << k << '\n';
            found = true;
        }

        //std::cout << counter << '\n';
        ++k;
    }

    return 0;
}