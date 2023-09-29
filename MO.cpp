// Mohamed_Waheed_
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll n, q, SQ, res;

struct query
{
    ll l, r, q_indx, b_indx;

    query() {}
    query(ll l, ll r, ll q_indx)
    {
        this->l = l - 1;
        this->r = r - 1;
        this->q_indx = q_indx;
        b_indx = l / SQ;
    }

    bool operator<(query x)
    {
        if (b_indx != x.b_indx)
            return b_indx < x.b_indx;
        return r < x.r;
    }
};

vector<query> Q;
vector<ll> v, ans;

void add(ll ind)
{
}

void remove(ll ind)
{
}

void MO_process()
{
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
}

void Main()
{
    cin >> n >> q;
    SQ = sqrt(n);
    ans.clear(), ans.resize(q, 0);
    v.clear(), v.resize(n, 0);
    Q.clear(), Q.resize(q);

    for (auto &it : v)
        cin >> it;

    for (ll i = 0; i < q; i++)
    {
        ll l, r;
        cin >> l >> r;
        Q[i] = query(l, r, i);
    }

    MO_process();

    for (ll i = 0; i < q; i++)
    {
        cout << ans[i] << '\n';
    }
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
