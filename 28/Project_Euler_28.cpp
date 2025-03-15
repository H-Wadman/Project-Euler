#include <iostream>



int main()
{
    constexpr int size {1001};

    int sum {0};
    
    for (int currentSize {1}; currentSize < size; currentSize += 2)
    {
        sum += currentSize * currentSize * 2 + currentSize + 1;
    }
    sum += size * size;
    sum *= 2;
    --sum;

    std::cout << sum;

}