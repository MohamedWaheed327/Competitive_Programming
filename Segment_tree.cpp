// Mohamed_Waheed_
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class segment_tree // 1 index
{
private:
    struct node
    {
        ll mn, mx;
        node() { mn = LLONG_MAX, mx = LLONG_MIN; }
        node(ll x)
        {
            mn = x;
            mx = x;
        }
    };

    ll size = 1;
    node SKIP;
    vector<node> seg;
    vector<ll> buildseg;

    node merge(node a, node b)
    {
        node ret;
        ret.mn = min(a.mn, b.mn);
        ret.mx = max(a.mx, b.mx);
        return ret;
    }

    void build(ll x, ll lx, ll rx)
    {
        if (rx - lx == 1)
        {
            if (lx < buildseg.size())
                seg[x] = node(buildseg[lx]);
            return;
        }
        ll m = (lx + rx) / 2;
        build(2 * x + 1, lx, m);
        build(2 * x + 2, m, rx);
        seg[x] = merge(seg[2 * x + 1], seg[2 * x + 2]);
    }

    void update(ll ind, ll value, ll x, ll lx, ll rx)
    {
        if (rx - lx == 1)
        {
            seg[x] = node(value);
            return;
        }
        ll m = (lx + rx) / 2;
        if (ind < m)
            update(ind, value, 2 * x + 1, lx, m);
        else
            update(ind, value, 2 * x + 2, m, rx);
        seg[x] = merge(seg[2 * x + 1], seg[2 * x + 2]);
    }

    node query(ll l, ll r, ll x, ll lx, ll rx)
    {
        if (l > rx || r < lx)
            return SKIP;
        if (l <= lx && rx <= r)
            return seg[x];
        ll m = (lx + rx) / 2;
        node s1 = query(l, r, 2 * x + 1, lx, m);
        node s2 = query(l, r, 2 * x + 2, m + 1, rx);
        return merge(s1, s2);
    }

public:
    segment_tree(vector<ll> a)
    {
        buildseg = a;
        while (size < a.size())
            size *= 2;
        seg.assign(2 * size, SKIP);
        build(0, 0, size);
    }

    void update(ll ind, ll value)
    {
        update(--ind, value, 0, 0, size);
        buildseg[ind] = value;
    }

    node query(ll l, ll r)
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
        ll l, r;
        cin >> l >> r;
        cout << st.query(l, r).mn << " " << st.query(l, r).mx << '\n';
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
