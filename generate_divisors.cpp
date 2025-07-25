// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

const int N = 100;

vector<int> calc(int N) {
    vector<int> _primes;
    vector<int> _spf(N + 1, 0);
    iota(_spf.begin(), _spf.end(), 0);
    for (long long i = 2; i <= N; i++) {
        if (_spf[i] == i) {
            _primes.push_back(i);
        }
        for (auto it : _primes) {
            if (i * it > N) {
                break;
            }
            _spf[i * it] = min(it, _spf[i]);
            if (i % it == 0) {
                break;
            }
        }
    }
    return _spf;
}

vector<int> spf = calc(N);
vector<int> factors(int n) {
    vector<int> ret;
    int cur = n;
    while (1 < cur) {
        ret.push_back(spf[cur]);
        cur /= spf[cur];
    }
    return ret;
}

vector<int> divisors(int n) {
    auto fact = factors(n);
    vector<array<int, 2>> p;
    for (auto &it : fact) {
        if (p.empty() || p.back()[0] != it) {
            p.push_back({it, 1});
        }
        else {
            p.back()[1]++;
        }
    }
    vector<int> ret;
    function<void(int, int)> build = [&](int i, int res) {
        if (i == p.size()) {
            ret.push_back(res);
            return;
        }
        int x = 1, itr = p[i][1] + 1;
        while (itr--) {
            build(i + 1, res * x);
            x *= p[i][0];
        }
    };
    build(0, 1);
    sort(ret.begin(), ret.end());
    return ret;
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
