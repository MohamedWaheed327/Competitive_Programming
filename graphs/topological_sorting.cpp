// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

vector<int> topo_sort(vector<vector<int>> &g) {
    int n = (int)g.size() - 1, ok = 1;
    vector<int> vis(n + 1, 0), check(n + 1, 0), ret;

    function<void(int)> dfs = [&](int node) {
        vis[node] = check[node] = true;
        for (auto it : g[node]) {
            if (!vis[it]) {
                dfs(it);
            }
            else if (check[it]) {
                ok = 0;
            }
        }
        check[node] = false;
        ret.push_back(node);
    };

    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            dfs(i);
        }
    }

    reverse(ret.begin(), ret.end());
    if (!ok) {
        ret.clear();
    }
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
