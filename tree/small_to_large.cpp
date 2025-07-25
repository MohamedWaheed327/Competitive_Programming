// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

class small_to_large {
private:
    vector<vector<int>> &g;
    vector<int> tree, in, sz, &v, ans;

    void euler(int node, int par) {
        in[node] = tree.size();
        tree.push_back(node);
        sz[node] = 1;
        for (auto it : g[node]) {
            if (it != par) {
                euler(it, node);
                sz[node] += sz[it];
            }
        }
    }

    void dfs(int node, int par, bool keep) {
        int heavy = -1;
        for (auto it : g[node]) {
            if (it != par && (heavy == -1 || sz[it] > sz[heavy])) {
                heavy = it;
            }
        }
        for (auto it : g[node]) {
            if (it != par && it != heavy) {
                dfs(it, node, false);
            }
        }
        if (~heavy) dfs(heavy, node, true);

        for (auto it : g[node]) {
            if (it != par && it != heavy) {
                for (int i = 0; i < sz[it]; ++i) {
                    add(tree[in[it] + i]);
                }
            }
        }
        calc(node);
        add(node);
        if (!keep) {
            for (int i = 0; i < sz[node]; ++i) {
                remove(tree[in[node] + i]);
            }
        }
    }

    int res = 0;
    void add(int node) {
    }

    void remove(int node) {
    }

    // you have only the nodes down, the node itself is not included
    void calc(int node) {
        ans[node] = res;
    }

public:
    small_to_large(vector<vector<int>> &g, vector<int> &v) : g(g), v(v) {
        in = sz = ans = vector<int>(g.size());
        euler(1, -1), dfs(1, -1, false);
    }

    vector<int> get() { return ans; }
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
