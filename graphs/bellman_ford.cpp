// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

template <int base = 1, int mode = 1> // mode = 1 (min), mode = -1 (max)
class bellman_ford {
private:
    int n;
    set<int> inf_nodes;
    vector<int64_t> dis;
    vector<int> par1, par2, par3;

public:
    const int64_t INF = 1e18;
    bellman_ford() = default;

    bellman_ford(vector<vector<pair<int, int>>> &g, vector<int> src = {base}) {
        n = (int)g.size() - 1;
        dis = vector<int64_t>(n + 1, INF);
        par1 = par2 = vector<int>(n + 1, -1);

        for (auto it : src) {
            dis[it] = 0;
        }

        int itr = n;
        while (itr--) {
            for (int i = base; i <= n; ++i) {
                for (auto [next, cost] : g[i]) {
                    if (dis[i] != INF && dis[i] + mode * cost < dis[next]) {
                        if (itr) {
                            dis[next] = dis[i] + mode * cost;
                        }
                        else {
                            inf_nodes.insert(next);
                        }
                        par1[next] = i;
                    }
                }
            }
        }

        vector<int> q(inf_nodes.begin(), inf_nodes.end());
        for (int i = 0; i < q.size(); ++i) {
            if (dis[q[i]] == -INF) continue;
            dis[q[i]] = -INF;

            for (auto [it, c] : g[q[i]]) {
                if (dis[it] != -INF) {
                    par2[it] = q[i];
                    q.push_back(it);
                }
            }
        }

        q = src;
        vector<int> vis(n + 1);
        par3.resize(n + 1);
        for (auto it : src) {
            par3[it] = -1;
        }
        for (int i = 0; i < q.size(); ++i) {
            if (vis[q[i]]) continue;
            vis[q[i]] = 1;
            for (auto [it, c] : g[q[i]]) {
                if (!vis[it]) {
                    if (~par3[it]) par3[it] = q[i];
                    q.push_back(it);
                }
            }
        }
    }

    int64_t best(int node) {
        return mode * dis[node];
    }

    /*
        return path, l, r
        when path contain +VE or -VE cycle --> l, r specifies the range of this cycle in path
    */
    tuple<vector<int>, int, int> get_path(int node) {
        if (dis[node] == INF) return {};

        vector<int> ret, vis(n + 1);
        while (dis[node] == -INF && !inf_nodes.count(node)) {
            ret.push_back(node);
            node = par2[node];
        }

        for (int itr = n + 1; ~node && itr--; node = par1[node]) {
            ret.push_back(node);
        }

        int l = ret.size() - 1 - (find(ret.rbegin() + 1, ret.rend(), ret.back()) - ret.rbegin()), r = ret.size() - 1;
        for (; ~node; node = par3[node]) {
            ret.push_back(node);
        }
        reverse(ret.begin(), ret.end());
        l = ret.size() - l - 1, r = ret.size() - r - 1, swap(l, r);
        if (dis[ret.back()] != -INF) l = r = -1;
        return {ret, l, r};
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
