// Mohamed_Waheed_
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class SQblocks {
private:
    ll ans(const vector<ll> &blk) {
        return blk[0];
    }

    int SQ;
    vector<ll> v;
    vector<vector<ll>> block;

public:
    SQblocks(const vector<ll> &v) {
        SQ = sqrt(v.size()) + 1;
        this->v = v;
        block.resize(SQ);
        for (int i = 0; i < v.size(); i++) {
            block[i / SQ].push_back(v[i]);
        }
        for (auto &it : block) {
            sort(it.begin(), it.end());
        }
    }

    void update(int ind, ll val) {
        auto &blk = block[ind / SQ];
        int it = lower_bound(blk.begin(), blk.end(), v[ind]) - blk.begin();
        v[ind] = blk[it] = val;

        while (0 < it && blk[it - 1] > blk[it]) {
            swap(blk[it - 1], blk[it]);
            --it;
        }
        while (it + 1 < blk.size() && blk[it] > blk[it + 1]) {
            swap(blk[it], blk[it + 1]);
            ++it;
        }
    }

    ll query(int l, int r) {
        ll ret = LLONG_MAX;
        while (l <= r) {
            if (l % SQ || r - l < SQ) {
                ret = min(ret, ans({v[l]}));
                l += 1;
            }
            else {
                ret = min(ret, ans(block[l / SQ]));
                l += SQ;
            }
        }
        return ret;
    }
};

void Main() {
    int n, q;
    cin >> n >> q;

    vector<ll> v(n);
    for (ll i = 0; i < n; ++i) {
        cin >> v[i];
    }

    SQblocks sq(v);
    while (q--) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll ind, v;
            cin >> ind >> v;
            sq.update(ind, v);
        }
        else {
            ll l, r;
            cin >> l >> r;
            cout << sq.query(l, --r) << '\n';
        }
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
