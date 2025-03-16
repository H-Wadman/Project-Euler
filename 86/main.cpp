#include <array>
#include <cmath>
#include <limits>

#include <boost/math/special_functions.hpp>
#include <fmt/base.h>
#include <fmt/ranges.h>

//using Cube = std::array<int, 3>;

//int M{100};

namespace
{

class Cube
{
    std::array<double, 3> m_arr{1, 1, 1};
    bool done_flag{false};

 public:
    Cube() = default;

    Cube(double a, double b, double c) : m_arr{a, b, c} {}

    auto operator++() -> Cube&
    {
        if (m_arr[2] < m_arr[1]) { ++m_arr[2]; }
        else if (m_arr[1] < m_arr[0]) {
            ++m_arr[1];
            m_arr[2] = 1;
        }
        else {
            ++m_arr[0];
            //if (m_arr[0] > M) { done_flag = true; }
            m_arr[1] = 1;
            m_arr[2] = 1;
        }

        return *this;
    }

    auto advance() -> void
    {
        if (m_arr[2] == 1 || m_arr[1] == m_arr[0]) {
            ++m_arr[0];
            m_arr[1] = 1;
            m_arr[2] = 1;
        }
        else if (m_arr[2] != 1) {
            ++m_arr[1];
            m_arr[2] = 1;
        }
        else {
            done_flag = false;
        }
    }

    auto operator[](int i) -> double& { return m_arr[i]; }

    auto operator[](int i) const -> double const& { return m_arr[i]; }

    //operator bool() const { return !done_flag && m_arr[0] <= M * M * M; }

    [[nodiscard]] auto has_solution() const -> bool;

    [[nodiscard]] auto volume() const -> double
    {
        return m_arr[0] * m_arr[1] * m_arr[2];
    }

    [[nodiscard]] auto arr() const -> const std::array<double, 3>&
    {
        return m_arr;
    }
};

auto distance(const Cube& c, int start) -> double
{
    double sum{c[(start + 1) % 3] + c[(start + 2) % 3]};

    return std::sqrt(c[start] * c[start] + sum * sum);
}

auto is_close(double d1, double d2) -> bool
{
    double diff{d1 - d2};
    static constexpr double eps{std::numeric_limits<double>::epsilon()};

    return (-eps <= diff && diff <= eps);
}

auto is_integer(double d) -> bool { return is_close(d, std::floor(d)); }

[[nodiscard]] auto shortest_path(const Cube& c) -> double
{
    double shortest{std::numeric_limits<double>::max()};
    for (int i{0}; i < std::ssize(c.arr()); ++i) {
        double candidate{distance(c, i)};
        shortest = std::min(shortest, candidate);
    }

    return shortest;
}

[[nodiscard]] auto Cube::has_solution() const -> bool
{
    double shortest{shortest_path(*this)};

    //fmt::println("Shortest solution: {}", shortest);
    return is_integer(shortest);
}

auto solution(int lim) -> double
{
    int count{0};
    Cube c{};
    while (true) {
        // fmt::println("Status: {} -> {}; {}", c.arr(), c.volume(),
        //              c.volume() > lim);

        if (c.has_solution()) {
            // fmt::println("{}, had solution with shortest path {}", c.arr(),
            //              shortest_path(c));
            ++count;
            fmt::println("Current count: {}", count);
            if (count > lim) { return c[0]; }
        }

        ++c;
    }
}

} //namespace

auto main() -> int
{
    assert(is_integer(10));
    assert(distance(Cube{6, 5, 3}, 0) == 10);

    fmt::println("The solution is: {}", solution(1'000'000));
    //fmt::println("The solution is: {}", solution(2000));

    //fmt::println("For M = {}, the solution is {}", M, count);
}
