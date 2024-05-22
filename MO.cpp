// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

template <class M>
class MO {
private:
    struct query {
        int l, r, q_indx;
    };

    int q, SQ;
    vector<M> v;
    vector<query> Q;

    long long res = 0;
    void add(int ind) {
        res += v[ind];
    }

    void remove(int ind) {
        res -= v[ind];
    }

    long long calc(...) {
        return res;
    }

public:
    MO(const vector<M> &v) {
        q = 0;
        this->v = v;
        SQ = sqrt(v.size());
    }

    template <class... T>
    void add_query(int l, int r, T &...x) {
        Q.push_back({l, r, q++, x...});
    }

    void mo_process() {
        vector<long long> ans(q);

        sort(Q.begin(), Q.end(), [&](query a, query b) {
            return pair{a.l / SQ, a.r} < pair{b.l / SQ, b.r};
        });

        int l = 1, r = 0;
        for (auto [L, R, q_indx] : Q) {
            while (r > R)
                remove(r--);
            while (r < R)
                add(++r);
            while (l > L)
                add(--l);
            while (l < L)
                remove(l++);
            ans[q_indx] = calc();
        }

        for (auto it : ans) {
            cout << it << '\n';
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
