#include <iostream>
#include <vector>
#include <cstdlib>

long long max(long long a, long long b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

/**Reads a digit from the console as a character and returns it as an integer
 * does not handle incorect input
 * @return the value of the character -48 to obtain the digit the character represents
*/
int getDigit()
{
    char temp {};
    std::cin >> temp;
    return static_cast<int>(temp) - 48;
}

/**Finds the largest horizontal product in a vector
 * @param a rectangular table of type <vector<vector<int>>
 * @param limit an integer that determines how many elements in a row will be considered
 * @return the largest horizontal product of 'limit' factors
*/
std::int_least32_t largestHorizontalProduct(std::vector<std::vector<int>> t, int limit)
{
    std::int_least32_t maxProduct {t[0][0]};
    std::int_least32_t currentProduct {};
    

    for (int i {0}; i < t.size(); i++)
    {
        for (int j {0}; j <= t[0].size() - limit; j++)
        {
            currentProduct = 1;
            for (int k {0}; k < limit; k++)
            {
                currentProduct *= static_cast<long long>(t[i][j+k]);
            }
            if (currentProduct > maxProduct)
            {
                maxProduct = currentProduct;
            }
        }
    }

    return maxProduct;
}

/**Finds the largest vertical product in a vector
 * @param a rectangular table of type <vector<vector<int>>
 * @param limit an integer that determines how many elements in a column will be considered
 * @return the largest vertical product of 'limit' factors
*/
std::int_least32_t largestVerticalProduct(std::vector<std::vector<int>> t, int limit)
{
    std::int_least32_t maxProduct {t[0][0]};
    std::int_least32_t currentProduct {};
    

    for (int i {0}; i < t[0].size(); i++)
    {
        for (int j {0}; j <= t.size() - limit; j++)
        {
            currentProduct = 1;
            for (int k {0}; k < limit; k++)
            {
                currentProduct *= static_cast<long long>(t[j+k][i]);
            }
            if (currentProduct > maxProduct)
            {
                maxProduct = currentProduct;
            }
        }
    }

    return maxProduct;
}

/**Finds the largest diagonal product in a vector
 * @param a rectangular table of type <vector<vector<int>>
 * @param limit an integer that determines how many elements in a diagonal will be considered
 * @return the largest diagonal product of 'limit' factors
*/
std::int_least32_t largestDiagonalProduct(std::vector<std::vector<int>> t, int limit)
{
    std::int_least32_t maxProduct {t[0][0]};
    std::int_least32_t currentProduct {};
    

    for (int i {0}; i <= t.size() - limit; i++)
    {
        for (int j {0}; j <= t[0].size() - limit; j++)
        {
            currentProduct = 1;
            for (int k {0}; k < limit; k++)
            {
                currentProduct *= static_cast<long long>(t[i+k][j+k]);
            }
            if (currentProduct > maxProduct)
            {
                maxProduct = currentProduct;
            }
        }
    }

    for (int i {limit-1}; i < t.size(); i++)
    {
        for (int j {0}; j <= t[0].size() - limit; j++)
        {
            currentProduct = 1;
            for (int k {0}; k < limit; k++)
            {
                    currentProduct *= static_cast<long long>(t[i-k][j+k]);
            }
            if (currentProduct > maxProduct)
            {
                maxProduct = currentProduct;
            }
        }
    }



    return maxProduct;
}


int main()
{
    constexpr int gridLength    {20};
    constexpr int gridHeight    {20};
    constexpr int adjacentNumbers {4};

    std::vector<std::vector<int>> numberGrid;
    numberGrid = std::vector<std::vector<int>>(gridHeight);
    for (int i {0}; i < gridHeight; i++)
    {
        numberGrid[i] = std::vector<int>(gridLength);
    }


    
    for (int i {0}; i < gridHeight; i++)
    {
        for (int j {0}; j < gridLength; j++)
        {
            numberGrid[i][j] = getDigit() * 10 + getDigit();
        }
    }

    std::cout << "This is the largest horizontal product: " << largestHorizontalProduct(numberGrid, adjacentNumbers) << '\n';
    std::cout << "This is the largest vertical product: " << largestVerticalProduct(numberGrid, adjacentNumbers) << '\n';
    std::cout << "This is the largest diagonal product: " << largestDiagonalProduct(numberGrid, adjacentNumbers) << '\n';

    std::cout << "\nThis is the largest product of them all: " << max(largestHorizontalProduct(numberGrid, adjacentNumbers),max(largestDiagonalProduct(numberGrid, adjacentNumbers),largestVerticalProduct(numberGrid, adjacentNumbers))) << '\n';

    
    return 0;
}