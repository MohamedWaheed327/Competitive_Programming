// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

class dr_string {
private:
    long long M1 = 1e9 + 7, M2 = 1e9 + 9, B1 = 31, B2 = 37;
    vector<int> pow1, pow2, hash1, hash2;

public:
    dr_string(const string &s) {
        int N = s.size() + 1;
        pow1.resize(N), pow2.resize(N);
        hash1.resize(N), hash2.resize(N);
        pow1[0] = pow2[0] = 1;
        hash1[0] = hash2[0] = 0;

        for (int i = 1; i < N; i++) {
            pow1[i] = (pow1[i - 1] * B1) % M1;
            pow2[i] = (pow2[i - 1] * B2) % M2;
            hash1[i] = (hash1[i - 1] * B1 + s[i - 1]) % M1;
            hash2[i] = (hash2[i - 1] * B2 + s[i - 1]) % M2;
        }
    }

    pair<int, int> substr(int l, int r) {
        return {((hash1[r + 1] - 1LL * hash1[l] * pow1[r - l + 1]) % M1 + M1) % M1,
                ((hash2[r + 1] - 1LL * hash2[l] * pow2[r - l + 1]) % M2 + M2) % M2};
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
