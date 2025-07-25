// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

template <class M>
class SQblocks {
private:
    int SQ;
    vector<M> v;
    vector<long long> ans;
    vector<vector<long long>> block;

public:
    SQblocks(const vector<M> &v) {
        SQ = sqrt(v.size()) + 1;
        this->v = v;
        ans.resize(SQ);
        block.resize(SQ);
        for (int i = 0; i < v.size(); i++) {
            block[i / SQ].push_back(v[i]);
        }
        for (int i = 0; i < SQ; ++i) {
            sort(block[i].begin(), block[i].end());
            if (block[i].size()) ans[i] = block[i][0];
        }
    }

    void update(int ind, long long val) {
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
        ans[ind / SQ] = blk[0];
    }

    long long query(int l, int r) {
        long long ret = LLONG_MAX;
        while (l <= r) {
            if (l % SQ || r - l < SQ) {
                ret = min(ret, 1ll * v[l]);
                l += 1;
            }
            else {
                ret = min(ret, ans[l / SQ]);
                l += SQ;
            }
        }
        return ret;
    }
};

void Main(...) {
    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    SQblocks sq(v);
    while (q--) {
        int op, ind, v, l, r;
        cin >> op;
        if (op == 1) {
            cin >> ind >> v;
            sq.update(--ind, v);
        }
        else {
            cin >> l >> r;
            cout << sq.query(--l, --r) << '\n';
        }
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
