#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <ostream>
#include <print>
#include <stdexcept>

//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_DISABLE
#include <doctest/doctest.h>

using Coord = std::pair<int, int>;

class Sudoku
{
    class Dig
    {
        int dig;

     public:
        Dig(int d) : dig{d}
        {
            if (d < 0 || d > 9) {
                throw std::invalid_argument(
                    "Dig constructor only accepts integers 0-9");
            }
        }

        Dig() : dig{0} {}

        Dig& operator=(int n)
        {
            if (0 > n || n > 9) {
                throw std::invalid_argument(
                    "A sudoku board can only contain digits 1-9 or be empty "
                    "(0)");
            }
            else {
                dig = n;
                return *this;
            }
        }

        operator int() const noexcept { return dig; }
    };


 public:
    static constexpr int board_sz{9};
    using Board = std::array<std::array<Dig, board_sz>, board_sz>;

    Sudoku() : m_board{} {}

    static Sudoku load(std::ifstream& input);

    explicit Sudoku(const Board& board) : m_board{board} {}

    Dig& operator[](std::size_t i, std::size_t j) { return m_board[i][j]; }

    const Dig& operator[](std::size_t i, std::size_t j) const
    {
        return m_board[i][j];
    }

    Dig* begin() { return m_board.front().begin(); }

    Dig* end() { return m_board.back().end(); }

    bool deduce();

    bool rec_solve();

    friend std::ostream& operator<<(std::ostream& out, Sudoku s);

    friend bool test_valid_in_line();
    friend bool test_valid_in_col();

 private:
    Board m_board;

    [[nodiscard]] bool valid_in_line(int line, Dig d) const;

    [[nodiscard]] bool valid_in_line(Coord c, Dig d) const
    {
        return valid_in_line(c.first, d);
    }

    [[nodiscard]] bool valid_in_col(int col, Dig d) const;

    [[nodiscard]] bool valid_in_col(Coord c, Dig d) const
    {
        return valid_in_col(c.second, d);
    }

    [[nodiscard]] bool valid_in_box(Coord c, Dig d) const;

    [[nodiscard]] bool can_place(Coord c, Dig d) const;
    [[nodiscard]] int deducable(Coord c) const;
};

Sudoku Sudoku::load(std::ifstream& input)
{
    std::string line;
    //Get rid of garbage "Grid XX"
    Sudoku s{};
    std::getline(input, line);
    for (int i{0}; i < board_sz; ++i) {
        std::getline(input, line);

        for (int j{0}; char c : line) {
            s.m_board[i][j] = c - '0';
            ++j;
        }
    }

    return s;
}

bool Sudoku::valid_in_line(int line_i, Dig d) const
{
    if (d == 0) {
        throw std::invalid_argument("An empty square should never be placed");
    }

    const auto& line{m_board[line_i]};

    return std::ranges::none_of(line, [d](Dig d2) { return d == d2; });
}

bool Sudoku::valid_in_col(int col_i, Dig d) const
{
    if (d == 0) {
        throw std::invalid_argument("An empty square should never be placed");
    }

    for (int i{0}; i < board_sz; ++i) {
        if (m_board[i][col_i] == d) { return false; }
    }

    return true;
}

bool Sudoku::valid_in_box(Coord c, Dig d) const
{
    if (d == 0) {
        throw std::invalid_argument("An empty square should never be placed");
    }

    auto [x, y] = c;
    Coord box{x - x % 3, y - y % 3};

    for (int i{0}; i < 3; ++i) {
        for (int j{0}; j < 3; ++j) {
            if (m_board[box.first + i][box.second + j] == d) { return false; }
        }
    }

    return true;
}

inline bool Sudoku::can_place(Coord c, Dig d) const
{
    return valid_in_line(c, d) && valid_in_col(c, d) && valid_in_box(c, d);
}

[[nodiscard]] int Sudoku::deducable(Coord c) const
{
    auto [y, x] = c;
    int found{0};
    for (int i{1}; i <= 9; ++i) {
        if (can_place(c, i)) {
            if (found != 0) { return 0; }
            else {
                found = i;
            }
        }
    }
    return (found == 0) ? -1 : found;
}

