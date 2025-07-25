// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

pair<bool, vector<int>> bipartite_graph(vector<vector<int>> &g) {
    bool ok = 1; // stores if graph is bipartite or not
    vector<int> side(g.size(), -1);

    function<void(int)> dfs = [&](int node) {
        for (auto it : g[node]) {
            if (side[it] == -1) {
                side[it] = side[node] ^ 1;
                dfs(it);
            }
            else if (side[node] == side[it]) {
                ok = 0;
            }
        }
    };

    for (int i = 0; i < g.size(); ++i) {
        if (side[i] == -1) {
            side[i] = 0;
            dfs(i);
        }
    }
    return {ok, side};
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
