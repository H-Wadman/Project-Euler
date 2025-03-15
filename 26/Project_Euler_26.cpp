#include <iostream>
#include <vector>

/**Kollar ifall en heltalsvektor innehåller ett visst värde
 * @param v en heltalsvektor
 * @param n ett heltal som söks
 * @return index för den första förekommelsen av n i v, -1 annars
*/
int hasValue (std::vector<int> v, int n)
{
    for (int i {0}; i < static_cast<int>(v.size()) - 1; i++)
    {
        if (v[i] == n) return i;
    }

    return -1;
}

/**Divides a number until finishes, or a recurring decimal cycle is found 
 * @param v 
 * 
*/
int divide (int p)
{
    using std::vector;

    vector<int> restLista {};
    int rest    {10};
    int kvot    {0};
    //använd do-while
    while ((hasValue(restLista, rest) == -1) && (rest != 0))
    {
        kvot = rest / p;
        rest -= kvot * p;
        rest *= 10;
        restLista.push_back(rest);
        
    }

    if (rest == 0) return 0;
    else 
    {
        return (restLista.size() - hasValue(restLista, rest) - 1);
    }
}

// a.size() > 0
int indexAvMax(std::vector<std::vector<int>> a, int k)
{
    int maxPost {a[0][k]};
    int maxIndex {0};
    for (int i {1}; i < a.size(); i++)
    {
        if (a[i][k] > maxPost)
        {
            maxPost = a[i][k];
            maxIndex = i;
        }
    }
    return maxIndex;
}


int main()
{
    std::vector<std::vector<int>> longDivision (0);

    for (int i {2}; i < 1000; i++)
    {
        longDivision.push_back({i, divide(i)});
    }


    std::cout << longDivision[indexAvMax(longDivision, 1)][0] << '\n';



    return 0;
}