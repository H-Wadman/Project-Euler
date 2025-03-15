#include <iostream>
#include <string>
#include <sstream>
#include <typeinfo>
#include <cmath>
#include <vector>
#include <iomanip>

/**Återsänd en decimal i följden 0.12345678910... etc. (de positiva heltalen i följd)
 * @param n ett positivt heltal, den n:e decimalen i följden att återsända
 * @return den n:e decimalen i följden
**/
double champerConstant(int n)
{
    std::string följd {};

    int count {1};
    while (följd.length() < n)
    {
        följd += std::to_string(count);
        ++count;
    }

    return static_cast<int>(följd[n-1]) - 48;
}

int main()
{
    std::vector<double> d (6);
    for (int i {0}; i < d.size(); i++)
    {
        d[i] = champerConstant(pow(10, static_cast<double>(i)));
    }
    
    std::cout << std::setprecision(2'000'000'000);
    double resultat {1.0};
    for (int i {0}; i < d.size(); i++)
    {
        resultat *= d[i];
    }

    std::cout << "Resultat: " << resultat << '\n';



    return 0;
}