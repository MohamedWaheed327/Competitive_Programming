// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

namespace combinatorics {
    long long MOD = 1e9 + 7;

    int size = 0;
    vector<int> _fac = {1};
    vector<int> _invfac = {1};
    vector<int> _inv = {1};

    long long power(long long n, long long p) {
        n %= MOD;
        long long ret = 1;
        while (p) {
            if (p & 1) {
                ret = ret * n % MOD;
            }
            n = n * n % MOD;
            p >>= 1;
        }
        return ret;
    }

    void init(int N) {
        _fac.resize(N + 1);
        _invfac.resize(N + 1);
        _inv.resize(N + 1);

        for (long long i = size + 1; i <= N; i++) {
            _fac[i] = _fac[i - 1] * i % MOD;
        }

        _invfac[N] = power(_fac[N], MOD - 2);
        for (int i = N; i >= size + 1; i--) {
            _invfac[i - 1] = 1LL * _invfac[i] * i % MOD;
            _inv[i] = 1LL * _invfac[i] * _fac[i - 1] % MOD;
        }
        size = N;
    }

    long long fac(int n) {
        if (n > size) {
            init(2 * n);
        }
        return _fac[n];
    }

    long long invfac(int n) {
        if (n > size) {
            init(2 * n);
        }
        return _invfac[n];
    }

    long long inv(int n) {
        if (n > size) {
            init(2 * n);
        }
        return _inv[n];
    }

    long long npr(int n, int r) {
        if (n < r) {
            return 0;
        }
        return fac(n) * invfac(n - r) % MOD;
    }

    long long ncr(int n, int r) {
        return npr(n, r) * invfac(r) % MOD;
    }

    long long catalan(int n) {
        return ncr(2 * n, n) * inv(n + 1) % MOD;
    }

    long long stars_and_bars(int star, int bar) {
        return ncr(star + bar - 1, star);
    }
}
using namespace combinatorics;

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
