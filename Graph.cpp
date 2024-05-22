// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

class graph {
private:
    int N;
    vector<bool> vis;
    vector<int> level;
    vector<int> parent;
    vector<int> dsu_parent;
    vector<vector<int>> anc;
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

    bool is_leave(int node) {
        return (int)g[node].size() == 1;
    }

    vector<int> components() {
        int key = 1;
        vector<int> comp(N);

        function<void(int)> Do = [&](int node) {
            if (vis[node])
                return;
            comp[node] = key;
            vis[node] = 1;
            for (auto it : g[node]) {
                if (!vis[it.first]) {
                    Do(it.first);
                }
            }
        };

        vis.assign(N, 0);
        for (int i = 0; i < N; i++) {
            if (!vis[i]) {
                Do(i);
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

        function<void(int)> Do = [&](int node) {
            if (vis[node] || is_cyclic[node] != 1)
                return;
            is_cyclic[node]--;
            vis[node] = 1;
            for (auto it : g[node]) {
                if (!vis[it.first]) {
                    is_cyclic[it.first]--;
                    Do(it.first);
                }
            }
        };

        vis.assign(N, 0);
        for (int i = 0; i < N; i++) {
            Do(i);
        }
        return is_cyclic;
    }

    vector<long long> dijkstra(int start) {
        vector<long long> cheapest_path(N, 1e18);
        vis.assign(N, 0);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
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

    void build_lca() {
        level.resize(N);
        parent.resize(N);

        function<void(int, int, int)> Do;
        Do = [&](int node, int par, int lvl) {
            parent[node] = par;
            level[node] = lvl;
            for (auto it : g[node]) {
                if (it.first != par) {
                    Do(it.first, node, lvl + 1);
                }
            }
        };
        Do(0, -1, 0);

        int lg = __lg(N) + 1;
        anc = vector(N, vector<int>(lg, -1));
        for (int i = 0; i < lg; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i == 0) {
                    anc[j][i] = parent[j];
                }
                else if (~anc[j][i - 1]) {
                    anc[j][i] = anc[anc[j][i - 1]][i - 1];
                }
            }
        }
    }

    int get_anc(int node, int k) {
        if (k >= N) {
            return -1;
        }
        int ret = node;
        for (int bit = __lg(k); ~bit; --bit) {
            if ((k & (1 << bit)) && ~ret) {
                ret = anc[ret][bit];
            }
        }
        return ret;
    }

    int lca(int a, int b) {
        if (level[a] < level[b]) {
            b = get_anc(b, level[b] - level[a]);
        }

        if (level[b] < level[a]) {
            a = get_anc(a, level[a] - level[b]);
        }

        if (a == b) {
            return a;
        }

        for (int i = __lg(N); ~i; --i) {
            if (anc[a][i] != anc[b][i]) {
                a = anc[a][i];
                b = anc[b][i];
            }
        }
        return parent[a];
    }

    int distance(int a, int b) {
        if (anc.empty()) {
            build_lca();
        }
        return level[a] + level[b] - 2 * level[lca(a, b)];
    }

    void solve() {
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
