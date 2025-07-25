// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

class LCA {
private:
    vector<vector<int>> dp, anc;
    vector<int> flat, st, depth;

    int merge(int a, int b) {
        if (depth[flat[a]] < depth[flat[b]]) {
            return a;
        }
        return b;
    }

public:
    LCA() {}
    LCA(vector<vector<int>> &g) {
        int n = (int)g.size() - 1;
        st.resize(n + 1);
        depth.resize(n + 1);

        anc.assign(__lg(n) + 1, vector<int>(n + 1, 0));
        function<void(int, int, int)> dfs = [&](int node, int par, int d) {
            depth[node] = d;
            anc[0][node] = par;
            st[node] = flat.size();
            flat.push_back(node);
            for (auto &it : g[node]) {
                if (it != par) {
                    dfs(it, node, d + 1);
                    flat.push_back(node);
                }
            }
        };
        dfs(1, 0, 0);

        for (int i = 1; i <= __lg(n); ++i) {
            for (int j = 1; j <= n; ++j) {
                anc[i][j] = anc[i - 1][anc[i - 1][j]];
            }
        }

        int f = flat.size();
        dp.assign(__lg(f) + 1, vector<int>(f));
        for (int i = 0; i < f; ++i) {
            dp[0][i] = i;
        }

        for (int i = 1; i <= __lg(f); ++i) {
            for (int j = 0; j + (1 << (i - 1)) < f; ++j) {
                dp[i][j] = merge(dp[i - 1][j], dp[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    int kth_anc(int node, int k) {
        if (depth[node] < k) {
            return 0;
        }
        for (int i = 0; i < anc.size(); ++i) {
            if (k & (1 << i)) {
                node = anc[i][node];
            }
        }
        return node;
    }

    int lca(int u, int v) {
        u = st[u], v = st[v];
        if (u > v) {
            swap(u, v);
        }
        int lg = 32 - __builtin_clz(v - u + 1) - 1;
        return flat[merge(dp[lg][u], dp[lg][v - (1 << lg) + 1])];
    }

    int distance(int a, int b) {
        return depth[a] + depth[b] - 2 * depth[lca(a, b)];
    }
};

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
