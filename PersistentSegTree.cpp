// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

template <int LX = 0, int RX = (int)1e9>
class seg_tree {
private:
    struct node {
        int f = 0;
        int left = -1, right = -1;

        void apply(int lx, int rx, long long val = 0) {
            f = val;
        }

        void merge(const node &a, const node &b) {
            f = a.f + b.f;
        }
    };

    inline void propagate(int x, int lx, int rx) {
        // int mid = lx + rx >> 1;
        // int left = seg[x].left;
        // int right = seg[x].right;
        // if (~seg[x].lazy) {
        //     seg[left].apply(lx, mid, seg[x].lazy);
        //     seg[right].apply(mid + 1, rx, seg[x].lazy);
        //     seg[x].lazy = -1;
        // }
    }

    int cur_time;
    vector<node> seg;
    vector<int> roots;

    void create_node(int &x) {
        if (x == -1) {
            x = seg.size();
            seg.push_back(node());
        }
    }

    int new_node() {
        seg.push_back(node());
        return seg.size() - 1;
    }

    template <class... M>
    int update(int x, int lx, int rx, int l, int r, const M &...val) {
        if (rx < l || r < lx) {
            return x;
        }
        if (l <= lx && rx <= r) {
            int nd = new_node();
            seg[nd].apply(lx, rx, val...);
            return nd;
        }
        create_node(seg[x].left);
        create_node(seg[x].right);
        propagate(x, lx, rx);
        int mid = lx + rx >> 1;
        int L = update(seg[x].left, lx, mid, l, r, val...);
        int R = update(seg[x].right, mid + 1, rx, l, r, val...);
        int nd = new_node();
        seg[nd].merge(seg[L], seg[R]);
        seg[nd].left = L, seg[nd].right = R;
        return nd;
    }

    node query(int x, int lx, int rx, int l, int r) {
        if (l <= lx && rx <= r) {
            return seg[x];
        }
        create_node(seg[x].left);
        create_node(seg[x].right);
        propagate(x, lx, rx);
        int mid = lx + rx >> 1;
        int left = seg[x].left;
        int right = seg[x].right;
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

    pair<int, node> node_find_first(int x, int lx, int rx, node *node_before, const auto &F) {
        node cur_node = seg[x];
        if (node_before != NULL) {
            cur_node.merge(*node_before, seg[x]);
        }
        if (!F(cur_node)) {
            return {-1, cur_node};
        }
        if (lx == rx) {
            return {lx, cur_node};
        }
        create_node(seg[x].left);
        create_node(seg[x].right);
        propagate(x, lx, rx);
        int mid = lx + rx >> 1;
        int left = seg[x].left;
        int right = seg[x].right;
        pair<int, node> lft = node_find_first(left, lx, mid, node_before, F);
        if (~lft.first) {
            return lft;
        }
        return node_find_first(right, mid + 1, rx, &lft.second, F);
    }

    pair<int, node> find_first(int x, int lx, int rx, int l, int r, node *node_before, const auto &F) {
        if (l <= lx && rx <= r) {
            return node_find_first(x, lx, rx, node_before, F);
        }
        create_node(seg[x].left);
        create_node(seg[x].right);
        propagate(x, lx, rx);
        int mid = lx + rx >> 1;
        int left = seg[x].left;
        int right = seg[x].right;
        if (r < mid + 1) {
            return find_first(left, lx, mid, l, r, node_before, F);
        }
        if (mid < l) {
            return find_first(right, mid + 1, rx, l, r, node_before, F);
        }
        pair<int, node> lft = find_first(left, lx, mid, l, r, node_before, F);
        if (~lft.first) {
            return lft;
        }
        return find_first(right, mid + 1, rx, l, r, &lft.second, F);
    }

    pair<int, node> node_find_last(int x, int lx, int rx, node *node_before, const auto &F) {
        node cur_node = seg[x];
        if (node_before != NULL) {
            cur_node.merge(seg[x], *node_before);
        }
        if (!F(cur_node)) {
            return {-1, cur_node};
        }
        if (lx == rx) {
            return {lx, cur_node};
        }
        create_node(seg[x].left);
        create_node(seg[x].right);
        propagate(x, lx, rx);
        int mid = lx + rx >> 1;
        int left = seg[x].left;
        int right = seg[x].right;
        pair<int, node> rgt = node_find_last(right, mid + 1, rx, node_before, F);
        if (~rgt.first) {
            return rgt;
        }
        return node_find_last(left, lx, mid, &rgt.second, F);
    }

    pair<int, node> find_last(int x, int lx, int rx, int l, int r, node *node_before, const auto &F) {
        if (l <= lx && rx <= r) {
            return node_find_last(x, lx, rx, node_before, F);
        }
        create_node(seg[x].left);
        create_node(seg[x].right);
        propagate(x, lx, rx);
        int mid = lx + rx >> 1;
        int left = seg[x].left;
        int right = seg[x].right;
        if (r < mid + 1) {
            return find_last(left, lx, mid, l, r, node_before, F);
        }
        if (mid < l) {
            return find_last(right, mid + 1, rx, l, r, node_before, F);
        }
        pair<int, node> rgt = find_last(right, mid + 1, rx, l, r, node_before, F);
        if (~rgt.first) {
            return rgt;
        }
        return find_last(left, lx, mid, l, r, &rgt.second, F);
    }

public:
    seg_tree() {
        seg.resize(1);
        cur_time = -1;
    }

    template <class... M>
    void insert(int l, int r, const M &...val) {
        roots.push_back(0);
        ++cur_time;
        roots[cur_time] = update(roots[max(cur_time - 1, 0)], LX, RX, l, r, val...);
    }

    template <class... M>
    void update(int l, int r, const M &...val) {
        roots[cur_time] = update(roots[cur_time], LX, RX, l, r, val...);
    }

    node query(int time, int l, int r) {
        return query(roots[time], LX, RX, l, r);
    }

    int find_first(int time, int l, int r, const auto &F) {
        return find_first(roots[time], LX, RX, l, r, NULL, F).first;
    }

    int find_last(int time, int l, int r, const auto &F) {
        return find_last(roots[time], LX, RX, l, r, NULL, F).first;
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
