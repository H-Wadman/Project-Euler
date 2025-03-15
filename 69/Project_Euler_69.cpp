#include <bit>
#include <iostream>
#include <utility>

class Timer
{
private:
	// Type aliases to make accessing nested type easier
	using Clock = std::chrono::steady_clock;
	using Second = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<Clock> m_beg { Clock::now() };

public:
	void reset()
	{
		m_beg = Clock::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
	}
};

int gcd(unsigned int u, unsigned int v)
{
    if (u == 0) return v;
    if (v == 0) return u;


    int shift {std::countr_zero(u | v)};
    
    u >>= std::countr_zero(u);
    v >>= std::countr_zero(v);

    while (true)
    {
        if (u > v) std::swap(u, v);
        v -= u;

        if (v == 0)
        {
            return u << shift;
        }

        v >>= std::countr_zero(v);
    }

}

void test_gcd()
{
    assert(gcd(2, 4) == 2);
    assert(gcd(1, 5) == 1);
    assert(gcd(36, 5) == gcd(5, 36));
    assert(gcd(6, 0) == 6);
    assert(gcd(17, 17) == 17);
}

int phi(unsigned int u)
{
    int counter {1};

    for (int i {2}; i < u; ++i)
    {
        if(gcd(u, i) == 1)
            ++counter;
    }

    return counter;
}

void test_phi()
{
    assert(phi(2u) == 1);
    assert(phi(3u) == 2);
    assert(phi(4u) == 2);
    assert(phi(5u) == 4);
    assert(phi(6u) == 2);
    assert(phi(7u) == 6);
    assert(phi(8u) == 4);
    assert(phi(9u) == 6);
    assert(phi(10u) == 4);
}

int main()
{
    test_gcd();
    test_phi();

    float max {0.0f};
    int n {0};

    Timer t;
    for(unsigned int u {10'000u}; u < 50'000u; u += 2)
    {
        float current {u / static_cast<float>(phi(u))}; 
        if (current > max)
        {
            max = current;
            n = u;
        }
    }
    std::cout << t.elapsed() << " seconds\n";

    std::cout << "Max ratio is " << max << " which is achieved for n = " << n << '\n';

    return 0;
}