// Mohamed_Waheed
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class graph {
private:
    int N;
    vector<bool> vis;
    vector<int> dsu_parent;
    vector<vector<pair<int, long long>>> g;

    void do_dfs(int node) {
        if (vis[node])
            return;
        vis[node] = 1;
        for (auto it : g[node]) {
            if (!vis[it.first]) {
                do_dfs(it.first);
            }
        }
    }

    void bfs(vector<int> parent, int dis, vector<int> &mn_dis) {
        if (parent.empty())
            return;
        for (auto it : parent)
            mn_dis[it] = dis;
        vector<int> child;
        for (auto i : parent) {
            vis[i] = 1;
            for (auto j : g[i]) {
                if (!vis[j.first]) {
                    child.push_back(j.first);
                    vis[j.first] = 1;
                }
            }
        }
        bfs(child, dis + 1, mn_dis);
    }

    int get_parent(int node) {
        if (dsu_parent.empty()) {
            dsu_parent.assign(N, 0);
            iota(dsu_parent.begin(), dsu_parent.end(), 0);
        }
        if (node == dsu_parent[node])
            return node;
        return dsu_parent[node] = get_parent(dsu_parent[node]);
    }

public:
    graph(int n) {
        N = n;
        g.resize(N);
    }

    void add_edge(int u, int v, long long cost = 0) {
        --u, --v;
        g[u].push_back({v, cost});
    }

    void dfs(int node) {
        vis.assign(N, 0);
        do_dfs(node);
    }

    vector<int> bfs(int node) {
        vector<int> dis(N, 1e9);
        vis.assign(N, 0);
        bfs({node}, 0, dis);
        return dis;
    }

    vector<int> components() {
        int key = 1;
        vector<int> comp(N);

        auto check = [&](auto self, ll node) {
            if (vis[node])
                return;
            comp[node] = key;
            vis[node] = 1;
            for (auto it : g[node]) {
                if (!vis[it.first]) {
                    self(self, it.first);
                }
            }
        };

        vis.assign(N, 0);
        for (int i = 0; i < N; i++) {
            if (!vis[i]) {
                check(check, i);
                key++;
            }
        }
        return comp;
    }

    vector<int> is_on_cycle() {
        vector<int> is_cyclic(N);
        for (int i = 0; i < N; ++i) {
            is_cyclic[i] = g[i].size();
        }

        auto check = [&](auto self, int node) {
            if (vis[node] || is_cyclic[node] != 1)
                return;
            is_cyclic[node]--;
            vis[node] = 1;
            for (auto it : g[node]) {
                if (!vis[it.first]) {
                    is_cyclic[it.first]--;
                    self(self, it.first);
                }
            }
        };

        vis.assign(N, 0);
        for (int i = 0; i < N; i++) {
            check(check, i);
        }
        return is_cyclic;
    }

    vector<long long> dijkstra(int start) {
        vector<long long> cheapest_path(N, 1e18);
        vis.assign(N, 0);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        pq.push({0, start});
        while (pq.size()) {
            auto [cost, node] = pq.top();
            pq.pop();
            if (vis[node])
                continue;
            vis[node] = 1;
            cheapest_path[node] = cost;
            for (auto [next, c] : g[node]) {
                if (!vis[next]) {
                    pq.push({cost + c, next});
                }
            }
        }
        return cheapest_path;
    }

    bool same_set(int u, int v) {
        return get_parent(u) == get_parent(v);
    }

    void unite(int u, int v) {
        u = get_parent(u);
        v = get_parent(v);
        dsu_parent[u] = v;
    }

    void solve() {
    }
};

void Main() {
}
/*









*/
signed main() {
    ios_base::sync_with_stdio(false), cout.tie(NULL), cin.tie(NULL);
    ll T = 1;
    // cin >> T;
    for (ll i = 1; i <= T; i++) {
        Main();
        cout << '\n';
    }
    return 0;
}
