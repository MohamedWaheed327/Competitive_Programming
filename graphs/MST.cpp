// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

template <class T>
auto MST(vector<vector<pair<int, T>>> &g) {
    int n = (int)g.size() - 1;
    vector<bool> added(n + 1, false);
    vector<vector<pair<int, int64_t>>> mst(n + 1);
    priority_queue<tuple<int64_t, int, int>> pq;

    auto add = [&](int node) {
        for (auto &[next, cost] : g[node]) {
            if (!added[next]) {
                pq.push({-cost, node, next});
            }
        }
        added[node] = true;
    };

    add(1);
    for (int i = 1; i < n; ++i) {
        while (added[get<2>(pq.top())]) {
            pq.pop();
        }
        auto [cost, from, to] = pq.top();
        pq.pop();
        mst[from].push_back({to, -cost});
        add(to);
    }
    return mst;
}

void Main(...) {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> g(n + 1);
    for (int i = 0, u, v, c; i < m; ++i) {
        cin >> u >> v >> c;
        g[u].push_back({v, c});
        g[v].push_back({u, c});
    }

    vector<vector<pair<int, int64_t>>> tree = MST(g);
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
