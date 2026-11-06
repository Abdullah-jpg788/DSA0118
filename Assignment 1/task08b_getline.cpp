// Task 8b: alternative - getline + stoi inside try/catch. Run: ./task08b < input.txt
#include <iostream>
#include <sstream>
#include <string>

int main()
{
    std::string line;
    int n = 0;
    while (std::getline(std::cin, line)) {
        ++n;
        std::istringstream in{line};
        std::string zs, hs;
        in >> zs >> hs;
        try {
            std::size_t pos1 = 0, pos2 = 0;
            int zone = std::stoi(zs, &pos1);
            int hour = std::stoi(hs, &pos2);
            if (pos1 != zs.size() || pos2 != hs.size()) throw std::invalid_argument("trailing characters");
            std::cout << "line " << n << ": zone " << zone << ", hour " << hour << '\n';
        } catch (const std::exception& e) {
            std::cout << "line " << n << ": bad input (" << e.what() << ")\n";
        }
    }
}
