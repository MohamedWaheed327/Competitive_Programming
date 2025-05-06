// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

template <class node>
class segment_tree {
private:
    int size;
    vector<node> seg;

    template <class... M>
    void build(int x, int lx, int rx, const vector<M> &...build_seg) {
        if (lx == rx) {
            return seg[x].apply(lx, rx, build_seg[lx]...);
        }
        int mid = (lx + rx) / 2;
        int left = x + 1;
        int right = x + 2 * (mid - lx + 1);
        build(left, lx, mid, build_seg...);
        build(right, mid + 1, rx, build_seg...);
        seg[x].merge(seg[left], seg[right]);
    }

    template <class... M>
    void modify(int x, int lx, int rx, int l, int r, const M &...value) {
        if (l <= lx && rx <= r) {
            return seg[x].apply(lx, rx, value...);
        }
        int mid = (lx + rx) / 2;
        int left = x + 1;
        int right = x + 2 * (mid - lx + 1);
        seg[x].propagate(seg[left], seg[right], lx, rx, mid);
        if (l <= mid) {
            modify(left, lx, mid, l, r, value...);
        }
        if (mid + 1 <= r) {
            modify(right, mid + 1, rx, l, r, value...);
        }
        seg[x].merge(seg[left], seg[right]);
    }

    node query(int x, int lx, int rx, int l, int r) {
        if (l <= lx && rx <= r) {
            return seg[x];
        }
        int mid = (lx + rx) / 2;
        int left = x + 1;
        int right = x + 2 * (mid - lx + 1);
        seg[x].propagate(seg[left], seg[right], lx, rx, mid);
        if (r < mid + 1) {
            return query(left, lx, mid, l, r);
        }
        if (mid < l) {
            return query(right, mid + 1, rx, l, r);
        }
        node ret;
        ret.merge(query(left, lx, mid, l, r), query(right, mid + 1, rx, l, r));
        return ret;
    }

    pair<int, node> find(int x, int lx, int rx, node *last, int l, int r, int dir, const auto &F) {
        if (l <= lx && rx <= r) {
            node cur_node = seg[x];
            if (last) {
                dir ? cur_node.merge(*last, seg[x]) : cur_node.merge(seg[x], *last);
            }
            if (!F(cur_node)) return {-1, cur_node};
            if (lx == rx) return {lx, cur_node};
        }
        int mid = (lx + rx) / 2;
        int left = x + 1;
        int right = x + 2 * (mid - lx + 1);
        seg[x].propagate(seg[left], seg[right], lx, rx, mid);
        if (r < mid + 1) {
            return find(left, lx, mid, last, l, r, dir, F);
        }
        if (mid < l) {
            return find(right, mid + 1, rx, last, l, r, dir, F);
        }
        auto [idx, nd] = (dir ? find(left, lx, mid, last, l, r, dir, F) : find(right, mid + 1, rx, last, l, r, dir, F));
        if (~idx) return {idx, nd};
        return dir ? find(right, mid + 1, rx, &nd, l, r, dir, F) : find(left, lx, mid, &nd, l, r, dir, F);
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
        modify(0, 0, size - 1, l, r, value...);
    }

    node query(int l, int r) {
        return query(0, 0, size - 1, l, r);
    }

    int find(int l, int r, int left_first, const auto &F) {
        return find(0, 0, size - 1, nullptr, l, r, left_first, F).first;
    }
};

struct node {
    long long sum = 0, mn, lazy = -1;

    void apply(int lx, int rx, long long val = 0) {
        sum = (rx - lx + 1) * val;
        mn = lazy = val;
    }

    void merge(const node &a, const node &b) {
        sum = a.sum + b.sum;
        mn = min(a.mn, b.mn);
    }

    inline void propagate(node &left, node &right, int lx, int rx, int mid) {
        if (lazy != -1) {
            left.apply(lx, mid, lazy);
            right.apply(mid + 1, rx, lazy);
            lazy = -1;
        }
    }
};

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
