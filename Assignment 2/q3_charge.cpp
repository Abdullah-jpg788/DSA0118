#include <cmath>
#include <iostream>

constexpr long long PER_GRAM_PAISE = 4;
constexpr long long PER_KG_PAISE = 4000;
constexpr long long EXPRESS_PAISE = 3000;
constexpr long long INSURANCE_PAISE = 1500;

struct Parcel { int grams; bool express; bool insured; };

long long charge(int grams)
{
    std::cout << "[int grams] ";
    return grams * PER_GRAM_PAISE;
}
long long charge(double kg, bool express = false, bool insured = false)
{
    std::cout << "[double kg, express=" << express << ", insured=" << insured << "] ";
    long long c = std::llround(kg * PER_KG_PAISE);
    if (express) c += EXPRESS_PAISE;
    if (insured) c += INSURANCE_PAISE;
    return c;
}
long long charge(const Parcel& p)
{
    std::cout << "[Parcel] ";
    return p.grams * PER_GRAM_PAISE + (p.express ? EXPRESS_PAISE : 0) + (p.insured ? INSURANCE_PAISE : 0);
}

int main()
{
    std::cout << "charge(2)           -> " << charge(2) << '\n';
    std::cout << "charge(2.0f)        -> " << charge(2.0f) << '\n';
    std::cout << "charge(2.5)         -> " << charge(2.5) << '\n';
    std::cout << "charge(2.5,true)    -> " << charge(2.5, true) << '\n';
    std::cout << "charge(2.5,true,true)-> " << charge(2.5, true, true) << '\n';
    std::cout << "charge(Parcel)      -> " << charge(Parcel{2500, true, true}) << '\n';
}
