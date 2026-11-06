#include <iostream>
#include <vector>

constexpr int N = 5;

int& highest(int (&marks)[N])
{
    int best = 0;
    for (int i = 1; i < N; ++i) if (marks[i] > marks[best]) best = i;
    return marks[best];
}
const int& highestConst(const int (&marks)[N])
{
    int best = 0;
    for (int i = 1; i < N; ++i) if (marks[i] > marks[best]) best = i;
    return marks[best];
}
int highestCopy(const int (&marks)[N]) { return highestConst(marks); }

int& dangling()
{
    int local = 42;
    return local;
}

int main()
{
    int marks[N] = {72, 91, 65, 88, 79};
    highest(marks) += 2;
    highest(marks) = highest(marks) + 0;
    std::cout << "after +2 moderation: ";
    for (int m : marks) std::cout << m << ' ';
    std::cout << '\n';

    const int& ro = highestConst(marks);
    int copy = highestCopy(marks);
    marks[1] = 50;
    std::cout << "const ref sees " << ro << " (element 1 is now 50); copy stays " << copy << '\n';

    std::vector<int> v{72, 91, 65};
    const int* before = v.data();
    int& first = v[0];
    (void)first;
    for (int i = 0; i < 100; ++i) v.push_back(i);
    std::cout << "vector storage moved after growth: " << std::boolalpha << (v.data() != before)
              << " -> 'first' now dangles (using it is undefined behaviour)\n";
    (void)&dangling;
}
