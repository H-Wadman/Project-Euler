#include <iostream>
#include <vector>
#include <cmath>

/**Returnerar siffrorna i ett heltal
 * @param n - ett heltal
 * @return en heltalsvektor innehållande siffrorna i n
**/
std::vector<int> siffror(int n)
{
    std::vector<int> sifferVektor {};
    int storlek {static_cast<int>(log10(n))};

    for (int i {storlek}; i >= 0; --i)
    {
        sifferVektor.push_back(n / static_cast<int>(pow(10, i)));
        n -= sifferVektor[sifferVektor.size() - 1] * static_cast<int>(pow(10, i));
    }
    
    return sifferVektor;
}

/**Sorterar en vektor i stigande ordning
 * @param v - en vektor som ska sorteras
*/
void sorteraVektor(std::vector<int>& v)
{
    int temp {};
    for (int i {0}; i < v.size() - 1; ++i)
    {
        for (int j {0}; j < v.size() - 1; ++j)
        {
            if (v[j] > v[j+1])
            {
                temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }
}

bool ärLika (const std::vector<int>& v1, const std::vector<int>& v2)
{
    if (v1.size() != v2.size()) return false;

    for (int i {0}; i < v1.size(); ++i)
    {
        if (v1[i] != v2[i]) return false;
    }
    return true;
}


int main()
{
    int testNummer {1};
    while (true)
    {
        std::vector<int> testVektor {siffror(testNummer)};
        sorteraVektor(testVektor);

        for (int i {2}; i <= 6; ++i)
        {
            std::vector<int> multipel {siffror(testNummer * i)};
            sorteraVektor(multipel);
            if (!ärLika(testVektor, multipel)) goto nästaNummer;
        }
        std::cout << testNummer << '\n';
        break;
    nästaNummer:
        ++testNummer;
    }

    return 0;
}