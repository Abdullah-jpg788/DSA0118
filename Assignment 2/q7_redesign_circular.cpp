#include <chrono>
#include <cstdio>

template <int K>
class Account {
    long long balance_ = 0;
    long long txn_[K] = {};
    int start_ = 0;
    int count_ = 0;
public:
    void deposit(long long a) {
        balance_ += a;
        if (count_ < K) { txn_[(start_ + count_) % K] = a; ++count_; }
        else { txn_[start_] = a; start_ = (start_ + 1) % K; }
    }
    long long newest() const { return txn_[(start_ + count_ - 1) % K]; }
    long long oldest() const { return txn_[start_]; }
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

int main() { std::puts("REDESIGN (circular buffer)"); run<10>(); run<50>(); }
