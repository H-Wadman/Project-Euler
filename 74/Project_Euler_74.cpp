#include <string>
#include <iostream>

//naive

using ll = long long;

ll factorial(ll n)
{
    if (n < 0) throw std::invalid_argument("Fuck off");

    if (n == 0) return 1;
    else return n * factorial(n - 1);
}

ll digitFactorial(ll n)
{
    std::string str {std::to_string(n)};
    int res {0};
    for (char c : str)
    {
        res += factorial(c - 48);
    }

    return res;
}

template <typename T>
std::optional<int> inVec(const std::vector<T>& vec, T t)
{
    for (std::size_t i {0}; i < vec.size(); ++i)
        if (vec[i] == t) return std::make_optional(i);

    return std::nullopt;
}

int nFacChain(ll n)
{
    std::vector<ll> prev {};
    int counter {0};

    std::optional<int> found {std::nullopt}; 
    while (!found)
    {
        prev.push_back(n);
        n = digitFactorial(n);
        found = inVec(prev, n);
    }

    while (*found > 0 && prev[*found - 1] != n)
        --*found;

    return (prev.size() - *found);
}

int main()
{
    int counter {0};
    for (int i {1}; i < 1'000'000; ++i)
    {
        if (nFacChain(i) == 60) ++counter;
    }

    std::cout << "Counter: " << counter << '\n';

    return 0;
}