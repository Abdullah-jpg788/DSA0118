// Task 5: peak check expression and lookup-table alternative.
#include <iostream>

constexpr bool isPeak(int hour) { return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20); }

int main()
{
    bool peak[24] = {};
    for (int h = 0; h < 24; ++h) peak[h] = isPeak(h);

    bool allAgree = true;
    for (int h = 0; h < 24; ++h) {
        bool noParens = h >= 8 && h < 10 || h >= 17 && h < 20;   // same result: && binds tighter than ||
        if (noParens != isPeak(h) || peak[h] != isPeak(h)) allAgree = false;
    }
    std::cout << "hour check (10 and 20 must be off-peak): 10 -> " << peak[10]
              << ", 20 -> " << peak[20] << ", 8 -> " << peak[8] << ", 17 -> " << peak[17] << '\n';
    std::cout << "expression, no-parentheses form and table agree for all 24 hours: "
              << std::boolalpha << allAgree << '\n';

    int i = 5;
    // i = i++;  // undefined/unsequenced before C++17 style rules; never write this
    int j = i++;  // j gets 5, i becomes 6
    int k = ++i;  // i becomes 7, k gets 7
    std::cout << "post/pre increment: j=" << j << " k=" << k << " i=" << i << '\n';
}
