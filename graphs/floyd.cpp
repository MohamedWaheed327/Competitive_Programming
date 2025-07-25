// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

class floyd {
private:
    const int64_t INF = 1e18;
    vector<vector<int64_t>> dp, next;

public:
    floyd(const auto &g) {
        int n = (int)g.size() - 1;
        dp.assign(n + 1, vector<int64_t>(n + 1, INF));
        next.assign(n + 1, vector<int64_t>(n + 1));

        for (int from = 1; from <= n; ++from) {
            dp[from][from] = 0;
            for (auto &[to, cost] : g[from]) {
                if (dp[from][to] > cost) {
                    dp[from][to] = cost;
                    next[from][to] = to;
                }
            }
        }

        for (int k = 1; k <= n; ++k) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    if (dp[i][k] + dp[k][j] < dp[i][j]) {
                        dp[i][j] = dp[i][k] + dp[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }

        for (int k = 1; k <= n; ++k) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    if (dp[i][k] + dp[k][j] < dp[i][j]) {
                        dp[i][j] = -INF;
                    }
                }
            }
        }
    }

    int64_t dis(int a, int b) {
        return dp[a][b];
    }

    vector<int> get_path(int a, int b) {
        if (dis(a, b) == INF || dis(a, b) == -INF) {
            return {};
        }

        vector<int> ret = {a};
        while (ret.back() != b) {
            ret.push_back(next[ret.back()][b]);
        }
        return ret;
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
