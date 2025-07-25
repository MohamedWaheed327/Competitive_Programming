// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

template <bool val_on_edge = false>
class Mo_Tree {
private:
    static inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
        if (pow == 0) return 0;
        int hpow = 1 << (pow - 1);
        int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
        seg = (seg + rotate) & 3;
        const int rotateDelta[4] = {3, 0, 0, 1};
        int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
        int nrot = (rotate + rotateDelta[seg]) & 3;
        int64_t subSquareSize = int64_t(1) << (2 * pow - 2);
        int64_t ordd = seg * subSquareSize;
        int64_t add = hilbertOrder(nx, ny, pow - 1, nrot);
        ordd += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
        return ordd;
    }

    struct query {
        int l, r, q_indx, lc;
        int64_t ord;
    };

    LCA lca;
    vector<query> Q;
    vector<int> tree, st, en, node_freq, v;

    void add(int ind, int add) {
        node_freq[tree[ind]] += add;
        if (node_freq[tree[ind]] == 1) {
            add_node(tree[ind]);
        }
        else {
            remove_node(tree[ind]);
        }
    }

    int64_t res = 0;
    void add_node(int node) {
    }

    void remove_node(int node) {
    }

    int64_t calc(...) {
        return res;
    }

public:
    Mo_Tree(vector<vector<int>> &g, const vector<int> &v) : v(v), lca(g) {
        st = en = node_freq = vector<int>(g.size());

        function<void(int, int)> dfs = [&](int node, int p) {
            st[node] = tree.size();
            tree.push_back(node);
            for (auto it : g[node]) {
                if (it != p) {
                    dfs(it, node);
                }
            }
            en[node] = tree.size();
            tree.push_back(node);
        };
        dfs(1, -1);
    }

    Mo_Tree(vector<vector<pair<int, int>>> &g) {
        int n = g.size();
        vector<vector<int>> _g(n);
        for (int i = 0; i < n; ++i) {
            for (auto [it, c] : g[i]) {
                _g[i].push_back(it);
            }
        }

        lca = LCA(_g);
        st = en = node_freq = v = vector<int>(n);

        function<void(int, int)> dfs = [&](int node, int p) {
            st[node] = tree.size();
            tree.push_back(node);
            for (auto [it, c] : g[node]) {
                if (it != p) {
                    v[it] = c;
                    dfs(it, node);
                }
            }
            en[node] = tree.size();
            tree.push_back(node);
        };
        dfs(1, -1);
    }

    void add_query(int u, int v) {
        if (st[u] > st[v]) {
            swap(u, v);
        }
        int lc = lca.lca(u, v), l = en[u], r = st[v];
        if (lc == u) {
            l = st[u] + val_on_edge, lc = -1;
        }
        Q.push_back({l, r, Q.size(), lc, hilbertOrder(l, r, __lg(tree.size()) + 1, 0)});
    }

    vector<int64_t> get_ans() {
        vector<int64_t> ans(Q.size());

        sort(Q.begin(), Q.end(), [&](query a, query b) {
            return a.ord < b.ord;
        });

        int l = 0, r = -1;
        for (auto [L, R, q_indx, lc, ord] : Q) {
            while (l > L)
                add(--l, 1);
            while (r < R)
                add(++r, 1);
            while (r > R)
                add(r--, -1);
            while (l < L)
                add(l++, -1);

            if (~lc && !val_on_edge) add_node(lc);
            ans[q_indx] = calc();
            if (~lc && !val_on_edge) remove_node(lc);
        }

        return ans;
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
