#include <iostream>
#include <string>

void byValue(long long fee, int pct) { fee -= fee * pct / 100; }
void byReference(long long& fee, int pct) { fee -= fee * pct / 100; }
void byPointer(long long* fee, int pct) { if (fee) *fee -= *fee * pct / 100; }
long long returnsNew(long long fee, int pct) { return fee - fee * pct / 100; }

struct Student { std::string name; char notes[1000]; long long fee; };
long long readFee(const Student& s) { return s.fee; }
long long readFeeCopy(Student s) { return s.fee; }

int main()
{
    long long f = 45000;
    byValue(f, 10);      std::cout << "value     : " << f << '\n';
    byReference(f, 10);  std::cout << "reference : " << f << '\n';
    long long g = 45000;
    byPointer(&g, 10);   std::cout << "pointer   : " << g << '\n';
    byPointer(nullptr, 10);
    long long h = returnsNew(returnsNew(45000, 10), 15);
    std::cout << "returned, merit then sports: " << h << '\n';
    byReference(f, 15);  std::cout << "in place, sports after merit: " << f << '\n';

    Student s{"Asha", {}, 45000};
    std::cout << "sizeof(long long)=" << sizeof(long long) << ", sizeof(Student)=" << sizeof(Student)
              << ", sizeof(reference-passed Student) ~ pointer size " << sizeof(void*) << '\n';
    std::cout << readFee(s) << ' ' << readFeeCopy(s) << '\n';
}
