// Mohamed_Waheed
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class segment_tree {
private:
    struct node {

        void apply(int lx, int rx, long long val = 0) {
        }

        void merge(const node &a, const node &b) const {
        }
    };

    inline void propagate(int x, int lx, int rx) {
        // int mid = lx + rx >> 1;
        // int left = x + 1;
        // int right = x + (mid - lx + 1 << 1);
        // if (~seg[x].lazy) {
        //     seg[left].apply(lx, mid, seg[x].lazy);
        //     seg[right].apply(mid + 1, rx, seg[x].lazy);
        //     seg[x].lazy = -1;
        // }
    }

    int size;
    vector<node> seg;

    template <class... M>
    void build(int x, int lx, int rx, const vector<M> &...build_seg) {
        if (lx == rx) {
            seg[x].apply(lx, rx, build_seg[lx]...);
            return;
        }
        int mid = lx + rx >> 1;
        int left = x + 1;
        int right = x + (mid - lx + 1 << 1);
        build(left, lx, mid, build_seg...);
        build(right, mid + 1, rx, build_seg...);
        seg[x].merge(seg[left], seg[right]);
    }

    template <class... M>
    void update(int x, int lx, int rx, int l, int r, const M &...value) {
        if (l <= lx && rx <= r) {
            seg[x].apply(lx, rx, value...);
            return;
        }
        propagate(x, lx, rx);
        int mid = lx + rx >> 1;
        int left = x + 1;
        int right = x + (mid - lx + 1 << 1);
        if (l <= mid) {
            update(left, lx, mid, l, r, value...);
        }
        if (r >= mid + 1) {
            update(right, mid + 1, rx, l, r, value...);
        }
        seg[x].merge(seg[left], seg[right]);
    }

    node query(int x, int lx, int rx, int l, int r) {
        if (l <= lx && rx <= r) {
            return seg[x];
        }
        propagate(x, lx, rx);
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

    int find_first(int x, int lx, int rx, int l, int r, const function<bool(node)> &F) {
        if (rx < l || r < lx || !F(seg[x])) {
            return -1;
        }

        if (lx == rx) {
            return lx;
        }

        propagate(x, lx, rx);
        int mid = lx + rx >> 1;
        int left = x + 1;
        int right = x + (mid - lx + 1 << 1);

        int lft = find_first(left, lx, mid, l, r, F);
        if (~lft) {
            return lft;
        }
        return find_first(right, mid + 1, rx, l, r, F);
    }

public:
    template <class... M>
    segment_tree(int n, M... x) {
        size = n;
        seg.resize(2 * size - 1);
        build(0, 0, size - 1, vector<M>(n, x)...);
    }

    template <class... M>
    segment_tree(const vector<M> &...build_seg) {
        size = (build_seg.size(), ...);
        seg.resize(2 * size - 1);
        build(0, 0, size - 1, build_seg...);
    }

    template <class... M>
    void update(int l, int r, const M &...value) {
        update(0, 0, size - 1, l, r, value...);
    }

    node query(int l, int r) {
        return query(0, 0, size - 1, l, r);
    }

    int find_first(int l, int r, const function<bool(node)> &F) {
        return find_first(0, 0, size - 1, l, r, F);
    }
};

void Main() {
    
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
