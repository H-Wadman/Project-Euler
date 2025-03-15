#include <iostream>
#include <vector>

int SUM {1'000'000};

long factorial(int n)
{
    int temp {1};
    for (int i {1}; i <= n; i++)
    {
        temp *= i;
    }
    return temp;
}


/**Will print the lexicographic permutations of the digits in base 10 in order up to the millionth permutation
 * @return 0 if everything goes well :D
*/
int main()
{
    std::vector<int> permutations;
    permutations = std::vector<int>(10);


    for (int i {9}; i >= 0; i--)
    {
        std::cout << "Current i: " << i << "; SUM before: " << SUM << '\n' << "Index: " << SUM / factorial(i);

        permutations[9-i] = SUM / factorial(i);
        SUM -= SUM / factorial(i) * factorial(i);
        if ()

        std::cout << "; SUM after: " << SUM << "\n\n";
    }
    
    for (int j{0}; j < 10; j++)
    {
        std::cout << permutations[j] << ", ";
    }
    std::cout << '\n';
    

 return 0;   
}