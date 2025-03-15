#include <array>
#include <filesystem>
#include <fstream>
#include <limits>
#include <optdoc.hpp>
#include <print>

constexpr int dim{5};

namespace fs = std::filesystem;
using Matrix = std::array<std::array<int, dim>, dim>;

Matrix load_data(const fs::path& path)
{
    std::ifstream input{path};

    Matrix res{};
    std::string buf{};

    for (int i{0}; i < dim; ++i) {
        for (int j{0}; j < dim; ++j) {
            input >> res[i][j];
            input.ignore(1, '\n');
        }
    }

    return res;
}

TEST_CASE("load data")
{
    auto matrix{load_data("../matrix.txt")};

    CHECK_EQ(matrix[0][0], 4'445);
    CHECK_EQ(matrix[0][1], 2'697);
    CHECK_EQ(matrix[dim - 1][dim - 1], 7'981);
}

inline bool in_bounds(std::pair<int, int> coord)
{
    auto [x, y] = coord;
    return 0 <= x && x < dim && 0 <= y && y < dim;
}

int new_val(std::pair<int, int> coord, const Matrix& m)
{
    if (coord == std::pair<int, int>{0, 0}) { return 0; }
    using Coord = std::pair<int, int>;
    auto [y, x] = coord;

    Coord c1{y, x - 1};
    Coord c2{y - 1, x};


    int val1 = in_bounds(c1) ? m[c1.first][c1.second]
                             : std::numeric_limits<int>::max();
    int val2 = in_bounds(c2) ? m[c2.first][c2.second]
                             : std::numeric_limits<int>::max();
    return std::min(val1, val2);
}

void compute_diagonal(Matrix& m, int dia)
{
    if (dia <= dim - 1) {
        for (int i{0}; i <= dia; ++i) {
            m[dia - i][i] += new_val({dia - i, i}, m);
        }
    }
    else {
        int len{(dim - 1) * 2 - dia};
        for (int i{0}; i <= len; ++i) {
            std::pair<int, int> c{dim - 1, dia - (dim - 1) + i};
            m[c.first][c.second] += new_val(c, m);
        }
    }
}

TEST_CASE("compute_diagonal")
{
    Matrix m{load_data("../matrix.txt")};
    Matrix m2{m};
    compute_diagonal(m, 0);

    for (int i{0}; i < dim; ++i) {
        for (int j{0}; j < dim; ++j) { CHECK_EQ(m[i][j], m2[i][j]); }
    }

    compute_diagonal(m, 1);
    CHECK_EQ(m[1][0], 5'541);
    CHECK_EQ(m[0][1], 7'142);
    compute_diagonal(m, 2);
    CHECK_EQ(m[2][0], 15'148);
    CHECK_EQ(m[1][1], 5'561);
}

int solve(Matrix& m)
{
    for (int i{0}; i < 2 * dim - 1; ++i) { compute_diagonal(m, i); }
    return m[dim - 1][dim - 1];
}

#ifdef DOCTEST_CONFIG_DISABLE
int main()
{
    Matrix m{load_data("../matrix_test.txt")};
    std::println("Solution: {}", solve(m));

    return 0;
}

#endif
