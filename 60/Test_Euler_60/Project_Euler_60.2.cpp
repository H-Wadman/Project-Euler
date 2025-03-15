#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <utility>
#include <algorithm>
#include <array>
#include <time.h>



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

struct Quintuplet
{
    int first   {};
    int second  {};
    int third   {};
    int fourth  {};
    int fifth   {};
};

using VecPairs = std::vector<std::pair<int, std::pair<int, int>>>;
using VecTriplets =  std::vector<std::pair<int, Triplet>>;
using VecQuad = std::vector<std::pair<int, Quadruplet>>;

bool operator==(Quadruplet q1, Quadruplet q2)
{
    return ((q1.first == q2.first) && (q1.second == q2.second) &&
    (q1.third == q2.third) && (q1.fourth == q2.fourth));
}

bool operator==(Triplet q1, Triplet q2)
{
    return ((q1.first == q2.first) && (q1.second == q2.second) &&
    (q1.third == q2.third));
}

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

bool isPrime(long long n, std::vector<int>& primeList)
{
    for (int a : primeList)
    {
        if (n % a == 0) return false;
        if (a * a > n) return true;
    }

    return true;
}

void addNextPrime(std::vector<int>& v)
{
    int p {v.back() + 2};
    while(!isPrime(p, v))
    {
        p += 2;
    }

    v.push_back(p);
}

int merge(int a, int b)
{
    int factor {10};
    while (factor < b)
    {
        factor *= 10;
    }

    return a * factor + b;
}

bool arePrimeMirrors(std::string s1, std::string s2)
{
    return (isPrime(std::stoi(s1 + s2)) && isPrime(std::stoi(s2 + s1)));
}

bool arePrimeMirrors(int a, int b)
{
    return (isPrime(merge(a, b)) && isPrime(merge(b, a)));
}

bool arePrimeMirrors(int a, int b, std::vector<int>& primeList)
{
    return (isPrime(merge(a, b), primeList) && isPrime(merge(b, a), primeList));
}

bool arePrimeMirrors(int a, std::pair<int, int> p, std::vector<int>& primeList)
{
    return (arePrimeMirrors(a, p.first, primeList) && arePrimeMirrors(a, p.second, primeList));
}

bool arePrimeMirrors(int a, Triplet t)
{
    return (arePrimeMirrors(a, t.first) && arePrimeMirrors(a, t.second) && arePrimeMirrors(a, t.third));
}

bool arePrimeMirrors(int a, Quadruplet t)
{
    return ((arePrimeMirrors(a, t.first)) && arePrimeMirrors(a, Triplet{t.second, t.third, t.fourth}));
}
/*
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
*/

void sortTriplet(std::pair<int, Triplet>& t)
{
    std::array<int, 3> temp {t.second.first, t.second.second, t.second.third};
    std::sort(temp.begin(), temp.end());
    t.second.first = temp[0];
    t.second.second = temp[1];
    t.second.third = temp[2];
}

bool tripletComparison(std::pair<int, Triplet>& triplet1, std::pair<int, Triplet>& triplet2)
{
    if (triplet1.first < triplet2.first) return true;
    else if (triplet1.first == triplet2.first)
    {
        if (triplet1.second.first != triplet2.second.first)
        {
            return (triplet1.second.first < triplet2.second.first);
        }
        else if (triplet1.second.second != triplet2.second.second)
        {
            return (triplet1.second.second < triplet2.second.second);
        }
        else if (triplet1.second.third != triplet2.second.third)
        {
            return (triplet1.second.third < triplet2.second.third);
        }
    }

    return false;
}

bool quadrupletComparison(std::pair<int, Quadruplet>& quadruplet1, std::pair<int, Quadruplet>& quadruplet2)
{
    if (quadruplet1.first < quadruplet2.first) return true;
    else if (quadruplet1.first == quadruplet2.first)
    {
        if (quadruplet1.second.first != quadruplet2.second.first)
        {
            return (quadruplet1.second.first < quadruplet2.second.first);
        }
        else if (quadruplet1.second.second != quadruplet2.second.second)
        {
            return (quadruplet1.second.second < quadruplet2.second.second);
        }
        else if (quadruplet1.second.third != quadruplet2.second.third)
        {
            return (quadruplet1.second.third < quadruplet2.second.third);
        }
        else if (quadruplet1.second.fourth != quadruplet2.second.fourth)
        {
            return (quadruplet1.second.fourth < quadruplet2.second.fourth);
        }
    }

    return false;
}

