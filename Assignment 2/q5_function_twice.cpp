#include <iostream>
#include <string>

class BusTicket {
    static int issued;
    static const int CAPACITY = 3;
    int seat;
    std::string name;
public:
    explicit BusTicket(const std::string& n) : seat(0), name(n)
    {
        if (issued < CAPACITY) { ++issued; seat = issued; }
    }
    static int count() { return issued; }
    void print() const
    {
        std::cout << name << ": " << (seat ? "Seat " + std::to_string(seat) : std::string("Waiting")) << '\n';
    }
};
int BusTicket::issued = 0;

void book(const std::string& a, const std::string& b, const std::string& c)
{
    BusTicket t[3] = {BusTicket(a), BusTicket(b), BusTicket(c)};
    for (const BusTicket& x : t) x.print();
    std::cout << "Issued after this call: " << BusTicket::count() << '\n';
}

int main()
{
    book("Asha", "Bala", "Chitra");
    std::cout << "---\n";
    book("Dev", "Esha", "Farid");
}
