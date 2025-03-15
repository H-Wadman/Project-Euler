#include <iostream>
#include <vector>

template <typename T>
bool inList(T t, std::vector<T> v)
{
    for (int i {0}; i < v.size(); ++i)
    {
        if (v[i] == t) return true;
    }
    return false;
}

bool isPentagonal(int n)
{
    int i {1};
    int current {1};
    while (current < n)
    {
        ++i;
        current = i * (3*i - 1) / 2;
    }
    return current == n;
}

void test_isPentagonal()
{
    using std::cout;
    cout << isPentagonal(1) << '\n';
    cout << !isPentagonal(2) << '\n';
    cout << isPentagonal(5) << '\n';
    cout << !isPentagonal(45) << '\n';
    cout << isPentagonal(70) << '\n';
}

int main()
{
    //test_isPentagonal();

    std::vector<int> pentagonals {1};

    int maxPost {};
    while (true)
    {
        maxPost = pentagonals[pentagonals.size() - 1];
        for (int i {0}; i + 1 < pentagonals.size(); ++i)
        {
            if(inList<int>(maxPost - pentagonals[i], pentagonals) && isPentagonal(maxPost + pentagonals[i]))
            {
                std::cout << maxPost - pentagonals[i] << '\n';
                goto finished;
            }
        }
        pentagonals.push_back(maxPost + 3*pentagonals.size() + 1);
    }

finished:
    return 0;
}