bool operator==(const std::pair<int, Triplet>& t1, const std::pair<int, Triplet>& t2)
{
    if(t1.first != t2.first) return false;
    
    return ((t1.second.first == t2.second.first) && (t1.second.second == t2.second.second) && (t1.second.third == t2.second.third));
}

bool areEqualTriplets(const std::pair<int, Triplet>& t1, const std::pair<int, Triplet>& t2)
{
    return (t1 == t2);
}

/*
void addLastPrimePair(const std::vector<int>& primeList, VecPairs& primePairs)
{
    for(int i {0}; i < primeList.size() - 1; ++i)
    {
        if(arePrimeMirrors(primeList.back(), primeList[i]))
        {
            primePairs.push_back(std::make_pair(primeList[i] + primeList.back(), std::make_pair(primeList[i], primeList.back())));
        }
    }

    //std::sort(primePairs.begin(), primePairs.end());
}
*/

void addLastPrimePair(const std::vector<int>& primeList, VecPairs& primePairs)
{
    
        if(arePrimeMirrors(primeList.back(), primeList[i]))
        {
            primePairs.push_back(std::make_pair(primeList[i] + primeList.back(), std::make_pair(primeList[i], primeList.back())));
        }

    //std::sort(primePairs.begin(), primePairs.end());
}

bool isInVector(std::pair<int, Triplet> p, VecTriplets v)
{
    for (auto a : v)
    {
        if ((a.first == p.first) && (a.second == p.second)) return true;
    }

    return false;
}

void addLastPrimeTriplet(std::vector<int>& primeList, const VecPairs& primePairs,
 VecTriplets& primeTriplets, int difference)
{
    for(int i {static_cast<int>(primePairs.size()) - difference}; i < primePairs.size(); ++i)
    {
        for(int j {0}; j < primeList.size(); ++j)
        {
            if(arePrimeMirrors(primeList[j], primePairs[i].second, primeList))
            {
                auto current {std::make_pair(primeList[j] + primePairs[i].first, 
                Triplet {primeList[j], primePairs[i].second.first, primePairs[i].second.second})};
                sortTriplet(current);
                if(!isInVector(current, primeTriplets))
                primeTriplets.push_back(current);
            }
        }
    }
    /*
    std::for_each(primeTriplets.begin(), primeTriplets.end(), sortTriplet);
    std::sort(primeTriplets.begin(), primeTriplets.end(), tripletComparison);
    return std::unique(primeTriplets.begin(), primeTriplets.end(), areEqualTriplets);
    */
}

void sortQuadruplet(Quadruplet& q)
{
    std::array<int, 4> arr{q.first, q.second, q.third, q.fourth};
    std::sort(arr.begin(), arr.end());
    q.first     = arr[0];
    q.second    = arr[1];
    q.third     = arr[2];
    q.fourth    = arr[3];
}

bool isInVector(std::pair<int, Quadruplet> p, VecQuad v)
{
    for (auto a : v)
    {
        if ((a.first == p.first) && (a.second == p.second)) return true;
    }

    return false;
}


void addLastPrimeQuadruplet(const std::vector<int>& primeList, 
const VecTriplets& primeTriplets, 
VecQuad& primeQuadruplets, int difference)
{
    for(int i {static_cast<int>(primeTriplets.size()) - difference}; i < primeTriplets.size(); ++i)
    {
        for(int j {0}; j < primeList.size(); ++j)
        {
            if(arePrimeMirrors(primeList[j], primeTriplets[i].second))
            {
                auto current {std::make_pair(primeList[j] + primeTriplets[i].first, 
                Quadruplet {primeList[j], primeTriplets[i].second.first, 
                primeTriplets[i].second.second, primeTriplets[i].second.third})};
                sortQuadruplet(current.second);
                if(!isInVector(current, primeQuadruplets))
                    primeQuadruplets.push_back(current);
            }
        }
    }

    std::sort(primeQuadruplets.begin(), primeQuadruplets.end(), quadrupletComparison);
}


void printPair(std::pair<int, std::pair<int, int>> p)
{
    std::cout << '<' << p.first << " | " << p.second.first << ", " << p.second.second << ">\n";
}

void printTriplet(std::pair<int, Triplet> t)
{
    std::cout << '<' << t.first << " | " << t.second.first << ", " << t.second.second << ", " << t.second.third << ">\n";
}

