// Mohamed_Waheed_
#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct sparse_table // 1 index
{
private:
    ll n;
    vector<ll> v, LOG;
    vector<vector<ll>> dp;

    ll merge(ll a, ll b)
    {
        return max(a, b);
    }

    void preCount()
    {
        for (ll i = 2; i <= n; i++)
        {
            LOG[i] = LOG[i >> 1] + 1;
        }
    }

    void build()
    {
        for (ll i = 0; i < n; i++)
        {
            dp[i][0] = v[i];
        }
        for (ll mask = 1; (1 << mask) <= n; mask++)
        {
            for (ll i = 0; i + (1 << mask) <= n; i++)
            {
                dp[i][mask] = merge(dp[i][mask - 1], dp[i + (1 << (mask - 1))][mask - 1]);
            }
        }
    }

public:
    sparse_table(vector<ll> v)
    {
        this->v = v;
        n = v.size();
        LOG.assign(n + 1, 0);
        dp.assign(n + 1, vector<ll>(22, 0));
        preCount();
        build();
    }

    ll query(ll l, ll r)
    {
        l--, r--;
        ll mask = LOG[r - l + 1];
        return merge(dp[l][mask], dp[r - (1 << mask) + 1][mask]);
    }
};

void Main()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    for (auto &it : v)
        cin >> it;

    sparse_table st(v);

    ll q;
    cin >> q;
    while (q--)
    {
        ll l, r;
        cin >> l >> r;
        cout << st.query(l, r) << '\n';
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
