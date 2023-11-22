// Mohamed_Waheed_
#include <bits/stdc++.h>
#define ll long long
using namespace std;

template <class T>
class segment_tree // 1 index
{
private:
    struct node
    {
        ll skip = 0;
        node() { skip = 1; }

        node(T x)
        {
        }
    };

    ll size = 1;
    vector<node> seg;
    vector<T> buildseg;

    node merge(node a, node b)
    {
        if (a.skip)
            return b;
        if (b.skip)
            return a;
        node ret;
        ret.skip = 0;

        return ret;
    }

    void build(ll x, ll lx, ll rx)
    {
        if (rx - lx == 0)
        {
            if (lx < buildseg.size())
                seg[x] = node(buildseg[lx]);
            return;
        }
        ll m = (lx + rx) / 2;
        build(2 * x + 1, lx, m);
        build(2 * x + 2, m + 1, rx);
        seg[x] = merge(seg[2 * x + 1], seg[2 * x + 2]);
    }

    void update(ll ind, T value, ll x, ll lx, ll rx)
    {
        if (rx - lx == 0)
        {
            seg[x] = node(value);
            return;
        }
        ll m = (lx + rx) / 2;
        if (ind <= m)
            update(ind, value, 2 * x + 1, lx, m);
        else
            update(ind, value, 2 * x + 2, m + 1, rx);
        seg[x] = merge(seg[2 * x + 1], seg[2 * x + 2]);
    }

    node query(ll l, ll r, ll x, ll lx, ll rx)
    {
        if (l > rx || r < lx)
            return node();
        if (l <= lx && rx <= r)
            return seg[x];
        ll m = (lx + rx) / 2;
        node s1 = query(l, r, 2 * x + 1, lx, m);
        node s2 = query(l, r, 2 * x + 2, m + 1, rx);
        return merge(s1, s2);
    }

public:
    segment_tree(vector<T> a)
    {
        buildseg = a;
        while (size < a.size())
            size *= 2;
        seg.assign(2 * size, node());
        build(0, 0, size - 1);
    }

    void update(ll ind, T value)
    {
        update(--ind, value, 0, 0, size - 1);
        buildseg[ind] = value;
    }

    node query(ll l, ll r)
    {
        return query(--l, --r, 0, 0, size - 1);
    }
};

void Main()
{
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
