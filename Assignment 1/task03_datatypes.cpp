// Task 3: data types, sizeof, ranges, and double vs integer-paise money.
#include <climits>
#include <cstdio>
#include <iostream>

int main()
{
    std::cout << "bool " << sizeof(bool) << ", char " << sizeof(char) << ", int " << sizeof(int)
              << ", long long " << sizeof(long long) << ", unsigned " << sizeof(unsigned)
              << ", float " << sizeof(float) << ", double " << sizeof(double) << '\n';
    std::cout << "int range: " << INT_MIN << " to " << INT_MAX << '\n';
    std::cout << "long long range: " << LLONG_MIN << " to " << LLONG_MAX << '\n';

    // Is int enough for a day's collection? 3,000,000 journeys * up to Rs 36 (3600 paise)
    long long dayPaise = 3000000LL * 3600;
    std::cout << "worst-case day total (paise): " << dayPaise
              << (dayPaise > INT_MAX ? "  -> exceeds int\n" : "  -> fits int\n");

    // Precision problem: add Rs 0.10 one million times.
    double rupees = 0.0;
    long long paise = 0;
    for (int i = 0; i < 1000000; ++i) { rupees += 0.10; paise += 10; }
    std::printf("double total : %.10f\n", rupees);
    std::printf("paise total  : %lld.%02lld\n", paise / 100, paise % 100);
    std::printf("double error : %.10f\n", rupees - 100000.0);

    // Error growth with n
    for (int n : {1000, 100000, 1000000, 10000000}) {
        double d = 0;
        for (int i = 0; i < n; ++i) d += 0.10;
        std::printf("n=%8d  double=%.6f  exact=%.6f  error=%.3e\n", n, d, n * 0.10, d - n / 10.0);
    }

    // Overflow: wrapped arithmetic done via unsigned to avoid undefined behaviour
    unsigned wrapped = static_cast<unsigned>(INT_MAX) + 1u;
    std::cout << "INT_MAX + 1 wraps to " << static_cast<int>(wrapped) << " (two's complement)\n";
}
