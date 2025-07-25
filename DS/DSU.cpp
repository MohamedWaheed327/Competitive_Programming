// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

class DSU {
private:
    vector<int> par, sz;

    int find_par(int node) {
        if (node == par[node]) {
            return node;
        }
        return par[node] = find_par(par[node]);
    }

public:
    DSU(int n) {
        par.resize(n + 1);
        sz.assign(n + 1, 1);
        iota(par.begin(), par.end(), 0);
    }

    bool same_set(int a, int b) {
        return find_par(a) == find_par(b);
    }

    void merge(int a, int b) {
        a = find_par(a);
        b = find_par(b);
        if (a != b) {
            if (sz[a] < sz[b]) {
                swap(a, b);
            }
            par[b] = a;
            sz[a] += sz[b];
        }
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
