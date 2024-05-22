// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

class segment_tree {
private:
    struct node {
        int mx;

        void apply(int lx, int rx, int val) {
            mx = val;
        }

        void merge(const node &a, const node &b) {
            mx = max(a.mx, b.mx);
        }
    };

    int size;
    vector<node> seg;

    template <class M>
    void build(int x, int lx, int rx, const vector<M> &build_seg) {
        if (lx == rx) {
            seg[x].apply(lx, rx, build_seg[lx]);
            return;
        }
        int mid = lx + rx >> 1;
        int left = x + 1;
        int right = x + (mid - lx + 1 << 1);
        build(left, lx, mid, build_seg);
        build(right, mid + 1, rx, build_seg);
        seg[x].merge(seg[left], seg[right]);
    }

    template <class M>
    void update(int x, int lx, int rx, int l, int r, const M &value) {
        if (l <= lx && rx <= r) {
            seg[x].apply(lx, rx, value);
            return;
        }
        int mid = lx + rx >> 1;
        int left = x + 1;
        int right = x + (mid - lx + 1 << 1);
        if (l <= mid) {
            update(left, lx, mid, l, r, value);
        }
        if (r >= mid + 1) {
            update(right, mid + 1, rx, l, r, value);
        }
        seg[x].merge(seg[left], seg[right]);
    }

    node query(int x, int lx, int rx, int l, int r) {
        if (l <= lx && rx <= r) {
            return seg[x];
        }
        int mid = lx + rx >> 1;
        int left = x + 1;
        int right = x + (mid - lx + 1 << 1);
        node ret;
        if (r < mid + 1) {
            return query(left, lx, mid, l, r);
        }
        else if (mid < l) {
            return query(right, mid + 1, rx, l, r);
        }
        else {
            ret.merge(query(left, lx, mid, l, r), query(right, mid + 1, rx, l, r));
        }
        return ret;
    }

public:
    template <class M>
    segment_tree(const vector<M> &build_seg) {
        size = build_seg.size();
        seg.resize(2 * size - 1);
        build(0, 0, size - 1, build_seg);
    }

    template <class M>
    void update(int ind, const M &value) {
        update(0, 0, size - 1, ind, ind, value);
    }

    int query(int l, int r) {
        if (l > r) {
            return 0;
        }
        return query(0, 0, size - 1, l, r).mx;
    }
};

template <class M>
vector<M> compress(vector<M> &v) {
    auto real = v;
    sort(real.begin(), real.end());
    real.erase(unique(real.begin(), real.end()), real.end());

    for (auto &it : v) {
        it = lower_bound(real.begin(), real.end(), it) - real.begin();
    }
    return real;
}

vector<int> lis(vector<int> v) {
    auto real = compress(v);
    int n = v.size();
    vector<int> dp(n, 0);
    segment_tree st(dp);
    vector<pair<int, int>> history;

    for (auto it : v) {
        history.push_back({it, dp[it]});
        dp[it] = max(dp[it], st.query(0, it - 1) + 1);
        st.update(it, dp[it]);
    }

    long long mx = st.query(0, n - 1), last = LLONG_MAX;
    vector<int> ret;
    for (int i = n - 1; ~i; i--) {
        if (mx == dp[v[i]] && last > v[i]) {
            mx--;
            last = v[i];
            ret.push_back(v[i]);
        }
        auto [idx, val] = history.back();
        dp[idx] = val;
        history.pop_back();
    }
    reverse(ret.begin(), ret.end());
    for (auto &it : ret) {
        it = real[it];
    }
    return ret;
}

void Main(...) {
    for (auto it : lis({2, 1, 5, 2, 8, 9, 4, 10})) {
        cout << it << " ";
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
