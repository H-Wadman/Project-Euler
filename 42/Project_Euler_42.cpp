#include <iostream>
#include <string>
#include <string_view>
#include <fstream>
#include <sstream>
#include <vector>

bool isTriangleNumber(int n)
{
    int i {1};
    while (i * (i + 1) / 2 < n)
    {
        ++i;
    }
    
    return (i * (i + 1) / 2 == n);
}

void test_isTriangleNumber()
{
    assert (isTriangleNumber(1));
    assert (!isTriangleNumber(2));
    assert (isTriangleNumber(3));
    assert (isTriangleNumber(55));
}

int stringValue(std::string_view s)
{
    int sum {0};
    for (int i {0}; i < s.size(); ++i)
    {
        sum += (static_cast<int>(s[i]) - 64); //Assumes only caracters [A-Z]
    }
    return sum;
}

void test_stringValue()
{
    assert (stringValue("AA") == 2);
    assert (stringValue("ABC") == 6);
    assert (stringValue("SKY") == 55);
}



int main()
{
    test_isTriangleNumber();
    test_stringValue();


    
    std::ifstream f("/Users/hannes/Coding/HelloWorld/Project_Euler/Folder_Euler_42/p042_words.txt");
    if (!f) std::cout << "File reading error\n";
    std::string interString {};
    f >> interString;

    std::stringstream longWord {interString};
    std::vector<std::string> wordList {};
    std::string temp;
    while(std::getline(longWord, temp, ','))
    {
        wordList.push_back(temp.substr(1, temp.size()-2));
    }
    wordList.pop_back();

    int wordsFound {0};
    for (auto v : wordList)
    {
        if(isTriangleNumber(stringValue(v))) ++wordsFound;
    }



    std::cout << wordsFound << '\n';

    return 0;
}