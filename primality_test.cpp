// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

long long mulmod(long long a, long long b, long long m) {
    long long res = 0;
    while (b > 0) {
        if (b & 1)
            res = ((m - res) > a) ? res + a : res - m + a;
        b >>= 1;
        a = ((m - a) > a) ? a + a : a - m + a;
    }
    return res;
}

long long power(long long n, long long p, long long mod) {
    n %= mod;
    long long ret = 1;
    while (p) {
        if (p & 1) {
            ret = mulmod(ret, n, mod);
        }
        n = mulmod(n, n, mod);
        p >>= 1;
    }
    return ret;
}

long long rand(long long l, long long r) {
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    return rng() % (r - l + 1) + l;
}

bool prime(long long n) {
    if (n <= 1)
        return false;
    for (int i = 1; i <= 10; i++) {
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