bool Sudoku::deduce()
{
    bool progress{false};

    for (int i{0}; i < board_sz; ++i) {
        for (int j{0}; j < board_sz; ++j) {
            if (m_board[i][j] != 0) { continue; }

            int is_deducable{deducable({i, j})};
            switch (is_deducable) {
                case -1:
                    throw std::runtime_error(std::format(
                        "Impossible to make progress ({}, {})", i, j));
                case 0 : continue;
                default: m_board[i][j] = is_deducable; progress = true;
            }
        }
    }

    return progress;
}

bool Sudoku::rec_solve()
{
    for (int i{0}; i < board_sz; ++i) {
        for (int j{0}; j < board_sz; ++j) {
            if (m_board[i][j] != 0) { continue; }

            for (int d{1}; d <= 9; ++d) {
                if (can_place({i, j}, d)) {
                    m_board[i][j] = d;
                    if (rec_solve()) { return true; }
                    else {
                        m_board[i][j] = 0;
                    }
                }
            }

            return false;
        }
    }

    return true;

    throw std::runtime_error("This should probably not happen, I'm too tired");
}

std::ostream& operator<<(std::ostream& out, Sudoku s)
{
    for (int j{0}; auto line : s.m_board) {
        for (int i{0}; int d : line) {
            out << d << ' ';

            ++i;
            if (i % 3 == 0) { out << "| "; }
        }
        ++j;
        constexpr int line_len{25};
        if (j % 3 == 0 && j < 9) { out << '\n' << std::string(line_len, '-'); }
        out << '\n';
    }

    return out;
}

int corner_score(const Sudoku& s)
{
    return 100 * s[0, 0] + 10 * s[0, 1] + s[0, 2];
}

TEST_CASE("Test constructor")
{
    Sudoku s{};
    for (int d : s) { CHECK_EQ(d, 0); }
}

TEST_CASE("Sudoku assignment")
{
    Sudoku s{};
    s[0, 5] = 5;
    CHECK_EQ(s[0, 5], 5);


    CHECK_THROWS_AS((s[0, 5] = 10), std::invalid_argument);
    CHECK_EQ((s[0, 3] = 0), 0);
    CHECK_EQ((s[0, 4] = 9), 9);
}

bool test_valid_in_line()
{
    Sudoku s{};
    for (int i{0}; i < 9; ++i) {
        for (int j{0}; j < 9; ++j) {
            for (int d{1}; d <= 9; ++d) {
                if (!s.valid_in_line({i, j}, d)) { return false; }
            }
        }
    }

    return true;
}

bool test_valid_in_col()
{
    Sudoku s{};
    for (int i{0}; i < 9; ++i) {
        for (int j{0}; j < 9; ++j) {
            for (int d{1}; d <= 9; ++d) {
                if (!s.valid_in_col({i, j}, d)) { return false; }
            }
        }
    }

    return true;
}

TEST_CASE("Valid_in_line")
{
    Sudoku s1{};
    CHECK(test_valid_in_line());
}

TEST_CASE("Valid_in_col")
{
    Sudoku s{};
    CHECK(test_valid_in_col());
}

TEST_CASE("Deduce")
{
    Sudoku s{};
    CHECK_FALSE(s.deduce());

    for (int i{1}; i < 9; ++i) { s[0, i] = i; }
    CHECK(s.deduce());
}

TEST_CASE("rec_solve")
{
    Sudoku s{};
    std::cout << s << '\n';
    CHECK(s.rec_solve());
    std::cout << s << '\n';
}

// TEST_CASE("Sudoku::load")
// {
//     std::ifstream input{"../sudoku.txt"};
//
//     Sudoku s{Sudoku::load(input)};
//
//     std::cout << s << '\n' << std::flush;
//
//     s = Sudoku::load(input);
//     std::cout << s << '\n';
//     input.close();
// }


int main()
{
    std::ifstream input{"../sudoku.txt"};

    Sudoku s{};
    int sum{0};
    for (int i{0}; i < 50; ++i) {
        s = Sudoku::load(input);

        // while (s.deduce()) {}

        s.rec_solve();

        sum += corner_score(s);
    }

    std::println("Result: {}", sum);

    return 0;
}
