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
