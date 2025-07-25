// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

template <const int mod = 998244353>
struct mint {
    int64_t value;

    mint(int64_t x = 0) {
        value = x % mod;
        if (value < 0) value += mod;
    }

    mint power(int64_t p) {
        mint ret = 1, base = value;
        while (p) {
            if (p & 1) ret *= base;
            base *= base;
            p /= 2;
        }
        return ret;
    }

    friend mint operator+(mint a, mint b) { return mint(a.value + b.value); }
    friend mint operator-(mint a, mint b) { return mint(a.value - b.value); }
    friend mint operator*(mint a, mint b) { return mint(a.value * b.value); }
    friend mint operator/(mint a, mint b) { return mint(a.value * b.power(mod - 2)); }
    friend bool operator==(mint a, mint b) { return a.value == b.value; }
    friend bool operator!=(mint a, mint b) { return a.value != b.value; }

    mint &operator+=(mint x) { return *this = *this + x; }
    mint &operator-=(mint x) { return *this = *this - x; }
    mint &operator*=(mint x) { return *this = *this * x; }
    mint &operator/=(mint x) { return *this = *this / x; }

    friend istream &operator>>(istream &in, mint &a) {
        in >> a.value, a = a.value;
        return in;
    }
    friend ostream &operator<<(ostream &out, mint a) { return out << a.value; }
};

using Z = mint<(int)1e9 + 7>;

namespace combinatorics {
    const int64_t MOD = 1e9 + 7;
    using Z = mint<MOD>;

    vector<Z> _fac = {1, 1};
    vector<Z> _inv = {1, 1};
    vector<Z> _facinv = {1, 1};

    void init(int N) {
        for (int i = _fac.size(); i <= N; i++) {
            _fac.push_back(_fac[i - 1] * i);
            _inv.push_back(MOD - MOD / i * _inv[MOD % i]);
            _facinv.push_back(_facinv[i - 1] * _inv[i]);
        }
    }

    Z fac(int n) {
        init(n);
        return _fac[n];
    }

    Z inv(int n) {
        init(n);
        return _inv[n];
    }

    Z facinv(int n) {
        init(n);
        return _facinv[n];
    }

    Z npr(int n, int r) {
        if (n < r) return 0;
        return fac(n) * facinv(n - r);
    }

    Z ncr(int n, int r) {
        return npr(n, r) * facinv(r);
    }

    Z catalan(int n, int k = 0) {
        return ncr(2 * n - k, n) * (k + 1) * inv(n + 1);
    }

    Z stars_and_bars(int star, int bar) { // **||**|*|||
        return ncr(star + bar, star);
    }

    Z permutation_with_repetition(const vector<int> &frq) {
        Z ret = fac(accumulate(frq.begin(), frq.end(), 0));
        for (auto it : frq) {
            ret *= facinv(it);
        }
        return ret;
    }

    Z count_necklaces(int beads, Z colors) { // for (divisors) total += phi(d) * pow(k, n / d)
        Z total = 0;
        for (int rot = 0; rot < beads; rot++) {
            total += colors.power(gcd(rot, beads));
        }
        return total / beads;
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
