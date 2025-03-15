#include <iostream>
#include <cstdint>
#include <array>
#include <bitset>
#include <cassert>
#include <algorithm>
#include <vector>

bool isHexagonal(int k)
{   
    int n {1};
    while(n * (2*n - 1) < k) ++n;

    return (k == n * (2*n - 1));
}

bool isTriangle(int k)
{
    if(isHexagonal(k)) return true;
    
    int n {2};
    while(n * (n+1) / 2 < k) n += 2;

    return (n * (n+1) / 2 == k);
}

void test_isTriangle()
{
    assert(isTriangle(1));
    assert(isTriangle(21));
    assert(isTriangle(28));
    assert(isTriangle(231));
}


bool isSquare(int k)
{
    int n {1};
    while(n * n < k) ++n;

    return (n * n == k);
}

void test_isSquare()
{
    assert(isSquare(16));
    assert(isSquare(36));
    assert(isSquare(144));
    assert(isSquare(9));
}

bool isPentagonal(int k)
{
    int n {1};
    while(n * (3*n - 1) / 2 < k) ++n;

    return (n * (3*n - 1) / 2 == k);
}

void test_isPentagonal()
{
    assert(isPentagonal(1));
    assert(isPentagonal(117));
    assert(isPentagonal(145));
    assert(isPentagonal(210));
}

bool isHeptagonal(int k)
{
    int n {1};

    while(n * (5*n - 3) / 2 < k) ++n;

    return (n * (5*n - 3) / 2 == k);
}

void test_isHeptagonal()
{
    assert(isHeptagonal(18));
    assert(isHeptagonal(55));
    assert(isHeptagonal(112));
    assert(isHeptagonal(235));
}

bool isOctagonal(int k)
{
    int n {1};
    while(n * (3*n - 2) < k) ++n;

    return (n * (3*n - 2) == k);
}

void test_isOctagonal()
{
    assert(isOctagonal(40));
    assert(isOctagonal(65));
    assert(isOctagonal(133));
    assert(isOctagonal(176));
}

char polygon(int k)
{
    if(isHexagonal(k))  return '6';
    if(isTriangle(k))   return '3';
    if(isSquare(k))     return '4';
    if(isPentagonal(k)) return '5';
    if(isHeptagonal(k)) return '7';
    if(isOctagonal(k))  return '8';

    return '0';
}

bool hasNoReps(std::vector<char>& v)
{
    int mask {0b0011'1111};

    for(int i {0}; i < 6; ++i)
    {   
        mask ^= (1 << (static_cast<int>(v[i]) - 51));
    }
    
    return mask == 0 || mask == 8;
}

bool isWellformedSet(const std::vector<int>& seg)
{
    std::vector<char> polygons (6);

    for(int i {0}; i < 5; ++i)
    {
        polygons[i] = polygon(seg[i] * 100 + seg[i+1]);
    }
    polygons[5] = polygon(seg[5] * 100 + seg[0]);


    return hasNoReps(polygons);
}

void test_isWellformedSet()
{
    std::array<int, 3> seg;
    seg[0] = 81;
    seg[1] = 28;
    seg[2] = 82;

    std::array<char, 3> polygons {};

    for(int i {0}; i < 2; ++i)
    {
        polygons[i] = polygon(seg[i] * 100 + seg[i+1]);
    }
    polygons[2] = polygon(seg[2]*100 + seg[0]);

    for(char c : polygons)
    {
        std::cout << c << ' ';
    }
    std::cout << '\n';
}


bool areEqual(std::vector<int>& v)
{   
    std::sort(v.begin(), v.end());
    auto a = std::unique(v.begin(), v.end());
    return a != v.end();
}

void test_areEqual()
{   
    std::vector<int> v {1, 2, 3, 4, 5, 6};
    assert(!areEqual(v));
    v[0] = 6;
    assert(areEqual(v));
}

//v.size() > 0
bool otherEqual(std::vector<int> v)
{
    for (int i {0}; i < v.size() - 1; ++i)
    {
        if(v[i] == v.back()) return true;
    }
    return false;
}

bool areIncompatible(int i, int j)
{
    return polygon(i*100 + j) == '0';
}

int main()
{
    //Tests
    {
        test_isTriangle();
        test_isSquare();
        test_isPentagonal();
        test_isHeptagonal();
        test_isOctagonal();
        test_areEqual();
        test_isWellformedSet();
    }
    
    int counter {0};
    for(int i {10}; i <= 99; ++i)
    {
        for(int j {10}; j <= 99; ++j)
        {
            if(areIncompatible(i, j))   continue;
            for (int k {10}; k <= 99; ++k)
            {
                if(areIncompatible(j, k))   continue;
                for (int l {10}; l <= 99; ++l)
                {
                    if(areIncompatible(k, l))   continue;
                    for(int m {10}; m <= 99; ++m)
                    {
                        if(areIncompatible(l, m))   continue;
                        for (int n {10}; n <= 99; ++n)
                        {
                            if(areIncompatible(m, n))   continue;
                            if(areIncompatible(n, i))   continue;
                            std::vector<int> current {i, j, k, l, m, n};
                            if(isWellformedSet(current))
                            {
                                std::cout << i << ' ' << j << ' ' << k << ' ' << l << ' ' << m << ' ' << n << '\n';
                                goto finished;

                            }
                        }
                    }
                }
            }
        }
    }

std::cout << "Went through all numbers\n" << counter << '\n';

finished:

    return 0;
}