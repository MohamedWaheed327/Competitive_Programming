// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> centroid_decomp(vector<vector<int>> &g) {
    int n = (int)g.size() - 1;
    vector<int> sz(n + 1);
    vector<bool> vis(n + 1, false);
    vector<vector<int>> ret(n + 1);

    function<int(int, int)> find_size = [&](int node, int par) {
        sz[node] = 1;
        for (auto &it : g[node]) {
            if (it != par && !vis[it]) {
                sz[node] += find_size(it, node);
            }
        }
        return sz[node];
    };

    function<int(int, int, int)> find_centroid = [&](int node, int par, int cur_sz) {
        for (auto &it : g[node]) {
            if (it != par && !vis[it] && sz[it] > cur_sz / 2) {
                return find_centroid(it, node, cur_sz);
            }
        }
        return node;
    };

    function<void(int, int)> init_centriod = [&](int node, int par) {
        int c = find_centroid(node, -1, find_size(node, -1));
        vis[c] = true;
        ret[c].push_back(par);
        ret[par].push_back(c);

        for (auto &it : g[c]) {
            if (!vis[it]) {
                init_centriod(it, c);
            }
        }
    };

    vis[1] = true;
    for (auto &it : g[1]) {
        init_centriod(it, 1);
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
