// Task 2: tokens, #define vs const vs constexpr, enum vs enum class.
#include <iostream>

#define OLD_PEAK_PERCENT 20                     // macro: no type, no scope
const int CONST_MIN_BALANCE = 5000;             // typed, scoped, may be runtime-initialised
constexpr int PEAK_SURCHARGE_PERCENT = 20;      // compile-time constant
constexpr int BASE_PAISE[] = {1000, 2000, 3000};
constexpr long long MIN_BALANCE_PAISE = 5000;

enum OldZone { OInner, OMiddle, OOuter };       // unscoped: leaks names, converts to int
enum class Zone { Inner, Middle, Outer };       // scoped, no implicit int conversion

constexpr long long baseFare(Zone z) { return BASE_PAISE[static_cast<int>(z)]; }

int main()
{
    // Tokens in this line: keyword (int), identifier (x), operator (=), constant (5), punctuator (;)
    int x = 5;
    std::cout << "x token demo: " << x << '\n';

    static_assert(baseFare(Zone::Outer) == 3000, "checked at compile time");
    constexpr long long peakOuter = baseFare(Zone::Outer) * (100 + PEAK_SURCHARGE_PERCENT) / 100;
    std::cout << "Outer peak fare (paise): " << peakOuter << '\n';

    int oldZoneAsInt = OOuter;                  // legal: unscoped enum converts silently
    std::cout << "unscoped enum as int: " << oldZoneAsInt << '\n';
    // int bad = Zone::Outer;                   // error: enum class does not convert
    std::cout << "enum class needs a cast: " << static_cast<int>(Zone::Outer) << '\n';

    std::cout << "macro value: " << OLD_PEAK_PERCENT << ", const: " << CONST_MIN_BALANCE
              << ", constexpr: " << MIN_BALANCE_PAISE << '\n';
    std::cout << "sizeof(Zone)=" << sizeof(Zone) << " sizeof(BASE_PAISE)=" << sizeof(BASE_PAISE) << '\n';
}
