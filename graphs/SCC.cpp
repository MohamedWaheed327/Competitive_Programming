// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

template <int base = 1>
class SCC {
private:
    stack<int> st;
    int n, id = 1, comp_c;
    const vector<vector<int>> &g;
    vector<vector<int>> dag, comps;
    vector<int> on_stack, low_link, ids, in_deg;

    void dfs(int node) {
        st.push(node), on_stack[node] = true;
        low_link[node] = ids[node] = id++;

        for (auto it : g[node]) {
            if (ids[it] == -1) {
                dfs(it);
            }
            if (on_stack[it]) {
                low_link[node] = low_link[it] = min(low_link[node], low_link[it]);
            }
        }

        if (ids[node] == low_link[node]) {
            while (true) {
                int cur = st.top();
                st.pop(), on_stack[cur] = false;

                low_link[cur] = low_link[node];
                if (cur == node) {
                    break;
                }
            }
        }
    }

public:
    SCC() = default;
    SCC(const vector<vector<int>> &_g) : g(_g) {
        n = (int)g.size() - 1;
        ids = vector(n + 1, -1);
        on_stack = low_link = vector(n + 1, 0);

        for (int i = base; i <= n; ++i) {
            if (ids[i] == -1) {
                dfs(i);
            }
        }

        set<int> s(low_link.begin() + base, low_link.end());
        vector<int> c(s.begin(), s.end());
        comp_c = c.size();
        for (int i = base; i <= n; ++i) {
            low_link[i] = lower_bound(c.begin(), c.end(), low_link[i]) - c.begin();
        }
    }

    int components_cnt() {
        return comp_c;
    }

    int component(int node) {
        return low_link[node];
    }

    bool same_component(int u, int v) {
        return component(u) == component(v);
    }

    vector<vector<int>> &compress() {
        if (dag.empty()) {
            in_deg.assign(components_cnt(), 0);
            dag.resize(components_cnt());
            for (int i = base; i <= n; ++i) {
                for (auto it : g[i]) {
                    if (!same_component(i, it)) {
                        dag[component(i)].push_back(component(it));
                        in_deg[component(it)]++;
                    }
                }
            }
        }
        return dag;
    }

    vector<vector<int>> &get_components() {
        if (comps.empty()) {
            comps.resize(components_cnt());
            for (int i = base; i <= n; ++i) {
                comps[component(i)].push_back(i);
            }
        }
        return comps;
    }

    bool is_head(int comp) {
        compress();
        return !in_deg[comp];
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
