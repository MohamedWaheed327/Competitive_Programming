// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

template <class node>
class segment_tree {
private:
    int size;
    vector<node> seg;

    template <class... M>
    void build(int x, int lx, int rx, const vector<M> &...a) {
        if (lx == rx) {
            return seg[x].apply(lx, rx, a[lx]...);
        }
        int mid = lx + rx >> 1;
        int left = x + 1;
        int right = x + 2 * (mid - lx + 1);
        build(left, lx, mid, a...);
        build(right, mid + 1, rx, a...);
        seg[x].merge(seg[left], seg[right]);
    }

    template <class... M>
    void modify(int x, int lx, int rx, int l, int r, const M &...value) {
        if (l <= lx && rx <= r) {
            return seg[x].apply(lx, rx, value...);
        }
        int mid = lx + rx >> 1;
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
        int mid = lx + rx >> 1;
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
        int mid = lx + rx >> 1;
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
    segment_tree(int n, M... x) : size(n), seg(2 * n) {
        build(0, 0, size - 1, vector<M>(n, x)...);
    }

    template <class... M>
    segment_tree(const vector<M> &...a) : size((a.size(), ...)), seg(2 * size) {
        build(0, 0, size - 1, a...);
    }

    template <class... M>
    void update(int l, int r, const M &...value) {
        modify(0, 0, size - 1, l, r, value...);
    }

    node query(int l, int r) {
        return query(0, 0, size - 1, l, r);
    }

    int find_first(int l, int r, const auto &F) {
        return find(0, 0, size - 1, nullptr, l, r, 1, F).first;
    }

    int find_last(int l, int r, const auto &F) {
        return find(0, 0, size - 1, nullptr, l, r, 0, F).first;
    }
};

struct node {
    int64_t sum = 0, lazy = -1;

    void apply(int lx, int rx, int64_t val = 0) {
        sum = (rx - lx + 1) * val;
        lazy = val;
    }

    void merge(const node &a, const node &b) {
        sum = a.sum + b.sum;
    }

    void propagate(node &left, node &right, int lx, int rx, int mid) {
        // if (lazy != -1) {
        //     left.apply(lx, mid, lazy);
        //     right.apply(mid + 1, rx, lazy);
        //     lazy = -1;
        // }
    }
};

template <class node, bool val_on_edge = false, bool reverse = false>
class HLD {
private:
    int n, cur_pos = 0;
    const vector<vector<int>> &g;
    segment_tree<node> forward, backward;
    vector<int> par, sz, depth, pos, top;

    vector<pair<int, int>> get_path(int l, int r) {
        vector<pair<int, int>> a, b;
        while (top[l] != top[r]) {
            if (depth[top[r]] > depth[top[l]]) {
                b.push_back({pos[top[r]], pos[r]});
                r = par[top[r]];
            }
            else {
                a.push_back({pos[l], pos[top[l]]});
                l = par[top[l]];
            }
        }

        if (!val_on_edge) {
            a.push_back({pos[l], pos[r]});
        }
        else if (l != r) {
            a.push_back(pos[l] > pos[r] ? pair{pos[l], pos[r] + 1} : pair{pos[l] + 1, pos[r]});
        }

        a.insert(a.end(), b.rbegin(), b.rend());
        return a;
    }

    void dfs1(int nd, int pr, int dep) {
        par[nd] = pr;
        sz[nd] = 1;
        depth[nd] = dep;
        for (auto it : g[nd]) {
            if (it != pr) {
                dfs1(it, nd, dep + 1);
                sz[nd] += sz[it];
            }
        }
    }

    void dfs2(int nd, bool is_top) {
        pos[nd] = cur_pos++;
        top[nd] = (is_top ? nd : top[par[nd]]);

        int heavy = -1;
        for (auto it : g[nd]) {
            if (it != par[nd] && (heavy == -1 || sz[heavy] < sz[it])) {
                heavy = it;
            }
        }
        if (heavy != -1) {
            dfs2(heavy, false);
        }
        for (auto it : g[nd]) {
            if (it != par[nd] && it != heavy) {
                dfs2(it, true);
            }
        }
    }

public:
    HLD(const vector<vector<int>> &_g, int root = -1) : g(_g), n(_g.size()), forward(n), backward(reverse ? n : 1) {
        par = sz = depth = pos = top = vector<int>(n);
        if (~root) dfs1(root, -1, 0), dfs2(root, true);
        for (int i = 0; i < n; ++i) {
            if (!sz[i]) {
                dfs1(i, -1, 0);
                dfs2(i, true);
            }
        }
    }

    template <class... M>
    void update_subtree(int v, const M &...value) {
        int L = pos[v] + (val_on_edge), R = pos[v] + sz[v] - 1;
        if (L <= R) {
            forward.update(L, R, value...);
            if (reverse) backward.update(n - R - 1, n - L - 1, value...);
        }
    }

    template <class... M>
    void update_path(int u, int v, const M &...value) {
        for (auto [L, R] : get_path(u, v)) {
            if (L > R) swap(L, R);
            forward.update(L, R, value...);
            if (reverse) backward.update(n - R - 1, n - L - 1, value...);
        }
    }

    node query_subtree(int v) {
        if (val_on_edge && sz[v] == 1) return node();
        return forward.query(pos[v] + (val_on_edge), pos[v] + sz[v] - 1);
    }

    node query_path(int u, int v) {
        node ret, mrg;
        int i = 0;
        for (auto [L, R] : get_path(u, v)) {
            mrg = (L <= R or !reverse ? forward.query(min(L, R), max(L, R)) : backward.query(n - L - 1, n - R - 1));
            i++ == 0 ? void(ret = mrg) : ret.merge(ret, mrg);
        }
        return ret;
    }
};

void Main(...) {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n + 1);
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    HLD<node> x(g, 1);
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
