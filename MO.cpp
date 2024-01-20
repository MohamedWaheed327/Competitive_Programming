// Mohamed_Waheed_
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class MO {
private:
    struct query {
        int l, r, q_indx, b_indx;
        query() {}
        query(int l, int r, int q_indx, int b_indx) {
            this->l = l;
            this->r = r;
            this->q_indx = q_indx;
            this->b_indx = b_indx;
        }
    };

    int q = 0, SQ;
    vector<ll> v;
    vector<query> Q;

    ll res = 0;
    int freq[100] = {};

    void add(ll ind) {
        if (!freq[v[ind]])
            res++;
        freq[v[ind]]++;
    }

    void remove(ll ind) {
        freq[v[ind]]--;
        if (!freq[v[ind]])
            res--;
    }

public:
    template <class M>
    MO(vector<M> v) {
        this->v = v;
        SQ = sqrt(v.size());
    }

    template <class... M>
    void add_query(int l, int r, M... x) {
        Q.push_back(query(l, r, q++, l / SQ, x...));
    }

    void mo_process() {
        vector<ll> ans(q);

        sort(Q.begin(), Q.end(), [&](query a, query b) {
            if (a.b_indx != b.b_indx)
                return a.b_indx < b.b_indx;
            return a.r < b.r;
        });

        ll l = 1, r = 0;
        for (auto it : Q) {
            while (r > it.r)
                remove(r--);
            while (r < it.r)
                add(++r);
            while (l > it.l)
                add(--l);
            while (l < it.l)
                remove(l++);
            ans[it.q_indx] = res;
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
