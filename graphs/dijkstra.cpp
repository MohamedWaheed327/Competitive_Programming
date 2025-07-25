// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

template <int base = 1>
class dijkstra {
private:
    vector<int> par;

public:
    const int64_t INF = 1e18;
    vector<int64_t> dis;

    dijkstra(vector<vector<pair<int, int>>> &g, vector<int> src = {base}) : dis(g.size(), INF), par(g.size(), -1) {
        priority_queue<pair<int64_t, int>, vector<pair<int64_t, int>>, greater<>> pq;
        for (auto it : src) {
            dis[it] = 0;
            pq.push({0, it});
        }

        while (pq.size()) {
            auto [cost, node] = pq.top();
            pq.pop();
            if (dis[node] < cost) continue;

            for (auto [next, c] : g[node]) {
                if (dis[node] + c < dis[next]) {
                    par[next] = node;
                    dis[next] = dis[node] + c;
                    pq.push({dis[next], next});
                }
            }
        }
    }

    vector<int> get_path(int node) {
        if (dis[node] == INF) return {};
        vector<int> ret;
        for (int cur = node; ~cur; cur = par[cur]) {
            ret.push_back(cur);
        }
        return vector(ret.rbegin(), ret.rend());
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
