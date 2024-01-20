// Mohamed_Waheed_
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class sparse_table {
private:
    struct node {
        int mx;

        void operator=(int val) {
            mx = val;
        }
    };

    node merge(const node &a, const node &b) const {
        node ret;
        ret.mx = max(a.mx, b.mx);
        return ret;
    }

    int size;
    vector<vector<node>> dp;

public:
    template <class M>
    sparse_table(const vector<M> &a) {
        size = (int)a.size();
        int max_log = 32 - __builtin_clz(size);
        dp.resize(max_log);

        dp[0].resize(size);
        for (int i = 0; i < size; ++i) {
            dp[0][i] = a[i];
        }

        for (int j = 1; j < max_log; j++) {
            dp[j].resize(size - (1 << j) + 1);
            for (int i = 0; i <= size - (1 << j); i++) {
                dp[j][i] = merge(dp[j - 1][i], dp[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    node query(int l, int r) const {
        int lg = 32 - __builtin_clz(r - l + 1) - 1;
        return merge(dp[lg][l], dp[lg][r - (1 << lg) + 1]);
    }
};

void Main() {
    ll n;
    cin >> n;
    vector<ll> v(n);
    for (auto &it : v) {
        cin >> it;
    }

    sparse_table st(v);

    ll q;
    cin >> q;
    while (q--) {
        ll l, r;
        cin >> l >> r;
        --l, --r;
        cout << st.query(l, r).mx << '\n';
    }
}
/*




*/
signed main() {
    ios_base::sync_with_stdio(false), cout.tie(NULL), cin.tie(NULL);
    ll T = 1;
    // cin >> T;
    for (ll i = 1; i <= T; i++) {
        Main();
        cout << '\n';
    }
    return 0;
}
