#include <iostream>
#include <utility>
#include <cassert>
#include <numeric>
#include <vector>
#include <cstdint>
#include <cmath>
#include <gmp.h>
#include <gmpxx.h>

class BigNum
{
    std::vector<uint64_t> m_num {};
    static const unsigned int MaxDigit {1'000'000'000};
    //static const unsigned int MaxDigit {10};

public:
    BigNum(std::vector<std::uint64_t> v) : m_num {v} {}

    BigNum(std::uint64_t x = 0)
    {
        while(x > 0)
        {
            this->m_num.push_back(x % MaxDigit);
            x /= MaxDigit;
        }
    }

    friend BigNum operator+(BigNum b1, const BigNum& b2);
    friend bool operator==(const BigNum& b1, const BigNum& b2);
    friend BigNum operator*(BigNum b1, unsigned int factor);
    friend BigNum operator*(const BigNum& b1, const BigNum& b2);
    friend bool operator<(const BigNum& b1, const BigNum& b2);
    friend std::ostream& operator<<(std::ostream& out, const BigNum& b);
};

bool operator<(const BigNum& b1, const BigNum& b2)
{
    if(b1.m_num.size() != b2.m_num.size())
        return b1.m_num.size() < b2.m_num.size();
    
    for(int i {static_cast<int>(b1.m_num.size()) - 1}; i >= 0; --i)
    {
        if(b1.m_num[i] < b2.m_num[i])
            return true;
        if(b1.m_num[i] > b2.m_num[i])
            return false;
    }

    return false;
}

std::ostream& operator<<(std::ostream& out, const BigNum& b)
{
    for(auto a : b.m_num)
    {
        out << a;
    }
    return out;
}

BigNum operator*(BigNum b1, unsigned int factor)
{
    if (factor == 0)
        return 0;
    if (factor == 1)
        return b1;
    if (factor == b1.MaxDigit)
    {
        b1.m_num.insert(b1.m_num.begin(), 0);
    }

    if (factor > b1.MaxDigit)
    {
        return b1 * BigNum{factor};
    }

    std::uint64_t carry {0};
    for(std::uint64_t& i : b1.m_num)
    {
        carry += i * static_cast<std::uint64_t>(factor);
        i      = carry % b1.MaxDigit;
        carry /= b1.MaxDigit;
    }

    while(carry > 0)
    {
        b1.m_num.push_back(carry % BigNum::MaxDigit);
        carry /= BigNum::MaxDigit;
    }

    return b1;
}

void test_factorMultiplication()
{
    auto b = (BigNum{456} * 4);
    auto b2 = BigNum{1824};
    assert((BigNum{456} * 4 == BigNum{1824}));

}

BigNum operator*(const BigNum& b1, const BigNum& b2)
{
    BigNum res {0};

    for(int i {static_cast<int>(b2.m_num.size()) - 1}; i >= 0; --i)
    {
        res = res * BigNum::MaxDigit + (b1 * b2.m_num[i]);
    }

    return res;
}

BigNum operator+(BigNum b1, const BigNum& b2)
{
    

    if (b1.m_num.size() < b2.m_num.size())
        b1.m_num.resize(b2.m_num.size(), 0);

    int carry {0};

    for(int i {0}; i < b2.m_num.size(); ++i)
    {
        b1.m_num[i] += b2.m_num[i] + carry;
        carry = b1.m_num[i] / BigNum::MaxDigit;
        b1.m_num[i] %= BigNum::MaxDigit;
    }
    for(std::size_t i {b2.m_num.size()}; i < b1.m_num.size() && carry != 0; ++i)
    {
        b1.m_num[i] += carry;
        carry = b1.m_num[i] / BigNum::MaxDigit;
        b1.m_num[i] %= BigNum::MaxDigit;
    }
    if(carry != 0)
    {
        b1.m_num.push_back(carry);
    }

    return b1;
}

bool operator==(const BigNum& b1, const BigNum& b2)
{
    if(b1.m_num.size() != b2.m_num.size()) return false;

    for(int i {0}; i < b1.m_num.size(); ++i)
    {
        if(b1.m_num[i] != b2.m_num[i]) return false;
    }

    return true;
}

void test_BigNumPlus()
{
    assert((BigNum{321} + BigNum {321} == BigNum{642}));
    assert((BigNum{555} + BigNum{555} == BigNum{1110}));
    assert((BigNum{999} + BigNum{1} == BigNum{1000}));
}

class Fraction;

using conF = std::pair<int, std::vector<int>>;

template <typename T>
void swap(T& a, T& b)
{
    T temp {a};
    a = b;
    b = temp;
}

Fraction operator+(Fraction f1, Fraction f2);

class Fraction
{
    BigNum m_num;  //Numerator of our fraction
    BigNum m_den;  //Denominator of our fraction

public:
    Fraction(BigNum num = 0, BigNum den = 1) : m_num {num}, m_den {den} {};

