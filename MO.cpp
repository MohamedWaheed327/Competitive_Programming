// Mohamed_Waheed_
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class MO {
private:
    struct query {
        int l, r, q_indx;
    };

    int q = 0, SQ;
    vector<long long> v;
    vector<query> Q;

    ll res = 0;
    int freq[100] = {};

    void add(int ind) {
        if (!freq[v[ind]])
            res++;
        freq[v[ind]]++;
    }

    void remove(int ind) {
        freq[v[ind]]--;
        if (!freq[v[ind]])
            res--;
    }

public:
    template <class M>
    MO(const vector<M> &v) {
        this->v = v;
        SQ = sqrt(v.size());
    }

    template <class... M>
    void add_query(int l, int r, M &...x) {
        Q.push_back({l, r, q++, x...});
    }

    void mo_process() {
        vector<long long> ans(q);

        sort(Q.begin(), Q.end(), [&](query a, query b) {
            if (a.l / SQ != b.l / SQ)
                return a.l / SQ < b.l / SQ;
            return a.r < b.r;
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
            ans[q_indx] = res;
        }

        for (auto it : ans) {
            cout << it << '\n';
        }
    }
};

void Main() {
    ll n;
    cin >> n;
    vector<ll> v(n);
    for (auto &it : v) {
        cin >> it;
    }

    MO m(v);

    ll q;
    cin >> q;
    while (q--) {
        ll l, r;
        cin >> l >> r;
        m.add_query(--l, --r); // number of distinct elements form l to r
    }
    m.mo_process();
}
/*





*/
signed main() {
    ios_base::sync_with_stdio(false), cout.tie(NULL), cin.tie(NULL);
    ll T = 1;
    // cin >> T;
    for (ll i = 1; i <= T; i++) {
        Main();
        cout << '\n';
    }
    return 0;
}
