// Mohamed_Waheed_
#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct SQblocks // 1 index
{
private:
    ll SQ;
    vector<ll> v;
    vector<vector<ll>> block;

    void sqdecompostion()
    {
        for (ll i = 0; i < v.size(); i++)
        {
            block[i / SQ].push_back(v[i]);
        }
        for (ll i = 0; i < SQ; i++)
        {
            sort(block[i].begin(), block[i].end());
        }
    }

public:
    SQblocks(vector<ll> a)
    {
        SQ = sqrt(a.size()) + 1;
        v = a;
        block.resize(SQ);
        sqdecompostion();
    }

    void update(ll ind, ll val)
    {
        ind--;
        ll it = lower_bound(block[ind / SQ].begin(), block[ind / SQ].end(), v[ind]) - block[ind / SQ].begin();
        block[ind / SQ][it] = val;
        sort(block[ind / SQ].begin(), block[ind / SQ].end());
        v[ind] = val;
    }

    ll query(ll l, ll r)
    {
        l--, r--;
        ll ret = LLONG_MAX;
        while (l <= r)
        {
            if (l % SQ || r - l < SQ)
            {
                ret = min(ret, v[l++]);
            }
            else
            {
                ret = min(ret, block[l / SQ][0]);
                l += SQ;
            }
        }
        return ret;
    }
};

void Main()
{
    ll n, q;
    cin >> n >> q;
    vector<ll> v(n);
    for (auto &it : v)
        cin >> it;

    SQblocks s(v);

    while (q--)
    {
        ll op;
        cin >> op;
        if (op == 1)
        {
            ll ind, val;
            cin >> ind >> val;
            s.update(ind, val);
        }
        else
        {
            ll l, r;
            cin >> l >> r;
            cout << s.query(l, r) << '\n';
        }
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
