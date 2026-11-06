#include <chrono>
#include <cstdio>

template <int K>
class Account {
    long long balance_ = 0;
    long long txn_[K] = {};
    int count_ = 0;
public:
    void deposit(long long a) {
        balance_ += a;
        if (count_ == K) { for (int i = 1; i < K; ++i) txn_[i - 1] = txn_[i]; --count_; }
        txn_[count_++] = a;
    }
    long long newest() const { return txn_[count_ - 1]; }
    long long oldest() const { return txn_[0]; }
    long long balance() const { return balance_; }
};

template <int K>
void run()
{
    constexpr int N = 5000000;
    Account<K> acc;
    auto t0 = std::chrono::steady_clock::now();
    for (int i = 1; i <= N; ++i) acc.deposit(i);
    auto t1 = std::chrono::steady_clock::now();
    std::printf("K=%2d  %8.2f ms  newest=%lld oldest=%lld balance=%lld sizeof=%zu\n", K,
                std::chrono::duration<double, std::milli>(t1 - t0).count(),
                acc.newest(), acc.oldest(), acc.balance(), sizeof(acc));
}

int main() { std::puts("ORIGINAL (shifting array)"); run<10>(); run<50>(); }
