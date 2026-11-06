#include <chrono>
#include <cstdio>

class Time {
    int h, m;
public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    int getH() const { return h; }
    int getM() const { return m; }
    int minutesTo(const Time& b) const { int d = (b.h * 60 + b.m) - (h * 60 + m); return d < 0 ? -d : d; }
    friend inline int minutesInline(const Time& a, const Time& b);
    friend int minutesNoInline(const Time& a, const Time& b);
};
inline int minutesInline(const Time& a, const Time& b)
{
    int d = (a.h * 60 + a.m) - (b.h * 60 + b.m);
    return d < 0 ? -d : d;
}
__attribute__((noinline)) int minutesNoInline(const Time& a, const Time& b)
{
    int d = (a.h * 60 + a.m) - (b.h * 60 + b.m);
    return d < 0 ? -d : d;
}
int viaGetters(const Time& a, const Time& b)
{
    int d = (a.getH() * 60 + a.getM()) - (b.getH() * 60 + b.getM());
    return d < 0 ? -d : d;
}

template <typename F>
double timeIt(const char* name, F f)
{
    constexpr int N = 10000000;
    long long sum = 0;
    auto t0 = std::chrono::steady_clock::now();
    for (int i = 0; i < N; ++i) {
        Time a(i % 24, i % 60), b((i + 5) % 24, (i * 7) % 60);
        sum += f(a, b);
    }
    auto t1 = std::chrono::steady_clock::now();
    double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
    std::printf("%-22s %8.2f ms  (checksum %lld)\n", name, ms, sum);
    return ms;
}

int main()
{
    timeIt("friend inline", [](const Time& a, const Time& b) { return minutesInline(a, b); });
    timeIt("friend noinline", [](const Time& a, const Time& b) { return minutesNoInline(a, b); });
    timeIt("member minutesTo", [](const Time& a, const Time& b) { return a.minutesTo(b); });
    timeIt("public getters", [](const Time& a, const Time& b) { return viaGetters(a, b); });
}
