// Mohamed_Waheed_
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class graph
{
private:
    ll N;
    vector<ll> vis;
    vector<ll> comp;
    vector<ll> is_cyclic;
    vector<ll> num_of_edges;
    vector<vector<pair<ll, ll>>> g;

    void do_dfs(ll node)
    {
        if (vis[node])
            return;
        vis[node] = 1;
        for (auto it : g[node])
        {
            if (!vis[it.first])
            {
                do_dfs(it.first);
            }
        }
    }

    void bfs(vector<ll> parent, ll dis, vector<ll> &mn_dis)
    {
        if (parent.empty())
            return;
        for (auto it : parent)
            mn_dis[it] = dis;
        vector<ll> child;
        for (auto i : parent)
        {
            vis[i] = 1;
            for (auto j : g[i])
            {
                if (!vis[j.first])
                {
                    child.push_back(j.first);
                    vis[j.first] = 1;
                }
            }
        }
        bfs(child, dis + 1, mn_dis);
    }

public:
    graph(ll n)
    {
        N = n + 1;
        g.resize(N);
        num_of_edges.assign(N, 0);
    }
    ~graph() {}

    void add_edge(ll u, ll v, ll cost = 0)
    {
        num_of_edges[u]++;
        g[u].push_back({v, cost});
    }

    void dfs(ll node)
    {
        vis.assign(N, 0);
        do_dfs(node);
    }

    void components()
    {
        ll key = 0;
        vis.assign(N, 0);
        auto check = [&](auto self, ll node)
        {
            if (vis[node])
                return;
            comp[node] = key;
            vis[node] = 1;
            for (auto it : g[node])
            {
                if (!vis[it.first])
                {
                    self(self, it.first);
                }
            }
        };
        for (ll i = 0; i < N; i++)
        {
            if (!vis[i])
            {
                check(check, i);
                key++;
            }
        }
    }

    vector<ll> is_on_cycle()
    {
        auto check = [&](auto self, ll node)
        {
            if (vis[node] || is_cyclic[node] != 1)
                return;
            is_cyclic[node]--;
            vis[node] = 1;
            for (auto it : g[node])
            {
                if (!vis[it.first])
                {
                    is_cyclic[it.first]--;
                    self(self, it.first);
                }
            }
        };
        vis.assign(N, 0);
        is_cyclic = num_of_edges;
        for (ll i = 1; i < N; i++)
            check(check, i);
        return is_cyclic;
    }

    vector<ll> bfs(ll node)
    {
        vector<ll> dis(N, 1e18);
        vis.assign(N, 0);
        bfs({node}, 0, dis);
        return dis;
    }

    vector<ll> dijkstra(ll start)
    {
        vis.assign(N, 0);
        priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
        vector<ll> cheapest_path(N);
        pq.push({0, start});
        while (pq.size())
        {
            ll cost = pq.top().first, node = pq.top().second;
            pq.pop();
            if (vis[node])
                continue;
            vis[node] = 1;
            cheapest_path[node] = cost;
            for (auto [a, b] : g[node])
            {
                if (!vis[a])
                {
                    pq.push({b + cost, a});
                }
            }
        }
        return cheapest_path;
    }
};

void Main()
{
}
/*








*/
signed main()
{
    ios_base::sync_with_stdio(false), cout.tie(NULL), cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ll T = 1;
    // cin >> T;
    for (ll i = 1; i <= T; i++)
    {
        Main();
        cout << '\n';
    }
    return 0;
}
