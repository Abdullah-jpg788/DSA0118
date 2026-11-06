// Task 4: same program with every conversion made explicit (brace init + static_cast).
#include <iostream>
int main()
{
 int a{7}, b{2};
 double c{static_cast<double>(a / b)};     // still integer division, but now visibly intended
 double d{static_cast<double>(a) / b};
 std::cout << c << ' ' << d << '\n';
 char ch{static_cast<char>('A' + 2)};
 std::cout << ch << ' ' << static_cast<int>(ch) + 1 << '\n';
 bool flag{5 != 0};                        // bool flag{5}; would be a narrowing error
 std::cout << flag << ' ' << std::boolalpha << flag << '\n';
 unsigned int u{1};
 int s{-1};
 std::cout << (static_cast<long long>(s) < static_cast<long long>(u) ? "s < u" : "s >= u") << '\n';
 // int x{3.7};   // compile error: narrowing conversion
}
