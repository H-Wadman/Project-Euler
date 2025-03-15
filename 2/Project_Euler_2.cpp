#include <iostream>


int sum(int aTemp, int bTemp)
{
    return aTemp + bTemp;
}

int main()
{
    int a = 1;
    int b = 1;
    int c = 0;

    int somme = 0;

    while ( a <= 4000000 )
    {
        c = a;
        a = sum(b, c);
        b = c;

        if ( (a % 2 == 0))
        {
            somme = somme + a;
            std::cout << "Somme: " << somme << std::endl;
            std::cout << "a: " << a << std::endl;
        }
        
    }

    return 0;

}



