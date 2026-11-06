// Task 10: double vs integer-paise totals, and int overflow, for 20,000 / 500,000 / 3,000,000 journeys.
#include <climits>
#include <cstdio>
#include <initializer_list>

int main()
{
    const int bases[] = {1000, 2000, 3000};          // paise
    for (long long n : {20000LL, 500000LL, 3000000LL}) {
        long long exact = 0;                          // integer paise
        double approx = 0.0;                          // rupees, computed with a fractional surcharge factor
        float approxF = 0.0f;
        unsigned wrapped = 0;                         // what an int accumulator would hold (wraps)
        for (long long i = 0; i < n; ++i) {
            int base = bases[i % 3];
            bool peak = (i % 5 == 0);
            long long f = peak ? base + base * 20 / 100 : base;
            exact += f;
            double rs = (base / 100.0) * (peak ? 1.2 : 1.0);
            approx += rs;
            approxF += static_cast<float>(rs);
            wrapped += static_cast<unsigned>(f);
        }
        std::printf("n=%8lld  exact paise=%12lld (Rs %lld.%02lld)\n", n, exact, exact / 100, exact % 100);
        std::printf("   double rupees=%.6f  diff from exact=%.3e Rs\n", approx, approx - exact / 100.0);
        std::printf("   float  rupees=%.2f  diff from exact=%.2f Rs\n", static_cast<double>(approxF),
                    static_cast<double>(approxF) - exact / 100.0);
        std::printf("   int accumulator (wrapped)=%d  %s\n", static_cast<int>(wrapped),
                    exact > INT_MAX ? "OVERFLOW" : "ok");
    }
}
