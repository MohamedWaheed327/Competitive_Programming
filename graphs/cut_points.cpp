// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

vector<int> cut_points(vector<vector<int>> &g) {
    int n = (int)g.size() - 1, timer = 0;

    vector<int> ret;
    vector<bool> vis(n + 1, false);
    vector<int> tin(n + 1, 1e9), low(n + 1, 1e9);

    function<void(int, int)> dfs = [&](int node, int par) {
        vis[node] = true;
        low[node] = tin[node] = timer++;

        int childs = 0;
        for (auto &it : g[node]) {
            if (it == par) {
                continue;
            }

            if (vis[it]) {
                low[node] = min(low[node], tin[it]);
            }
            else {
                dfs(it, node);
                low[node] = min(low[node], low[it]);
                if (low[it] >= tin[node] && ~par) {
                    ret.push_back(node);
                }
                childs++;
            }
        }

        if (par == -1 && childs > 1) {
            ret.push_back(node);
        }
    };

    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            dfs(i, -1);
        }
    }
    sort(ret.begin(), ret.end());
    ret.erase(unique(ret.begin(), ret.end()), ret.end());
    return ret;
}

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
