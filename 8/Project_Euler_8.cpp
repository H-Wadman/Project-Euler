#include <iostream>

// Finds the largest product possible from 13 adjacent digits within a 1000-digit number
int main()
    {

        long long maxValue  {0}; //Will be holding the largest product found at the moment
        int       maxIndex  {0};

        int d1  {0};
        int d2  {0};
        int d3  {0};
        int d4  {0};
        int d5  {0};
        int d6  {0};
        int d7  {0};
        int d8  {0};
        int d9  {0};
        int d10 {0};
        int d11 {0};
        int d12 {0};
        int d13 {0};
        
        long long product {};
        int counter {0};
        char temp {};
        while (temp != 'n')
        {
            std::cin >> temp;

            switch(counter % 13)
            {
                case 0:
                d1  = static_cast<int>(temp) - 48;
                break;
                case 1:
                d2  = static_cast<int>(temp) - 48;
                break;
                case 2:
                d3 = static_cast<int>(temp) - 48;
                break;
                case 3:
                d4 = static_cast<int>(temp) - 48;
                break;
                case 4:
                d5 = static_cast<int>(temp) - 48;
                break;
                case 5:
                d6 = static_cast<int>(temp) - 48;
                break;
                case 6:
                d7 = static_cast<int>(temp) - 48;
                break;
                case 7:
                d8 = static_cast<int>(temp) - 48;
                break;
                case 8:
                d9 = static_cast<int>(temp) - 48;
                break;
                case 9:
                d10 = static_cast<int>(temp) - 48;
                break;
                case 10:
                d11 = static_cast<int>(temp) - 48;
                break;
                case 11:
                d12 = static_cast<int>(temp) - 48;
                break;
                case 12:
                d13 = static_cast<int>(temp) - 48;
                break;
            }

            product = 
              static_cast<long long>(d1) * static_cast<long long>(d2) * static_cast<long long>(d3) * static_cast<long long>(d4)
            * static_cast<long long>(d5) * static_cast<long long>(d6) * static_cast<long long>(d7) * static_cast<long long>(d8) 
            * static_cast<long long>(d9) * static_cast<long long>(d10) * static_cast<long long>(d11) * static_cast<long long>(d12)
            * static_cast<long long>(d13);

            if (product > maxValue) 
            {
                maxValue = product;
                maxIndex = counter + 1;
            }
            ++counter;

        }

    std::cout << "This is the max value: " << maxValue << '\n';
    std::cout << "This is the index: " << maxIndex << '\n';

    }