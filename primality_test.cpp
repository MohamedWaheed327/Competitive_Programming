// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

int64_t power(int64_t n, int64_t p, int64_t mod) {
    n %= mod;
    int64_t ret = 1;
    while (p) {
        if (p & 1) {
            ret = (__int128_t)ret * n % mod;
        }
        n = (__int128_t)n * n % mod;
        p >>= 1;
    }
    return ret;
}

int64_t rand(int64_t l, int64_t r) {
    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int64_t>(l, r)(rng);
}

bool is_prime(int64_t n) {
    if (n <= 1) return false;
    int itr = 10;
    while (itr--) {
        if (power(rand(1, n - 1), n - 1, n) != 1) {
            return false;
        }
    }
    return true;
}

void Main(...) {
    
}
/*









*/
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) {
        Main(i), cout << '\n';
    }
}
