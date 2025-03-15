#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>

/**Loads characters from a file with ASCII-codes separated by commmas
 * @param s – the path to the file
 * @return a vector containing all the characters of the file
*/
std::vector<char> loadData(std::string s)
{
    std::ifstream file {std::ifstream(s)};
    std::vector<char> data {};

    std::string temp {};
    while(getline(file, temp, ','))
    {
        data.push_back(static_cast<char>(std::stoi(temp)));
    }
    return data;
}

/**Searches a character vector for sequence of characters matching a string
 * @param v – a vector of characters to be searched
 * @param s – a string to search for
 * @return true if the string is found, false otherwise 
*/
bool hasWord(const std::vector<char>& v, const std::string& s)
{
    bool found {false};
    for (int i {0}; i + s.length() <= v.size(); ++i)
    {
        found = true;
        for (int j {0}; j < s.length(); ++j)
        {
            if(v[i+j] != s[j]) 
            {
                found = false;
                break;
            }
        }
        if (found) return true;
    }

    return false;
}

void test_hasWord()
{
    std::vector<char> v {'m', 'u', 'm', 's'};
    std::string s1 {"mum"};
    std::string s2 {"ums"};

    assert(hasWord(v, s1));
    assert(hasWord(v, s2));
    assert(!hasWord(v, "mus"));
}

void nextPassword(std::string& s)
{
    bool finished {true};
    for (auto a : s)
    {
        if (a != 'z') finished = false;
    }
    if(finished)
    {
        s = "aaa";
        return;
    }

    for(int i {0}; i < s.length(); ++i)
    {
        if(s[i] != 'z')
        {
            ++s[i];
            return;
        }
        s[i] = 'a';
    }
}

void decrypt(std::vector<char>& v, std::string password)
{
    for (int i {0}; i < v.size(); ++i)
    {
        v[i] = static_cast<char>(v[i]^password[i % password.size()]);
    }
}

void printCharacters(const std::vector<char>& v)
{
    for (char c : v)
    {
        std::cout << c;
    }
    std::cout << '\n';
}

bool hasCommonWords(const std::vector<char>& v)
{
    /*
    int count {static_cast<int>(hasWord(v, "to")) + static_cast<int>(hasWord(v, "the"))
                + static_cast<int>(hasWord(v, "be")) + static_cast<int>(hasWord(v, "and")) + static};

    return count > 3;
    */
   return (hasWord(v, "to") && hasWord(v, "the") && hasWord(v, "be") && hasWord(v, "of") && hasWord(v, "and") && hasWord(v, "that"));

}

int main()
{
    //test_hasWord();

    std::vector <char> data = loadData("/Users/hannes/Coding/HelloWorld/Project_Euler/Folder_Euler_59/p059_cipher.txt");
    

    auto decryptedData {data};
    std::string password {"zzz"};
    do
    {
        nextPassword(password);
        decryptedData = data;
        decrypt(decryptedData, password);
    }
    while(!(hasCommonWords(decryptedData)));
    
    printCharacters(decryptedData);
    std::cout << "Password: " << password << '\n';

    int sum {0};
    for (char c : decryptedData)
    {
        sum += static_cast<int>(c);
    }
    std::cout << "Sum: " << sum << '\n';

    return 0;
}