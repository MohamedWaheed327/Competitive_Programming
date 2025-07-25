// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

class sparse_table {
private:
    long long merge(long long a, long long b) {
        return a & b;
    }

    vector<vector<long long>> dp;

public:
    template <class M>
    sparse_table(const vector<M> &a) {
        int n = a.size(), lg = __lg(n);
        dp.resize(lg + 1, vector<long long>(n));

        for (int i = 0; i < n; ++i) {
            dp[0][i] = a[i];
        }

        for (int j = 1; j <= lg; j++) {
            for (int i = 0; i + (1 << (j - 1)) < n; i++) {
                dp[j][i] = merge(dp[j - 1][i], dp[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    long long query(int l, int r) {
        int lg = 32 - __builtin_clz(r - l + 1) - 1;
        return merge(dp[lg][l], dp[lg][r - (1 << lg) + 1]);
    }
};

void Main(...) {
    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    for (auto &it : v) {
        cin >> it;
    }

    sparse_table st(v);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << st.query(--l, --r) << '\n';
    }
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
