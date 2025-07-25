// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

void ternary_local_mn() {
    auto f = [&](int64_t x) {
        return x;
    };

    int64_t l = 0, r = 100, ans;
    while (l <= r) { // 2 1 2
        int64_t m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;

        if (f(m1) < f(m2)) {
            r = m2 - 1, ans = m1;
        }
        else {
            l = m1 + 1, ans = m2;
        }
    }
}

void ternary_local_mx() {
    auto f = [&](int64_t x) {
        return x;
    };
    
    int64_t l = 0, r = 100, ans;
    while (l <= r) { // 1 2 1
        int64_t m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
    
        if (f(m1) > f(m2)) {
            r = m2 - 1, ans = m1;
        }
        else {
            l = m1 + 1, ans = m2;
        }
    }
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
