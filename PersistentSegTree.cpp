// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

/* if range assign, you can set opt to true */
template <class node, int64_t LX = INT_MIN, int64_t RX = INT_MAX, bool opt = false>
class seg_tree {
private:
    vector<node> seg;
    vector<int> roots = {-1}, left, right;

    void create_node(int &x) {
        if (x == -1) {
            x = seg.size();
            seg.push_back(node());
            left.push_back(-1);
            right.push_back(-1);
        }
        else if (!opt) {
            int y = x;
            x = seg.size();
            seg.push_back(seg[y]);
            left.push_back(left[y]);
            right.push_back(right[y]);
        }
    }

    template <class... M>
    int update(int x, int64_t lx, int64_t rx, int64_t l, int64_t r, const M &...val) {
        if (rx < l || r < lx) return x;

        int nd = (opt ? -1 : x);
        if (l <= lx && rx <= r) {
            create_node(nd);
            seg[nd].apply(lx, rx, val...);
            return nd;
        }

        int64_t mid = lx + rx >> 1;
        create_node(left[x]);
        create_node(right[x]);
        seg[x].propagate(seg[left[x]], seg[right[x]], lx, rx, mid);

        create_node(nd);
        left[nd] = update(left[x], lx, mid, l, r, val...);
        right[nd] = update(right[x], mid + 1, rx, l, r, val...);
        seg[nd].merge(seg[left[nd]], seg[right[nd]]);

        return nd;
    }

    node query(int x, int64_t lx, int64_t rx, int64_t l, int64_t r) {
        if (l <= lx && rx <= r) {
            return seg[x];
        }

        int64_t mid = lx + rx >> 1;
        create_node(left[x]);
        create_node(right[x]);
        seg[x].propagate(seg[left[x]], seg[right[x]], lx, rx, mid);

        if (r < mid + 1) {
            return query(left[x], lx, mid, l, r);
        }
        if (mid < l) {
            return query(right[x], mid + 1, rx, l, r);
        }
        node ret;
        ret.merge(query(left[x], lx, mid, l, r), query(right[x], mid + 1, rx, l, r));
        return ret;
    }

    pair<int, node> find(int x, int64_t lx, int64_t rx, node *last, int64_t l, int64_t r, int dir, const auto &F) {
        if (l <= lx && rx <= r) {
            node cur_node = seg[x];
            if (last) {
                dir ? cur_node.merge(*last, seg[x]) : cur_node.merge(seg[x], *last);
            }
            if (!F(cur_node)) return {-1, cur_node};
            if (lx == rx) return {lx, cur_node};
        }

        int64_t mid = lx + rx >> 1;
        create_node(left[x]);
        create_node(right[x]);
        seg[x].propagate(seg[left[x]], seg[right[x]], lx, rx, mid);

        if (r < mid + 1) {
            return find(left[x], lx, mid, last, l, r, dir, F);
        }
        if (mid < l) {
            return find(right[x], mid + 1, rx, last, l, r, dir, F);
        }
        auto [idx, nd] = (dir ? find(left[x], lx, mid, last, l, r, dir, F) : find(right[x], mid + 1, rx, last, l, r, dir, F));
        if (~idx) return {idx, nd};
        return dir ? find(right[x], mid + 1, rx, &nd, l, r, dir, F) : find(left[x], lx, mid, &nd, l, r, dir, F);
    }

public:
    seg_tree() { create_node(roots[0]); }

    int cur_time() { return roots.size() - 1; }

    void push_back(int time) {
        roots.push_back(roots[time]);
    }

    template <class... M>
    void update(int time, int64_t l, int64_t r, const M &...val) {
        roots[time] = update(roots[time], LX, RX, l, r, val...);
    }

    node query(int time, int64_t l, int64_t r) {
        return query(roots[time], LX, RX, l, r);
    }

    int find_first(int time, int64_t l, int64_t r, const auto &F) {
        return find(roots[time], LX, RX, nullptr, l, r, 1, F).first;
    }

    int find_last(int time, int64_t l, int64_t r, const auto &F) {
        return find(roots[time], LX, RX, nullptr, l, r, 0, F).first;
    }
};

struct node {
    int64_t sum = 0;

    void apply(int64_t lx, int64_t rx, int64_t val = 0) {
        sum = val;
    }

    void merge(const node &a, const node &b) {
        sum = a.sum + b.sum;
    }

    void propagate(node &left, node &right, int64_t lx, int64_t rx, int64_t mid) {
        // if (lazy != -1) {
        //     left.apply(lx, mid, lazy);
        //     right.apply(mid + 1, rx, lazy);
        //     lazy = -1;
        // }
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
