#include <iostream>

int main()
{
    int counter     {0};
    int maxCounter  {0};
    int maxNumber   {0};

    for (int i = 1; i < 1000001; i += 1)
    {
        counter = 0;
        u_int64_t n = i;
        while(n != 1)
        {
            if( n % 2 == 0)
            {
                n = n/2;
            }
            else
            {
                n = 3*n + 1;
            }
            counter++;
        }
        if(counter > maxCounter)
        {
            maxCounter = counter;
            maxNumber = i;
        }
   }

    std::cout << maxNumber << " " << maxCounter << std::endl;
    return 0;
}