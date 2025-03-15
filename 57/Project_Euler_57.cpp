#include <iostream>
#include "/Users/hannes/Coding/C++_libraries/bigint-main/Big Integer Library in Single file/bigint.h"
#include <utility>
struct Bråk
{
    bigint täljare {};
    bigint nämnare {};
};

Bråk operator+(Bråk b1, Bråk b2)
{
    bigint täljare {b1.täljare * b2.nämnare + b2.täljare * b1.nämnare};
    bigint nämnare {b1.nämnare * b2.nämnare};
    bigint gcd {big_gcd(täljare, nämnare)};
    return {täljare / gcd, nämnare / gcd};
}

void nästaIteration(Bråk& b)
{
    b.täljare += 2 * b.nämnare;
    std::swap(b.täljare, b.nämnare);
}

bool störreTäljare(Bråk b)
{
    return (big_log10(b.täljare) > big_log10(b.nämnare));
}

int main()
{
    Bråk b {1 , 2};
    Bråk ett {1, 1};
    int counter {0};
    for (int i {0}; i < 999; ++i)
    {
        if (störreTäljare(b + ett)) ++counter;
        nästaIteration(b);
    }

    std::cout << counter << '\n';

    return 0;
}