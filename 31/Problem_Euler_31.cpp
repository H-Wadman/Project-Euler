#include <iostream>

// Most scuffed program I've ever written
int pennyAmount(int twoPound, int onePound, int fiftyPence, int twentyPence, int tenPence, int fivePence, int twoPence, int startValue)
{
    return startValue - (200*twoPound + 100*onePound + 50*fiftyPence + 20*twentyPence + 10*tenPence + 5*fivePence + 2*twoPence);
}

int main()
{
    int startValue  {200};
    int twoPound    {0};
    int onePound    {0};
    int fiftyPence  {0};
    int twentyPence {0};
    int tenPence    {0};
    int fivePence   {0};
    int twoPence    {0};
    int penny       {startValue};

    int counter {0};

    while(penny >= 0)
    {
        while(penny >= 0)
        {
            while(penny >= 0)
            {
                while(penny >= 0)
                {
                    while( penny >= 0)
                    {
                        while (penny >= 0)
                        {   
                            while(penny >= 0)
                            {
                                counter++;
                                twoPence++;
                                penny -= 2;
                            }
                            fivePence++;
                            twoPence = 0;
                            penny = pennyAmount(twoPound, onePound, fiftyPence, twentyPence, tenPence, fivePence, twoPence, startValue);
                        }
                        tenPence++;
                        fivePence = 0;
                        twoPence = 0;
                        penny = pennyAmount(twoPound, onePound, fiftyPence, twentyPence, tenPence, fivePence, twoPence, startValue);
                    }    
                    twentyPence++;
                    tenPence = 0;
                    fivePence = 0;
                    twoPence = 0;
                    penny = pennyAmount(twoPound, onePound, fiftyPence, twentyPence, tenPence, fivePence, twoPence, startValue);
                }
                fiftyPence++;
                twentyPence = 0;
                tenPence = 0;
                fivePence = 0;
                twoPence = 0;
                penny = pennyAmount(twoPound, onePound, fiftyPence, twentyPence, tenPence, fivePence, twoPence, startValue);
            }
            onePound++;
            fiftyPence = 0;
            twentyPence = 0;
            tenPence = 0;
            fivePence = 0;
            twoPence = 0;
            penny = pennyAmount(twoPound, onePound, fiftyPence, twentyPence, tenPence, fivePence, twoPence, startValue);
        }
        twoPound++;
        onePound = 0;
        fiftyPence = 0;
        twentyPence = 0;
        tenPence = 0;
        fivePence = 0;
        twoPence = 0;
        penny = pennyAmount(twoPound, onePound, fiftyPence, twentyPence, tenPence, fivePence, twoPence, startValue);
    }
    
    std::cout << counter << '\n';

}