// Mohamed_Waheed_
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class MO // 1 index
{
private:
    struct query
    {
        ll l, r, q_indx, b_indx;
        query() {}
        query(ll l, ll r, ll q_indx, ll b_indx)
        {
            this->l = l;
            this->r = r;
            this->q_indx = q_indx;
            this->b_indx = b_indx;
        }
        bool operator<(query x)
        {
            if (b_indx != x.b_indx)
                return b_indx < x.b_indx;
            return r < x.r;
        }
    };

    ll q = 0, SQ;
    vector<ll> v;
    vector<query> Q;

    ll res = 0;
    vector<ll> freq = vector<ll>(1e6 + 1, 0);
    void add(ll ind)
    {
        if (!freq[v[ind]])
            res++;
        freq[v[ind]]++;
    }
    void remove(ll ind)
    {
        freq[v[ind]]--;
        if (!freq[v[ind]])
            res--;
    }

public:
    MO(vector<ll> a)
    {
        v = a;
        SQ = sqrt(a.size());
    }

    void add_query(ll l, ll r)
    {
        Q.push_back(query(--l, --r, q++, l / SQ));
    }

    void mo_process()
    {
        vector<ll> ans(q, 0);

        sort(Q.begin(), Q.end());
        ll r = 0, l = 1;
        for (ll i = 0; i < q; i++)
        {
            while (r > Q[i].r)
                remove(r--);
            while (r < Q[i].r)
                add(++r);
            while (l > Q[i].l)
                add(--l);
            while (l < Q[i].l)
                remove(l++);
            ans[Q[i].q_indx] = res;
        }

        for (ll i = 0; i < q; i++)
        {
            cout << ans[i] << "\n "[i == q - 1];
        }
    }
};

void Main()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    for (auto &it : v)
        cin >> it;

    MO m(v);

    ll q;
    cin >> q;
    while (q--)
    {
        ll l, r;
        cin >> l >> r;
        m.add_query(l, r); // number of distinct elements form l to r
    }
    m.mo_process();
}
/*




*/
signed main()
{
    ios_base::sync_with_stdio(false), cout.tie(NULL), cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ll T = 1;
    // cin >> T;
    for (ll i = 1; i <= T; i++)
    {
        Main();
        cout << '\n';
    }
    return 0;
}
