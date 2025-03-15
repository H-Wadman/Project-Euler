#include <iostream>
#include <array>
#include <string>
#include <string_view>
#include <utility>
#include <fstream>

enum class Value {v2, v3, v4, v5, v6, v7, v8, v9, v10, Jack, Queen, King, Ace};
enum class Suit  {spades, diamonds, hearts, clubs};

struct Card
{
    Value value;
    Suit suit;
};

using Hand = std::array <Card, 5>;

void swap(Hand& h, int i, int j)
{
    Card temp {h[i]};
    h[i] = h[j];
    h[j] = temp;
}

void sortHand(Hand& h)
{
    bool isSorted {false};
    while (!isSorted)
    {
        isSorted = true;
        for (int i {0}; i < 4; ++i)
        {
            if (static_cast<int>(h[i].value) > static_cast<int>(h[i + 1].value))
            {
                isSorted = false;
                swap(h, i, i+1);
            }
        }
    }
}

std::string getValue(Card c)
{
    switch(c.value)
    {
        case Value::Ace:
            return "A";
        case Value::King:
            return "K";
        case Value::Queen:
            return "Q";
        case Value::Jack:
            return "J";
        default:
            std::string s {std::to_string(static_cast<int>(c.value) + 2)};
            return s;
        
    }
}

char getSuit(Card& c)
{
    switch(c.suit)
    {
        case Suit::clubs:
            return 'C';
        case Suit::diamonds:
            return 'D';
        case Suit::hearts:
            return 'H';
        case Suit::spades:
            return 'S';
    }
}

void printCard(Card& c)
{
    std::cout << getValue(c) << getSuit(c);
}

void printHand(Hand& h)
{
    for (Card c : h)
    {
        printCard(c);
        std::cout << '\n';
    }
    std::cout << "_________________\n";
}

std::pair<bool, int> isOnepair(Hand& h)
{
    for (int i {0}; i < 4; ++i)
    {
        for (int j {1}; i + j < 5; ++j)
        {
            if(h[i].value == h[i + j].value) return std::make_pair(true, static_cast<int>(h[i].value));
        }
    }
    return std::make_pair(false, -1);
}

std::pair<bool, int> isTwopair(Hand& h)
{
    std::pair<bool, int> pairOne {isOnepair(h)};
    if (!pairOne.first) return std::make_pair(false, -1);

    for (int i {0}; i < 4; ++i)
    {
        if(static_cast<int>(h[i].value) == pairOne.second) continue;
        for (int j {1}; i + j < 5; ++j)
        {
            if(h[i].value == h[j + i].value) return std::make_pair(true, static_cast<int>(h[i].value));
        }
    }
    return std::make_pair(false, -1);

}

std::pair<bool, int> isThreeOfAKind(Hand& h)
{
    int counter {0};

    for (int i {0}; i < 3; ++i)
    {
        counter = 0;
        for (int j {1}; i + j < 5; ++j)
        {
            if(h[i].value == h[i + j].value) ++counter;
        }
        if (counter >= 2) return std::make_pair(true, static_cast<int>(h[i].value));
    }
    return std::make_pair(false, -1);
}

std::pair<bool, int> isStraight(Hand& h)
{
    int startValue{static_cast<int>(h[0].value)};
    for (int i {1}; i < 5; ++i)
    {   
        if (static_cast<int>(h[i].value) != startValue + i)
        {
            return std::make_pair(false, -1);
        }
    }
    return std::make_pair(true, startValue);
}

std::pair<bool, int> isFlush(Hand& h)
{
    Suit s {h[0].suit};

    for (int i {1}; i < 5; ++i)
    {
        if (h[i].suit != s) return std::make_pair(false, -1);
    }
    
    return std::make_pair(true, static_cast<int>(h[4].value));
}

std::pair<bool, int> isFullHouse(Hand& h)
{
    std::pair<bool, int> three {isThreeOfAKind(h)};

    if (!three.first) return three;

    Value val {};
    for (int i {0}; i < 5; ++i)
    {
        if (three.second != static_cast<int>(h[i].value)) 
        {
            val = h[i].value;
            break;
        }
    }

    int counter {0};
    for (int i {0}; i < 5; ++i)
    {
        if(h[i].value == val) ++counter;
    }

    if (counter == 2) return std::make_pair(true, three.second);

    return std::make_pair(false, -1);
}

std::pair<bool,int> isFourOfAKind(Hand& h)
{
    Value v1 {h[0].value};
    int count1 {0};
    Value v2 {h[1].value};
    int count2 {0};

    for (int i {0}; i < 5; ++i)
    {
        if (v1 == h[i].value) ++count1;
        if (v2 == h[i].value) ++count2;
    }
    if (count1 == 4)
    {
        return std::make_pair(true, static_cast<int>(v1));
    }
    else if (count2 == 4)
    {
        return std::make_pair(true, static_cast<int>(v2));
    }

    return std::make_pair(false, -1);
}