    BigNum getNum() { return m_num; }
    BigNum getDen() { return m_den; }

    /* int procede()
    {
        std::uint64_t res {m_den / m_num};
        m_den -= res * m_num;
        swap(m_num, m_den);

        return res;
    } */

    Fraction& operator+=(Fraction f)
    {
        *this = (*this + f);
        return *this;
    }

    Fraction inverse()
    {
        assert(m_num != 0);
        return Fraction {m_den, m_num};
    }

    template <typename T>
    Fraction& operator+=(T t)
    {   
        *this = *this + t;
        return *this;
    }
};

Fraction operator+(Fraction f1, Fraction f2)
{
    BigNum den {f1.getDen() * f2.getDen()};
    BigNum num {f1.getNum() * f2.getDen() + f2.getNum() * f1.getDen()};
    /* 
    int gcd {std::gcd(den, num)};

    return Fraction{num / gcd, den / gcd}; 
    */
   return Fraction{num, den};
}

Fraction operator+(Fraction f1, int n)
{
    return Fraction{f1.getNum() + f1.getDen() * n, f1.getDen()};
}

Fraction operator+(int n, Fraction f1) { return f1 + n; }

bool operator==(Fraction f1, Fraction f2)
{
    if(f1.getNum() == 0 && f2.getNum() == 0)    return true;

    return (f1.getNum() == f2.getNum()) && (f1.getDen() == f2.getDen());
}

std::ostream& operator<<(std::ostream& out, Fraction f)
{
    out << f.getNum() << '/' << f.getDen();
    return out;
}

Fraction operator*(Fraction f1, Fraction f2)
{
    return Fraction{f1.getNum() * f2.getNum(), f1.getDen() * f2.getDen()};
}

Fraction operator/(Fraction f1, Fraction f2)
{
    return f1 * f2.inverse();
}

void test_operators()
{
    Fraction f1 {3, 4};
    Fraction f2 {4, 5};

    assert((f1 * f2 == Fraction{12, 20}));
    assert((f1 / f2 == Fraction{15, 16}));
    

}

Fraction continuedFraction(conF f)
{
    assert(f.second.size() != 0);

    Fraction res {};

    for(std::size_t i {1}; i<= f.second.size(); ++i)
    {
        res += f.second[f.second.size() - i];
        res = res.inverse();

    }
    res += f.first;

    return res;
}

/* void test_procede()
{
    Fraction pair {Fraction{43, 93}};
    assert((pair.procede() == 2));
    assert((pair == Fraction{7, 43}));
    assert(pair.procede() == 6);
    assert((pair == Fraction{1, 7}));
    pair.procede();

    assert((pair == Fraction{0,1}));
} */

void test_continuedFraction()
{
    conF v {4, {2, 6, 7}};
    //std::cout << continuedFraction(v) << '\n';
    assert((continuedFraction(v) == Fraction{415, 93}));
}

//Not used
/* Fraction nextRegConF(Fraction f, int n)
{
    Fraction r {n-1};
    r = r / (f + 2);

    std::uint64_t gcd {std::gcd(r.getNum(), r.getDen())};

    return Fraction{r.getNum() / gcd, r.getDen() / gcd};
}

void test_nextRegConF()
{
    Fraction f {0};
    f = nextRegConF(f, 2);
    assert(((f + 1) == Fraction{3, 2}));
    f = nextRegConF(f, 2);
    assert(((f+1) == Fraction{7, 5}));
    f = nextRegConF(f, 2);
    assert(((f+1) == Fraction{17, 12}));
} */

struct radInt
{
    int m_root;
    int m_integer;


