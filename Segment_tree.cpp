// Mohamed_Waheed_
#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct segment_tree // 1 index
{
    ll size = 1, SKIP = 0;
    vector<ll> seg, buildseg;

    ll merge(ll a, ll b)
    {
        return a + b;
    }

    void build(ll x, ll lx, ll rx)
    {
        if (rx - lx == 1)
        {
            if (lx < buildseg.size())
                seg[x] = buildseg[lx];
            return;
        }
        ll m = (lx + rx) / 2;
        build(2 * x + 1, lx, m);
        build(2 * x + 2, m, rx);
        seg[x] = merge(seg[2 * x + 1], seg[2 * x + 2]);
    }

    segment_tree(vector<ll> a)
    {
        buildseg = a;
        while (size < a.size())
            size *= 2;
        seg.assign(2 * size, SKIP);
        build(0, 0, size);
    }

    void update(ll ind, ll value, ll x, ll lx, ll rx)
    {
        if (rx - lx == 1)
        {
            seg[x] = value;
            return;
        }
        ll m = (lx + rx) / 2;
        if (ind < m)
            update(ind, value, 2 * x + 1, lx, m);
        else
            update(ind, value, 2 * x + 2, m, rx);
        seg[x] = merge(seg[2 * x + 1], seg[2 * x + 2]);
    }

    void update(ll ind, ll value)
    {
        update(--ind, value, 0, 0, size);
        buildseg[ind] = value;
    }

    ll query(ll l, ll r, ll x, ll lx, ll rx)
    {
        if (l > rx || r < lx)
            return SKIP;
        if (l <= lx && rx <= r)
            return seg[x];
        ll m = (lx + rx) / 2;
        ll s1 = query(l, r, 2 * x + 1, lx, m);
        ll s2 = query(l, r, 2 * x + 2, m + 1, rx);
        return merge(s1, s2);
    }

    ll query(ll l, ll r)
    {
        return query(--l, --r, 0, 0, size - 1);
    }
};

void Main()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    for (auto &it : v)
        cin >> it;

    segment_tree st(v);

    ll q;
    cin >> q;
    while (q--)
    {
        ll op;
        cin >> op;
        if (op == 1)
        {
            ll indx, val;
            cin >> indx >> val;
            st.update(indx, val);
        }
        else
        {
            ll l, r;
            cin >> l >> r;
            cout << st.query(l, r) << '\n';
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
