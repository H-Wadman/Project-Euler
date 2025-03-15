#include "doctest_config.hpp"

#include <algorithm>
#include <charconv>
#include <doctest.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <stdexcept>

using namespace std::literals;
namespace fs = std::filesystem;

template <std::size_t N>
using Matrix = std::array<std::array<int, N>, N>;

template <std::size_t N>
Matrix<N> load_matrix(const fs::path& p)
{
    std::ifstream in{p};
    std::string buf{};

    Matrix<N> res{};
    int i{};
    while (in >> buf) {
        std::ranges::split_view test{std::ranges::views::split(buf, ","sv)};
        for (int j{}; auto s : test) {
            std::string_view deb{s};
            int val{};
            std::from_chars_result conv{
                std::from_chars(&*s.begin(), &*s.end(), val)};
            if (conv.ec != std::errc{}) {
                throw std::runtime_error{
                    "Error occured in from_chars in load_matrix"};
            }
            if (conv.ptr != &*s.end()) {
                throw std::runtime_error{
                    "Conversion succeeded but invalid character encountered"};
            }
            res[i][j++] = val;
        }
        ++i;
    }

    return res;
}

template <std::size_t N>
std::ostream& operator<<(std::ostream& out, const Matrix<N>& m)
{
    out << "{\n";
    for (const auto& a : m) {
        out << "\t{ ";
        for (int i : a) { out << i << ' '; }
        out << "}\n";
    }
    out << "}\n";
    return out;
}

//NOLINTBEGIN

TEST_CASE("load_matrix")
{
    fs::path source{SOURCE_PATH};
    Matrix<5> test{load_matrix<5>(source / "matrix" / "test.txt")}; //NOLINT

    REQUIRE_EQ(test.size(), 5UZ);
    REQUIRE_EQ(test[0].size(), 5UZ);

    CHECK(test[0][0] == 131);
    CHECK(test[0][1] == 673);
    CHECK(test[1][0] == 201);
    CHECK(test[4][4] == 331);
} //NOLINTEND

inline size_t next_ix(size_t j, size_t y)
{
    return (j < y) ? j + 1UZ : j - 1UZ;
}

template <std::size_t N>
Matrix<N> get_init_cost(const Matrix<N>& mat)
{
    Matrix<N> cost{};
    for (size_t i{0}; i < N; ++i) { cost[i][0] = mat[i][0]; }

    return cost;
}

//Each previous column needs to be calculated before calculating in a new column
//coord.second >= 1
//coordinates must be positive
template <std::size_t N>
int calculate_cost(const Matrix<N>& mat, std::pair<size_t, size_t> coord,
                   const Matrix<N>& costs)
{
    auto [y, x]{coord};
    int min{std::numeric_limits<int>::max()};
    for (size_t i{0}; i < N; ++i) {
        int temp{costs[i][coord.second - 1]};
        size_t j{i};
        while (true) {
            temp += mat[j][coord.second];
            if (j == y) { break; }
            j = next_ix(j, y);
        }

        if (temp < min) { min = temp; }
    }

    return min;
}

//NOLINTBEGIN
TEST_CASE("calculate_cost")
{
    fs::path source{SOURCE_PATH};
    Matrix<5> test{load_matrix<5>(source / "matrix/test.txt")};
    Matrix<5> cost{get_init_cost(test)};

    CHECK_EQ(calculate_cost(test, {0, 1}, cost), 804);
    cost[0][1] = 804;
    CHECK_EQ(calculate_cost(test, {1, 1}, cost), 297);
    cost[1][1] = 297;
    CHECK_EQ(calculate_cost(test, {2, 1}, cost), 1100);
    cost[2][1] = 1100;
    CHECK_EQ(calculate_cost(test, {3, 1}, cost), 1236);
    cost[3][1] = 1236;
    CHECK_EQ(calculate_cost(test, {4, 1}, cost), 1537);
    cost[4][1] = 1537;

    //std::cout << cost << '\n';
    //Col 2
    CHECK_EQ(calculate_cost(test, {1, 2}, cost), 639);
    cost[1][2] = 639;
} //NOLINTEND

template <size_t N>
void update_col(const Matrix<N>& mat, size_t col, Matrix<N>& costs)
{
    for (size_t i{0}; i < N; ++i) {
        costs[i][col] = calculate_cost(mat, {i, col}, costs);
    }
}

template <size_t N>
int solve_matrix(const Matrix<N>& mat, Matrix<N>& costs)
{
    for (size_t i{1}; i < N; ++i) { update_col(mat, i, costs); }

    int min{std::numeric_limits<int>::max()};
    for (size_t i{0}; i < N; ++i) {
        if (costs[i][N - 1] < min) { min = costs[i][N - 1]; }
    }

    return min;
}

//NOLINTBEGIN
TEST_CASE("solve_matrix")
{
    fs::path source{SOURCE_PATH};
    Matrix<5> test{load_matrix<5>(source / "matrix/test.txt")};
    Matrix<5> cost{get_init_cost(test)};

    CHECK_EQ(solve_matrix(test, cost), 994);

} //NOLINTEND

#ifdef DOCTEST_CONFIG_DISABLE

int main()
{
    try {
        fs::path source{SOURCE_PATH};
        //NOLINTNEXTLINE
        Matrix<80> mat{
            load_matrix<80>(source / "matrix/0082_matrix.txt")}; //NOLINT
        Matrix<80> costs{get_init_cost(mat)};                    //NOLINT

        std::cout << "Cost was: " << solve_matrix(mat, costs) << '\n';
    }
    catch (...) {
        std::cerr << "Exception was thrown in main\n";
        std::exit(1); //NOLINT
    }

    return 0;
}

#endif