    radInt(int root=0, int integer=0) : m_root {root}, m_integer {integer} {}

    int conjugate()
    {
        return m_root - m_integer * m_integer;
    }
};

bool operator==(radInt r1, radInt r2)
{
    return r1.m_integer == r2.m_integer;
}


int nextConFStep(std::pair<int, radInt>& q)
{
    q.first = q.second.conjugate() / q.first;
    q.second.m_integer = -q.second.m_integer;

    int counter{0};
    int limit {static_cast<int>(sqrt(q.second.m_root))};
    while(limit + q.second.m_integer - q.first >= 0)
    {
        q.second.m_integer -= q.first;
        ++counter;
    }

    return counter;
}

bool hasRepeatingSequence(const std::pair<int, radInt>& q, const std::pair<int, radInt>& og)
{
    return q == og;
}

std::ostream& operator<<(std::ostream& out, conF c)
{
    std::cout << '[' << c.first << ";(";
    for(int i {0}; i + 1 < c.second.size(); ++i)
    {
        out << c.second[i] << ',';
    }
    out << c.second.back() << ")]";

    return out;
}

conF sqrtConF(int n)
{
    conF c {};
    c.first = static_cast<int>(sqrt(n));

    std::pair<int, radInt> q {1, {n, -c.first}};
    std::pair<int, radInt> og {q};


    do
    {
        c.second.push_back(nextConFStep(q));
    } while(!hasRepeatingSequence(q, og));

    return c;
}

bool inVector(std::vector<int> v, int n)
{
    for(int a : v)
    {
        if (a == n) return true;
    }
    
    return false;
}

Fraction repeatEval(const conF& c, int n)
{
    --n;

    Fraction f {};
    for(int i {n}; i >= 0; --i)
    {
        f += c.second[i % c.second.size()];
        f = f.inverse();
    }

    return f;
}

Fraction pellSolution(const conF& c, int d)
{   
    int counter {0};


    while(true)
    {
        Fraction res {repeatEval(c, counter) + c.first};
        if(res.getNum() * res.getNum() == BigNum{1} + d * res.getDen() * res.getDen()) //x^2 - D * y^2 = 1
            return res;
        

        ++counter;
    }
}


int main()
{
    //test_procede();
    test_continuedFraction();
    test_operators();
    //test_nextRegConF();
    test_BigNumPlus();
    test_factorMultiplication();

    std::uint64_t maxD {0};
    BigNum maxX {0};

    std::vector<int> squareList {};
    {
        int n = 2;
        while(n * n <= 1000)
        {
            squareList.push_back(n * n);
            ++n;
        }
    }

     for(int d {2}; d <= 1000; ++d)
    {
        if(inVector(squareList, d)) continue;

        conF root {sqrtConF(d)};
        Fraction res {pellSolution(root, d)};

        if(maxX < res.getNum())
        {
            maxX = res.getNum();
            maxD = d;
        }
    }

    std::cout << "maxX: " << maxX << '\n' << "maxD: " << maxD << '\n';

    /* int test {6};
    conF cTest {sqrtConF(test)};
    std::cout << cTest << '\n';
    std::cout << continuedFraction(cTest) << '\n';
    std::cout << repeatEval(cTest, 4) << '\n';
    std::cout << pellSolution(cTest, test) << '\n'; */

    return 0;
} 