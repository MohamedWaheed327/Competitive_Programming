// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

class suffix_array {
private:
    vector<vector<long long>> dp;
    void build_sparse() {
        if (dp.size()) {
            return;
        }
        int n = lcp_.size(), lg = __lg(n);
        dp.resize(lg + 1, vector<long long>(n));

        for (int i = 0; i < n; ++i) {
            dp[0][i] = lcp_[i];
        }

        for (int j = 1; j <= lg; j++) {
            for (int i = 0; i + (1 << (j - 1)) < n; i++) {
                dp[j][i] = min(dp[j - 1][i], dp[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    long long query(int l, int r) {
        int lg = 32 - __builtin_clz(r - l + 1) - 1;
        return min(dp[lg][l], dp[lg][r - (1 << lg) + 1]);
    }

public:
    vector<int> suf, group, lcp_;
    suffix_array(string s) {
        int n = s.size();
        s += ' ';
        suf = group = vector<int>(n + 1);
        iota(suf.begin(), suf.end(), 0);
        sort(suf.begin(), suf.end(), [&](int i, int j) {
            return s[i] < s[j];
        });
        for (int i = 1; i <= n; ++i) {
            group[suf[i]] = group[suf[i - 1]] + (s[suf[i]] != s[suf[i - 1]]);
        }

        vector<int> cnt, arr, ptr, newG;
        int k = 1;
        auto sort = [&](int x) {
            cnt = arr = ptr = cnt = vector<int>(n + 1);
            for (int i = 0; i <= n; ++i) {
                cnt[group[(suf[i] + x) % (n + 1)]]++;
            }

            int sum = 0;
            for (int i = 0; i <= n; ++i) {
                ptr[i] = sum;
                sum += cnt[i];
            }

            for (int i = 0; i <= n; ++i) {
                arr[ptr[group[(suf[i] + x) % (n + 1)]]++] = suf[i];
            }
            suf = arr;
        };

        while (group[suf[n]] != n) {
            sort(k);
            sort(0);
            newG = group;
            for (int i = 1; i <= n; ++i) {
                newG[suf[i]] = newG[suf[i - 1]] + (group[suf[i]] != group[suf[i - 1]] || group[suf[i] + k] != group[suf[i - 1] + k]);
            }
            group = newG;
            k <<= 1;
        }

        k = 0;
        lcp_ = vector<int>(n);
        for (int i = 0; i < n; ++i) {
            int pos = group[i], j = suf[pos - 1];
            while (s[i + k] == s[j + k]) {
                ++k;
            }
            lcp_[pos - 1] = k;
            k = max(k - 1, 0);
        }
    }

    int lcp(int i, int j) {
        i = group[i], j = group[j];
        if (i > j) {
            swap(i, j);
        }
        if (i == j) {
            return (int)lcp_.size() - suf[i];
        }
        if (i + 1 == j) {
            return lcp_[i];
        }
        build_sparse();
        return query(i, j - 1);
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
