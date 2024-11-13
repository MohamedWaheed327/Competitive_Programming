// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

template <class M, bool val_on_edge = false>
class Mo_Tree {
private:
    static inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
        if (pow == 0)
            return 0;
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

    int q;
    vector<int> depth, flat, st, en, node_freq;
    vector<vector<int>> anc;
    vector<M> v;
    vector<query> Q;

    long long res = 0;
    void add_node(int node) {

    }

    void remove_node(int node) {

    }

    long long calc(...) {
        return res;
    }

    void add(int ind) {
        node_freq[flat[ind]]++;
        if (node_freq[flat[ind]] == 1) {
            add_node(flat[ind]);
        }
        else {
            remove_node(flat[ind]);
        }
    }

    void remove(int ind) {
        node_freq[flat[ind]]--;
        if (node_freq[flat[ind]] == 1) {
            add_node(flat[ind]);
        }
        else {
            remove_node(flat[ind]);
        }
    }

public:
    Mo_Tree(vector<vector<int>> &g, const vector<M> &v) {
        q = 0;
        this->v = v;
        int n = (int)g.size() - 1;
        depth.resize(n + 1), st.resize(n + 1);
        en.resize(n + 1), node_freq.resize(n + 1);
        anc.assign(n + 1, vector<int>(__lg(n) + 2, 0));

        function<void(int, int, int)> dfs = [&](int node, int p, int d) {
            anc[node][0] = p;
            depth[node] = d;
            st[node] = flat.size();
            flat.push_back(node);
            for (auto it : g[node]) {
                if (it != p) {
                    dfs(it, node, d + 1);
                }
            }
            en[node] = flat.size();
            flat.push_back(node);
        };
        dfs(1, 0, 0);

        for (int j = 1; j <= __lg(n); ++j) {
            for (int i = 1; i <= n; ++i) {
                anc[i][j] = anc[anc[i][j - 1]][j - 1];
            }
        }
    }

    int kth_anc(int node, int k) {
        int ret = node;
        for (int bit = (int)anc[ret].size() - 1; ~bit; --bit) {
            if (k & (1 << bit)) {
                ret = anc[ret][bit];
            }
        }
        return ret;
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) {
            swap(u, v);
        }
        u = kth_anc(u, depth[u] - depth[v]);
        if (u == v) {
            return u;
        }
        for (int bit = anc[0].size() - 1; ~bit; --bit) {
            if (anc[u][bit] != anc[v][bit]) {
                u = anc[u][bit];
                v = anc[v][bit];
            }
        }
        return anc[u][0];
    }

    template <class... T>
    void add_query(int u, int v, T &...x) {
        if (st[u] > st[v]) {
            swap(u, v);
        }
        int lc = lca(u, v), l, r, lc_ = -1;
        if (lc == u || lc == v) {
            l = st[u] + val_on_edge, r = st[v];
        }
        else {
            l = en[u], r = st[v], lc_ = lc;
        }
        Q.push_back({l, r, q++, lc_, hilbertOrder(l, r, __lg(flat.size()) + 1, 0), x...});
    }

    void mo_process() {
        vector<long long> ans(q);

        sort(Q.begin(), Q.end(), [&](query a, query b) {
            return a.ord < b.ord;
        });

        int l = 0, r = -1;
        for (auto [L, R, q_indx, lc, ord] : Q) {
            while (l > L)
                add(--l);
            while (r < R)
                add(++r);
            while (r > R)
                remove(r--);
            while (l < L)
                remove(l++);

            if (~lc && !val_on_edge)
                add_node(lc);
            ans[q_indx] = calc();
            if (~lc && !val_on_edge)
                remove_node(lc);
        }

        for (auto it : ans) {
            cout << it << '\n';
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
