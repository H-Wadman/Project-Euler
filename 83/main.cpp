#include <array>
#include <boost/algorithm/string.hpp>
#include <boost/container/static_vector.hpp>
#include <charconv>
#include <cstddef>
#include <filesystem>
#include <fmt/base.h>
#include <fmt/ranges.h>
#include <fstream>
#include <limits>
#include <ranges>

namespace rg        = std::ranges;
namespace fs        = std::filesystem;
namespace container = boost::container;
using Coord         = std::pair<int, int>;

namespace
{

[[maybe_unused]] const std::string input_path{
    "/Users/hannes/Coding/Cpp/challenges/Project_Euler/83/input.txt"};
[[maybe_unused]] const std::string test_path{
    "/Users/hannes/Coding/Cpp/challenges/Project_Euler/83/test.txt"};

template <std::size_t N>
class Matrix
{
    std::array<std::array<int, N>, N> m_mat;

 public:
    auto operator[](std::size_t i) -> std::array<int, N>& { return m_mat[i]; }

    auto operator[](std::size_t i) const -> const std::array<int, N>&
    {
        return m_mat[i];
    }

    auto getArr() -> const std::array<std::array<int, N>, N>& { return m_mat; }
};

template <std::size_t N>
auto read_matrix(const fs::path& p) -> Matrix<N>
{
    Matrix<N> res{};
    std::ifstream fs{p};

    std::string buf{};
    int i = 0;
    while (std::getline(fs, buf)) {
        std::vector<std::string> split;
        boost::split(split, buf, boost::algorithm::is_any_of(","));
        assert(split.size() == N);

        auto convert{[](const std::string& s) -> int {
            int res{};
            auto [_, ec]{
                std::from_chars(s.data(), s.data() + s.size(), res)}; //NOLINT

            assert(ec == std::errc{});

            return res;
        }};
        rg::copy(split | rg::views::transform(convert), res[i].begin());

        ++i;
    }

    return res;
}

template <std::size_t N>
auto getDirs(Coord c) -> container::static_vector<Coord, 4>
{
    container::static_vector<Coord, 4> res{};

    static constexpr std::array<Coord, 4> steps{
        {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}
    };

    auto valid{[](Coord c) {
        return c.first >= 0 && c.second >= 0 && c.first < N && c.second < N;
    }};

    for (Coord s : steps) {
        Coord temp{c.first + s.first, c.second + s.second};
        if (valid(temp)) { res.push_back(temp); }
    }

    return res;
}

template <std::size_t N>
auto get_costs() -> Matrix<N>
{
    Matrix<N> cost{};

    for (std::size_t i{0}; i < N; ++i) {
        cost[i].fill(std::numeric_limits<int>::max());
    }

    return cost;
}

auto pop_min(auto& range, auto& proj = std::identity{}) -> auto
{
    auto min_cost = rg::min_element(range, proj);
    auto c{*min_cost};
    range.erase(min_cost);

    return c;
}

template <std::size_t N>
void update_tiles(const Matrix<N>& m, Coord c, Matrix<N>& costs,
                  std::vector<Coord>& yell)
{
    auto dirs{getDirs<N>(c)};

    for (Coord d : dirs) {
        auto candidate = costs[c.first][c.second] + m[d.first][d.second];
        auto& cost{costs[d.first][d.second]};

        //If we have a new shortest path to d
        if (candidate < cost) {
            //If d cost is +inf it has never been reached and we add it to
            //yell
            if (cost == std::numeric_limits<
                            std::remove_reference_t<decltype(cost)>>::max()) {
                yell.push_back(d);
            }

            costs[d.first][d.second] = candidate;
        }
    }
}

template <std::size_t N>
auto solve(const Matrix<N>& m) -> int
{
    Matrix<N> costs{get_costs<N>()};


    auto less_cost{[&costs](Coord c1, Coord c2) {
        return costs[c1.first][c1.second] < costs[c2.first][c2.second];
    }};


    costs[0][0] = m[0][0];
    std::vector<Coord> yell{{{0, 0}}};
    std::vector<Coord> red{};

    while (!yell.empty()) {
        //Pop coordinate with smallest current cost
        Coord c{pop_min(yell, less_cost)};
        red.push_back(c);


        //Update all adjacent tiles and add to yell if necessary
        update_tiles(m, c, costs, yell);
    }

    return costs.getArr().back().back();
}


} //namespace

auto main() -> int
{
    [[maybe_unused]] Matrix<80> input{read_matrix<80>(input_path)};
    [[maybe_unused]] Matrix<5> test{read_matrix<5>(test_path)};
    fmt::println("Solution: {}", solve(input));
    return 0;
}
