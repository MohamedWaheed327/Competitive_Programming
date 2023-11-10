// Mohamed_Waheed_
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class segment_tree
{
private:
    struct node
    {
        ll mx;
        node()
        {
            mx = LLONG_MIN;
        }
        node(ll x)
        {
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
        update(ind, value, 0, 0, size);
        buildseg[ind] = value;
    }

    ll query(ll l, ll r)
    {
        if (r < l)
            return 0;
        return query(l, r, 0, 0, size - 1).mx;
    }
};

vector<ll> compress(vector<ll> &v)
{
    ll n = v.size();
    vector<pair<ll, ll>> p;
    for (ll i = 0; i < n; i++)
    {
        p.push_back({v[i], i});
    }
    sort(p.begin(), p.end());

    vector<ll> real(n);
    ll last = p[0].first, nxt = 0;
    for (auto [F, S] : p)
    {
        if (last < F)
            nxt++;
        last = F;
        real[nxt] = F;
        v[S] = nxt;
    }
    return real;
}

vector<ll> lis(vector<ll> v)
{
    auto real = compress(v);
    ll n = v.size();
    vector<ll> dp(n, 0);
    segment_tree st(dp);

    struct x {  ll idx, old; };
    vector<x> history;

    for (auto it : v)
    {
        x temp;
        temp.idx = it;
        temp.old = dp[it];
        history.push_back(temp);
        dp[it] = max(dp[it], st.query(0, it - 1) + 1);
        st.update(it, dp[it]);
    }

    ll mx = *max_element(dp.begin(), dp.end()), last = LLONG_MAX;
    vector<ll> ret;
    for (ll i = n - 1; i >= 0; i--)
    {
        if (mx == dp[v[i]] && last > v[i])
        {
            mx--;
            last = v[i];
            ret.push_back(v[i]);
        }
        dp[history.back().idx] = history.back().old;
        history.pop_back();
    }
    reverse(ret.begin(), ret.end());
    for (auto &it : ret)
        it = real[it];
    return ret;
}

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
