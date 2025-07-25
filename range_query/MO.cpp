// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

template <class M>
class MO {
private:
    struct query {
        int l, r, q_indx;
    };

    vector<M> v;
    vector<query> Q;

    int64_t res = 0;
    void add(int ind) {
        res += v[ind];
    }

    void remove(int ind) {
        res -= v[ind];
    }

    int64_t calc(...) {
        return res;
    }

public:
    MO(const vector<M> &v) : v(v) {}

    void add_query(int l, int r) {
        Q.push_back({l, r, Q.size()});
    }

    vector<int64_t> get_ans() {
        int SQ = sqrt(v.size());
        sort(Q.begin(), Q.end(), [&](query a, query b) {
            return pair{a.l / SQ, a.r} < pair{b.l / SQ, b.r};
        });

        vector<int64_t> ans(Q.size());
        int l = 0, r = -1;
        for (auto [L, R, q_indx] : Q) {
            while (r < R)
                add(++r);
            while (l > L)
                add(--l);
            while (r > R)
                remove(r--);
            while (l < L)
                remove(l++);
            ans[q_indx] = calc();
        }

        return ans;
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
