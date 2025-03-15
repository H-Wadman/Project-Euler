#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <utility>

struct Triplet
{
    int first   {};
    int second  {};
    int third   {};
};

struct Quadruplet
{
    int first   {};
    int second  {};
    int third   {};
    int fourth  {};
};

std::ostream& operator<<(std::ostream& os, const Quadruplet& q)
{
    os << q.first << ' ' << q.second << ' ' << q.third << ' ' << q.fourth << " \n";

    return os;
}

/*
template <typename T>
bool sortingAlgorithm(T& p1, T& p2)
{
    return (p1.first > p2.first);
}

bool sortingAlgorithm(const std::pair<int, std::pair<int, int>>& p1, const std::pair<int, std::pair<int, int>>& p2)
{
    return (p1.first > p2.first);
}
*/

bool isPrime(long long n)
{
    /*
    * Uncomment if you want to handle special cases
    if (n < 2) return false;
    if (n == 2) return true;
    */
    if (n % 2 == 0) return false;

    for (int i {3}; i <= static_cast<int>(sqrt(n)); ++i)
    {
        if(n % i == 0) return false;
    }

    return true;
}

void addNextPrime(std::vector<int>& v)
{   
    int p {v.back() + 2};
    while(!isPrime(p))
    {
        p += 2;
    }

    v.push_back(p);
}

bool arePrimeMirrors(std::string s1, std::string s2)
{
    return (isPrime(std::stoi(s1 + s2)) && isPrime(std::stoi(s2 + s1)));
}

bool arePrimeMirrors(int a, int b)
{
    std::string s1 {std::to_string(a)};
    std::string s2 {std::to_string(b)};
    return (isPrime(std::stoll(s1 + s2)) && isPrime(std::stoll(s2 + s1)));
}

bool arePrimeMirrors(int a, std::pair<int, int> p)
{
    return (arePrimeMirrors(a, p.first) && arePrimeMirrors(a, p.second));
}

bool arePrimeMirrors(int a, Triplet t)
{
    return (arePrimeMirrors(a, t.first) && arePrimeMirrors(a, t.second) && arePrimeMirrors(a, t.third));
}

bool arePrimeMirrors(int a, Quadruplet q)
{
    return (arePrimeMirrors(a, q.first) && arePrimeMirrors(a, q.second) && 
    arePrimeMirrors(a, q.third) && arePrimeMirrors(a, q.fourth));
}

void addLastPrimePair(const std::vector<int>& primeList, std::vector<std::pair<int, std::pair<int, int>>>& primePairs)
{
    for(int i {0}; i < primeList.size() - 1; ++i)
    {
        if(arePrimeMirrors(primeList.back(), primeList[i]))
        {
            primePairs.push_back(std::make_pair(primeList[i] + primeList.back(), std::make_pair(primeList[i], primeList.back())));
        }
    }

    std::sort(primePairs.begin(), primePairs.end());
}

bool tripletComparison(std::pair<int, Triplet>& triplet1, std::pair<int, Triplet>& triplet2)
{
    return triplet1.first > triplet2.first;
}

bool quadrupletComparison(std::pair<int, Quadruplet>& q1, std::pair<int, Quadruplet> q2)
{
    return q1.first > q2.first;
}

void addLastPrimeTriplet(const std::vector<int>& primeList, const std::vector<std::pair<int, std::pair<int, int>>>& primePairs,
 std::vector<std::pair<int, Triplet>>& primeTriplets, int difference)
{
    std::vector<int> sums {};
    for(int i {static_cast<int>(primePairs.size()) - difference}; i < primePairs.size(); ++i)
    {
        for(int j {0}; j < primeList.size(); ++j)
        {
            if(arePrimeMirrors(primeList[j], primePairs[i].second))
            {
                primeTriplets.push_back(std::make_pair(primeList[j] + primePairs[i].first, 
                Triplet {primeList[j], primePairs[i].second.first, primePairs[i].second.second}));
            }
        }
    }
    std::sort(primeTriplets.begin(), primeTriplets.end(), tripletComparison);
}

void addLastPrimeQuadruplets(const std::vector<int>& primeList, 
const std::vector<std::pair<int, Triplet>>& primeTriplets, 
std::vector<std::pair<int, Quadruplet>>& primeQuadruplets, int difference)
{
    for(int i {static_cast<int>(primeTriplets.size()) - difference}; i < primeTriplets.size(); ++i)
    {
        for(int j {0}; j < primeList.size(); ++j)
        {
            if(arePrimeMirrors(primeList[j], primeTriplets[i].second))
            {
                primeQuadruplets.push_back(std::make_pair(primeList[j] + primeTriplets[i].first, 
                Quadruplet {primeList[j], primeTriplets[i].second.first, 
                primeTriplets[i].second.second, primeTriplets[i].second.third}));
            }
        }
    }
    std::sort(primeQuadruplets.begin(), primeQuadruplets.end(), quadrupletComparison);
}

bool hasFiveCombinations(int a, Quadruplet q)
{
    std::vector<std::string> mirrors{std::to_string(a), std::to_string(q.first), 
    std::to_string(q.second), std::to_string(q.third), std::to_string(q.fourth)};

    for (int i {0}; i < mirrors.size(); ++i)
    {
        for(int j {i+1}; j < mirrors.size(); ++j)
        {
            if(!arePrimeMirrors(mirrors[i], mirrors[j])) return false;
        }
    }
    return true;
}

int main()
{

    std::vector<int>                    primeList {2, 3};
    std::vector<std::pair<int, std::pair<int, int>>>    primePairs                  {};
    std::vector<std::pair<int, Triplet>>                primeTriplets               {};
    std::vector<std::pair<int, Quadruplet>>             primeQuadruplets            {};

    bool found {false};
    while(!found)
    {
        addNextPrime(primeList);

        int before {static_cast<int>(primePairs.size())};
        addLastPrimePair(primeList, primePairs);
        int difference {static_cast<int>(primePairs.size()) - before};

        before = static_cast<int>(primeTriplets.size());
        addLastPrimeTriplet(primeList, primePairs, primeTriplets, difference);
        difference = static_cast<int>(primeTriplets.size()) - before;

        before = static_cast<int>(primeQuadruplets.size());
        addLastPrimeQuadruplets(primeList, primeTriplets, primeQuadruplets, difference);
        difference = static_cast<int>(primeQuadruplets.size()) - before;

        for(int i {static_cast<int>(primeQuadruplets.size()) - difference}; i < primeQuadruplets.size(); ++i)
        {
            for(std::size_t j {0}; j < primeList.size(); ++j)
            {
                if(hasFiveCombinations(primeList[j], primeQuadruplets[i].second))
                {
                    found = true;
                    std::cout << primeList[j] << ' ' << primeQuadruplets[i].second;

                }
            }
        }
    }

    return 0;
}