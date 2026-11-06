#include <iomanip>
#include <iostream>

class SavingsAccount {
    static constexpr int HISTORY = 10;
    int accountNo_;
    long long balance_;
    long long txn_[HISTORY];
    int count_;

    void record(long long amount);
public:
    SavingsAccount(int no, long long opening) : accountNo_{no}, balance_{opening}, txn_{}, count_{0} {}
    long long balance() const { return balance_; }
    bool deposit(long long amount);
    bool withdraw(long long amount);
    void miniStatement() const;
};

void SavingsAccount::record(long long amount)
{
    if (count_ == HISTORY) {
        for (int i = 1; i < HISTORY; ++i) txn_[i - 1] = txn_[i];
        --count_;
    }
    txn_[count_++] = amount;
}
bool SavingsAccount::deposit(long long amount)
{
    if (amount <= 0) return false;
    balance_ += amount;
    record(amount);
    return true;
}
bool SavingsAccount::withdraw(long long amount)
{
    if (amount <= 0 || amount > balance_) return false;
    balance_ -= amount;
    record(-amount);
    return true;
}
void SavingsAccount::miniStatement() const
{
    std::cout << "Mini-statement for account " << accountNo_ << " (last " << count_ << ")\n";
    for (int i = count_ - 1; i >= 0; --i) {
        long long t = txn_[i];
        std::cout << std::setw(8) << (t >= 0 ? "Deposit" : "Withdraw") << std::setw(10) << (t >= 0 ? t : -t) << '\n';
    }
    std::cout << "Balance: " << balance_ << '\n';
}

int main()
{
    SavingsAccount acc{1001, 5000};
    for (int i = 1; i <= 12; ++i) {
        if (i % 3 == 0) acc.withdraw(100 * i); else acc.deposit(100 * i);
    }
    acc.miniStatement();
    std::cout << "withdraw too much: " << std::boolalpha << acc.withdraw(10000000) << '\n';

}
