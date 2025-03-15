#include <iostream>
#include <vector>



int main()
{
    using std::vector;

    vector<char> digits {2};
    for (int i {1}; i <= 999; i++)
    {
        for (int j {0}; j < digits.size(); j++)
        {
            digits[j] *= 2;
        }
        for (int j {0}; j < digits.size() - 1; j++)
        {
            if (digits[j] > 9)
            {
                digits[j+1] += digits[j] / 10;
                digits[j] -= digits[j] / 10 * 10;
            }
        }
        if (digits[digits.size()-1] > 9)
        {
            digits.push_back(digits[digits.size()-1] / 10);
            digits[digits.size() - 2] -= digits[digits.size() - 1] * 10;
        }
        
    }

    int sum {0};
    for (int i {0}; i < digits.size(); i++)
    {
        sum += digits[i];
    }

    std::cout << sum;
    return 0;
}
