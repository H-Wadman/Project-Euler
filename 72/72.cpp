#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <numeric>
#include <print>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/multiprecision/gmp.hpp>

using boost::multiprecision::mpz_int;

constexpr std::size_t n_primes{79'000};

template <std::size_t s>
std::array<int, s> prime_sieve()
{
    std::array<int, s> primes{2, 3};
    std::size_t curr_size{2};

    for (int i{5}; curr_size < s; i += 1) {
        bool isPrime{true};
        for (int j{0}; j < curr_size && std::sqrt(i) >= primes[j]; ++j) {
            if (i % primes[j] == 0) {
                isPrime = false;
                break;
            }
        }

        if (isPrime) { primes[curr_size++] = i; }
    }

    return primes;
}

class Phi
{
    static constexpr std::size_t m_n_primes{79'000};
    static inline std::array<int, n_primes> m_primes{prime_sieve<m_n_primes>()};
    static inline bool first_instance{true};
    std::vector<std::pair<int, int>> m_reduced;

    static int divisible_by(int n)
    {
        const double root{std::sqrt(n)};
        for (int p : Phi::m_primes) {
            if (p > root) { break; }
            if (n % p == 0) { return p; }
        }

        return -1;
    }

    static std::pair<int, int> into_rel_prime_divs(int n)
    {
        int div{divisible_by(n)};

        if (div == -1) { return std::make_pair(n, 1); }

        int res{1};

        while (n % div == 0) {
            res *= div;
            n   /= div;
        }

        return std::make_pair(res, n);
    }

    static std::pair<int, int> into_rel_prime_divs(int n, int pr_factor)
    {
        int res{1};
        while (n % pr_factor == 0) {
            res *= pr_factor;
            n   /= pr_factor;
        }

        return std::make_pair(res, n);
    }

    [[nodiscard]] int phi(int n) const
    {
        int div{divisible_by(n)};

        if (div == -1) { return n - 1; }
        else {
            auto prime_divs{into_rel_prime_divs(n, div)};
            if (prime_divs.second == 1) {
                int count = 0;
                while (prime_divs.first != 1) {
                    prime_divs.first /= div;
                    ++count;
                }

                auto base{std::ranges::find_if(m_reduced,
                                               [div](std::pair<int, int> pair) {
                                                   return pair.first == div;
                                               })};

                if (base == m_reduced.end()) {
                    throw std::runtime_error(std::format(
                        "Base somehow not found in reduced at line {}",
                        __LINE__));
                }

                return static_cast<int>(pow(div, count - 1)) * base->second;
            }

            auto fst{std::ranges::find_if(
                m_reduced, [prime_divs](std::pair<int, int> pair) {
                    return pair.first == prime_divs.first;
                })};
            auto snd{std::ranges::find_if(
                m_reduced, [prime_divs](std::pair<int, int> pair) {
                    return pair.first == prime_divs.second;
                })};

            if (fst == m_reduced.end() || snd == m_reduced.end()) {
                std::cerr << std::format(
                    "Waddahell, fst == end? {}, snd == end? {}\n",
                    fst == m_reduced.end(), snd == m_reduced.end());
            }

            return fst->second * snd->second;
        }
    }

 public:
    int operator()(int n)
    {
        int res{phi(n)};
        m_reduced.emplace_back(n, res);
        return res;
    }

    const std::vector<std::pair<int, int>>& reduced() const
    {
        return m_reduced;
    }
};

mpz_int reduced_fracs_under(int lim)
{
    Phi phi{};

    for (int d{2}; d <= lim; ++d) { phi(d); }

    auto acc_vec{[](std::vector<std::pair<int, int>> vec) {
        return std::accumulate(
            vec.begin(), vec.end(), mpz_int{},
            [](const mpz_int& acc, const std::pair<int, int> pair) {
                return acc + pair.second;
            });
    }};

    return acc_vec(phi.reduced());
}

int main()
{
    constexpr int d{1'000'000};
    std::print("Number of reduced fractions with denominator <= {} is ", d);
    std::cout << reduced_fracs_under(d) << '\n';


    return 0;
}
