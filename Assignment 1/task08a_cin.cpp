// Task 8a: read "zone hour" pairs with cin, recovering from letters. Run: ./task08a < input.txt
#include <iomanip>
#include <iostream>
#include <limits>

constexpr int BASE_PAISE[] = {1000, 2000, 3000};
constexpr bool isPeak(int h) { return (h >= 8 && h < 10) || (h >= 17 && h < 20); }

int main()
{
    long long balance = 20000;
    int zone = 0, hour = 0, line = 0;
    std::cout << "No. Zone Hour   Fare  Balance\n";
    while (true) {
        ++line;
        if (!(std::cin >> zone >> hour)) {
            if (std::cin.eof()) break;
            std::cin.clear();                                              // clear error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad line
            std::cout << std::setw(3) << line << "  invalid input skipped\n";
            continue;
        }
        if (zone < 0 || zone > 2 || hour < 0 || hour > 23) {
            std::cout << std::setw(3) << line << "  out-of-range values skipped\n";
            continue;
        }
        long long f = BASE_PAISE[zone];
        if (isPeak(hour)) f += f * 20 / 100;
        if (balance - f < 5000) { std::cout << std::setw(3) << line << "  denied (low balance)\n"; continue; }
        balance -= f;
        std::cout << std::setw(3) << line << std::setw(5) << zone << std::setw(5) << hour
                  << std::setw(6) << f / 100 << '.' << std::setfill('0') << std::setw(2) << f % 100
                  << std::setfill(' ') << std::setw(6) << balance / 100 << '.'
                  << std::setfill('0') << std::setw(2) << balance % 100 << std::setfill(' ') << '\n';
    }
    std::cout << std::fixed << std::setprecision(2) << "Final balance Rs " << balance / 100.0 << '\n';
}