void printQuadruplet(std::pair<int, Quadruplet> t)
{
    std::cout << '<' << t.first << " | " << t.second.first << ", " << t.second.second 
    << ", " << t.second.third << ", " << t.second.fourth << ">\n";
}

void printQuintuplet(std::pair<int, Quintuplet> t)
{
    std::cout << '<' << t.first << " | " << t.second.first << ", " << t.second.second 
    << ", " << t.second.third << ", " << t.second.fourth << ", " << t.second.fifth << ">\n";
}



int main()
{


    std::vector<int>           primeList {2, 3};
    VecPairs                   primePairs          {};
    VecTriplets                primeTriplets       {};
    VecTriplets                primeTripletsTemp   {};
    VecQuad                    primeQuadruplets    {};

    std::pair<int, Quintuplet> bestCandidate {};

    

    //auto tripletEnd = addLastPrimeTriplet(primeList, primePairs, primeTriplets, 0);
    //auto quadrupletEnd = addLastPrimeQuadruplet(primeList, primeTriplets, primeQuadruplets, tripletEnd);
    //while(primeQuadruplets.size() < 12)
    while ((primeList.back() < bestCandidate.first) || (bestCandidate.first == 0))
    {   
        addNextPrime(primeList);


        int before {static_cast<int>(primePairs.size())};
        addLastPrimePair(primeList, primePairs);
        int difference {static_cast<int>(primePairs.size()) - before};
        //tripletEnd = addLastPrimeTriplet(primeList, primePairs, primeTriplets, difference);
        before = static_cast<int>(primeTriplets.size());
        addLastPrimeTriplet(primeList, primePairs, primeTriplets, difference);
        difference = static_cast<int>(primePairs.size()) - before;
        //quadrupletEnd = addLastPrimeQuadruplet(primeList, primeTriplets, primeQuadruplets, tripletEnd);

        addLastPrimeQuadruplet(primeList, primeTriplets, primeQuadruplets, difference);
        
        //std::cout << primeList.back() << '\n';
         for(std::pair<int, Quadruplet>& a : primeQuadruplets)
        {   
            
            //std::cerr << '(' << arePrimeMirrors(primeList.back(), a.second) << ',' << ((a.first < bestCandidate.first) || (bestCandidate.first == 0)) << ")\n";

            if(arePrimeMirrors(primeList.back(), a.second) && (((a.first + primeList.back()) < bestCandidate.first) || (bestCandidate.first == 0)))
            {
                std::cerr << "Has found one! :) \n";
                bestCandidate = std::make_pair(primeList.back() + a.first, 
                Quintuplet {primeList.back(), a.second.first, a.second.second, a.second.third, a.second.fourth});
            }
        }
        

        if(primeQuadruplets.size() > 0)
        {
            for(int a : primeList)
            {
            if(arePrimeMirrors(a, primeQuadruplets.back().second) && (((primeQuadruplets.back().first + a) < bestCandidate.first) || (bestCandidate.first == 0)))
            {
                std::cerr << "Has found one! :) \n";
                bestCandidate = std::make_pair(a + primeQuadruplets.back().first, 
                Quintuplet {a, primeQuadruplets.back().second.first, primeQuadruplets.back().second.second,
                primeQuadruplets.back().second.third, primeQuadruplets.back().second.fourth});
            }
            }
        }
        if(primeList.size() % 25 == 0) std::cout << primeList.back() << "(Size == " << primeList.size() << ")\n";
    }


    //! primePairs is only sorted at the end, otherwise the program breaks
    std::sort(primePairs.begin(), primePairs.end());
    std::for_each(primePairs.begin(), primePairs.end(), printPair);
    std::cout << "----------------------------\n";
    std::for_each(primeTriplets.begin(), primeTriplets.end(), printTriplet);
    std::cout << "----------------------------\n";
    std::for_each(primeQuadruplets.begin(), primeQuadruplets.end(), printQuadruplet);

    std::cout << "Result: ";
    printQuintuplet(bestCandidate);

    for(int i {0}; auto a : primeList)
    {
        std::cout << a << ' ';
        ++i;
        if(i % 25 == 0) std::cout << '\n';
    }
    std::cout << '\n';

    std::cout << bestCandidate.first << '\n';
    std::cout << "Result: ";
    printQuintuplet(bestCandidate);
    std::cout << "primeList.size() = " << primeList.size() << '\n';
    
    return 0;
}