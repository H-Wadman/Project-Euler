#include <algorithm>
#include <iostream>
#include <primesieve.hpp>
#include <set>
#include <vector>

using Prime = std::int64_t;

class Triplet
{
    using Num = int;
    //7071
    static constexpr int limit{9000};
    Num m_x;
    Num m_y;
    Num m_z;
    std::vector<Prime> primes;

 public:
    Triplet(Num x, Num y, Num z) : m_x{x}, m_y{y}, m_z{z} //NOLINT
    {
        primesieve::generate_primes(limit, &primes);
    }

    Triplet() : m_x{0}, m_y{0}, m_z{0}
    {
        primesieve::generate_primes(limit, &primes);
    }

    void increment()
    {
        if (m_x < (Num)primes.size()) { ++m_x; }
        else {
            m_x = 0;
            if (m_y < (Num)primes.size()) { ++m_y; }
            else {
                ++m_z;
            }
        }
    }

    [[nodiscard]] bool done() const { return m_z > limit; }

    Triplet& operator++()
    {
        increment();
        return *this;
    }

    [[nodiscard]] Prime x() const { return primes[m_x]; }

    [[nodiscard]] Prime x2() const { return x() * x(); }

    [[nodiscard]] Prime y() const { return primes[m_y]; }

    [[nodiscard]] Prime y3() const { return y() * y() * y(); }

    [[nodiscard]] Prime z() const { return primes[m_z]; }

    [[nodiscard]] Prime z4() const { return z() * z() * z() * z(); }

    [[nodiscard]] Prime val() const { return x2() + y3() + z4(); }

    void increment_y()
    {
        m_x = 0;
        ++m_y;
        if (m_y > limit) {
            m_y = 0;
            ++m_z;
        }
    }

    void increment_z()
    {
        m_x = 0;
        m_y = 0;
        ++m_z;
    }
};

static constexpr int max_limit{50'000'000};

bool check_increment(Triplet& t)
{
    if (t.val() > max_limit) {
        t.increment_y();
        if (t.val() > max_limit) { t.increment_z(); }

        return true;
    }

    return false;
}

bool contains(const std::vector<Prime>& res, Prime ele)
{
    return std::ranges::any_of(res, [ele](Prime p) { return p == ele; });
}

int main()
{
    Triplet t{};

    int count{0};
    std::set<Prime> res{};
    //res.reserve(1139628); //NOLINT
    while (!t.done()) {
        // std::cout << t.val() << "{ " << t.x() << ", " << t.y() << ", " <<
        // t.z()
        //           << "}\n";
        if (check_increment(t)) {
            if (t.val() > max_limit) { break; }
            continue;
        }

        if (!res.contains(t.val())) {
            ++count;
            res.insert(t.val());
        }

        t.increment();
    }

    std::cout << "Count: " << count << '\n';

    return 0;
}
