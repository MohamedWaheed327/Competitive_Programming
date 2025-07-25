// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

int64_t inclusion_exclusion(int64_t n, vector<int64_t> factors) {
    int sz = (int)factors.size();
    int64_t ret = 0;
    for (int64_t mask = 1; mask < (1 << sz); ++mask) {
        int64_t lc = 1;
        for (int64_t bit = 0; bit < sz; ++bit) {
            if ((1 << bit) & mask) {
                lc = lcm(lc, factors[bit]);
            }
        }

        if (__builtin_popcount(mask) & 1) {
            ret += n / lc;
        }
        else {
            ret -= n / lc;
        }
    }
    return n - ret;
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
