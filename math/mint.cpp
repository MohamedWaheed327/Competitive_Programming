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
