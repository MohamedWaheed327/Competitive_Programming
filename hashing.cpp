// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

class dr_string {
private:
    static const long long mod = (1LL << 61) - 1;
    static long long base;
    vector<long long> pow{1}, hash{0};

    long long sub(long long a, long long b) {
        a -= b;
        if (a < 0)
            a += mod;
        return a;
    }

public:
    dr_string(const auto &a) {
        for (int i = 0; i < a.size(); i++) {
            pow.push_back((__int128_t)pow[i] * base % mod);
            hash.push_back(((__int128_t)hash[i] * base + a[i]) % mod);
        }
    }

    long long substr(int l, int r) {
        return sub(hash[r + 1], (__int128_t)hash[l] * pow[r - l + 1] % mod);
    }

    long long merge(long long h1, long long h2, int len2) {
        return ((__int128_t)h1 * pow[len2] + h2) % mod;
    }
};
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long dr_string::base = (mod >> 2) + rng() % (mod >> 1);

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
