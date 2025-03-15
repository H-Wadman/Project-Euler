#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


int max(int a, int b)
{
    return ((a > b) ? a : b);
}

void printVector(std::vector<std::vector<int>> t)
{
    for (int i {0}; i < t.size(); i++)
    {
        for (int j {0}; j < t[i].size(); j++)
        {
            std::cout << t[i][j] << " ";
        }
        std::cout << '\n';
    }
}

int main()
{ 
    std::string fileName {};
    std::cin >> fileName;
    std::ifstream count(fileName);
    int pSize {0};
    std::string line {};
    while(getline(count, line))
    {
        ++pSize;
    }
    count.close();

    std::vector<std::vector<int>> pyramid (pSize);
    for (int i {0}; i < pSize; i++)
    {
        pyramid[i] = std::vector<int> (i+1);
    }
    std::ifstream data(fileName);
    for (int i {0}; i < pyramid.size(); i++)
    {
        for (int j {0}; j < pyramid[i].size(); j++)
        {
            data >> pyramid[i][j];
        }
    }

    for (int i {pSize-2}; i >= 0; i--)
    {
        for (int j {0}; j < pyramid[i].size(); j++)
        {
            pyramid[i][j] += max(pyramid[i+1][j], pyramid[i+1][j+1]);
        }
    }

    std::cout << pyramid[0][0] << '\n';


    return 0;
}