#include "hwutil.hpp"
#include <array>
#include <iostream>
#include <print>

int main()
{
    std::println("Hello, World!");

    constexpr std::size_t test_size{10'000};
    constexpr std::array<int, test_size> primes{prime_sieve<test_size>()};

    std::print("Here are the first {} primes: ", test_size);
    for (int p : primes) { std::println("{} ", p); }

    return 0;
}