std::pair<bool, int> isStraightFlush(Hand& h)
{
    int startValue{static_cast<int>(h[0].value)};
    for (int i {0}; i < 5; ++i)
    {   
        Suit s {h[0].suit};
        if (static_cast<int>(h[i].value) != startValue + i || h[i].suit != s)
        {
            return std::make_pair(false, -1);
        }
    }
    return std::make_pair(true, startValue);
}

std::pair<bool, int> isRoyalFlush(Hand& h)
{
    for (int i {0}; i < 5; ++i)
    {
        Suit s {h[0].suit};
        if (static_cast<int>(h[i].value) != 8 + i || h[i].suit != s)
        {
            return std::make_pair(false, -1);
        }
    }
    return std::make_pair(true, -1);
}

std::pair<int, int> getRank(Hand& h)
{
    sortHand(h);
    enum rank {highCard, onePair, twoPair, threeOfAKind, straight, flush, fullHouse, fourOfAKind, straightFlush, royalFlush};
    std::pair<bool,int> currentPair {};
    
    currentPair = isRoyalFlush(h);
    if(currentPair.first)   return std::make_pair(royalFlush, currentPair.second);

    currentPair = isStraightFlush(h);
    if (currentPair.first) return std::make_pair(straightFlush, currentPair.second);

    currentPair = isFourOfAKind(h);
    if(currentPair.first) return std::make_pair(fourOfAKind, currentPair.second);

    currentPair = isFullHouse(h);
    if(currentPair.first) return std::make_pair(fullHouse, currentPair.second);

    currentPair = isFlush(h);
    if(currentPair.first) return std::make_pair(flush, currentPair.second);

    currentPair = isStraight(h);
    if(currentPair.first) return std::make_pair(straight, currentPair.second);
    
    currentPair = isThreeOfAKind(h);
    if(currentPair.first) return std::make_pair(threeOfAKind, currentPair.second);

    currentPair = isTwopair(h);
    if(currentPair.first) return std::make_pair(twoPair, currentPair.second);

    currentPair = isOnepair(h);
    if(currentPair.first) return std::make_pair(onePair, currentPair.second);

    return std::make_pair(highCard, static_cast<int>(h[4].value));
}

Card makeCard(std::string s)
{
    Value value {};
    switch(s[0])
    {
        case '2':   
            value = Value::v2;
            break;
        case '3':
            value = Value::v3;
            break;
        case '4':
            value = Value::v4;
            break;
        case '5':
            value = Value::v5;
            break;
        case '6':
            value = Value::v6;
            break;
        case '7':
            value = Value::v7;
            break;
        case '8':
            value = Value::v8;
            break;
        case '9':
            value = Value::v9;
            break;
        case 'T':
            value = Value::v10;
            break;
        case 'J':
            value = Value::Jack;
            break;
        case 'Q':
            value = Value::Queen;
            break;
        case 'K':
            value = Value::King;
            break;
        case 'A':
            value = Value::Ace;
            break;
    }
    Suit suit {};
    switch(s[1])
    {
        case 'H':
            suit = Suit::hearts;
            break;
        case 'C':
            suit = Suit::clubs;
            break;
        case 'S':
            suit = Suit::spades;
            break;
        case 'D':
            suit = Suit::diamonds;
            break;
    }
    return {value, suit};
}

int main()
{
    
    std::ifstream file;
    file.open("/Users/hannes/Coding/HelloWorld/Project_Euler/Folder_Euler_54/p054_poker.txt");

    std::string input {};

    Hand h1 {};
    Hand h2 {};
    int scoreP1 {};
    int scoreP2 {};
    std::pair<int, int> rankP1 {};
    std::pair<int, int> rankP2 {};
    while(file >> input)
    {
        h1[0] = makeCard(input);

        for (int i {1}; i < 5; ++i)
        {
            file >> input;
            h1[i] = makeCard(input);
        }
        for (int i {0}; i < 5; ++i)
        {
            file >> input;
            h2[i] = makeCard(input);
        }

        rankP1 = getRank(h1);
        rankP2 = getRank(h2);

        if(rankP1.first > rankP2.first)         ++scoreP1;
        else if (rankP2.first > rankP1.first)   ++scoreP2;
        else
        {
            if(rankP1.second > rankP2.second)   ++scoreP1;
            else                                ++scoreP2;
        }

    }

    std::cout << scoreP1 << '\n';

    return  0;
}