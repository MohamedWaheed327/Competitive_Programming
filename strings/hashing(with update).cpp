// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

template <class node>
class segment_tree {
private:
    int size;
    vector<node> seg;

    template <class... M>
    void build(int x, int lx, int rx, const vector<M> &...a) {
        if (lx == rx) {
            return seg[x].apply(lx, rx, a[lx]...);
        }
        int mid = lx + rx >> 1;
        int left = x + 1;
        int right = x + 2 * (mid - lx + 1);
        build(left, lx, mid, a...);
        build(right, mid + 1, rx, a...);
        seg[x].merge(seg[left], seg[right]);
    }

    template <class... M>
    void modify(int x, int lx, int rx, int l, int r, const M &...value) {
        if (l <= lx && rx <= r) {
            return seg[x].apply(lx, rx, value...);
        }
        int mid = lx + rx >> 1;
        int left = x + 1;
        int right = x + 2 * (mid - lx + 1);
        seg[x].propagate(seg[left], seg[right], lx, rx, mid);
        if (l <= mid) {
            modify(left, lx, mid, l, r, value...);
        }
        if (mid + 1 <= r) {
            modify(right, mid + 1, rx, l, r, value...);
        }
        seg[x].merge(seg[left], seg[right]);
    }

    node query(int x, int lx, int rx, int l, int r) {
        if (l <= lx && rx <= r) {
            return seg[x];
        }
        int mid = lx + rx >> 1;
        int left = x + 1;
        int right = x + 2 * (mid - lx + 1);
        seg[x].propagate(seg[left], seg[right], lx, rx, mid);
        if (r < mid + 1) {
            return query(left, lx, mid, l, r);
        }
        if (mid < l) {
            return query(right, mid + 1, rx, l, r);
        }
        node ret;
        ret.merge(query(left, lx, mid, l, r), query(right, mid + 1, rx, l, r));
        return ret;
    }

    pair<int, node> find(int x, int lx, int rx, node *last, int l, int r, int dir, const auto &F) {
        if (l <= lx && rx <= r) {
            node cur_node = seg[x];
            if (last) {
                dir ? cur_node.merge(*last, seg[x]) : cur_node.merge(seg[x], *last);
            }
            if (!F(cur_node)) return {-1, cur_node};
            if (lx == rx) return {lx, cur_node};
        }
        int mid = lx + rx >> 1;
        int left = x + 1;
        int right = x + 2 * (mid - lx + 1);
        seg[x].propagate(seg[left], seg[right], lx, rx, mid);
        if (r < mid + 1) {
            return find(left, lx, mid, last, l, r, dir, F);
        }
        if (mid < l) {
            return find(right, mid + 1, rx, last, l, r, dir, F);
        }
        auto [idx, nd] = (dir ? find(left, lx, mid, last, l, r, dir, F) : find(right, mid + 1, rx, last, l, r, dir, F));
        if (~idx) return {idx, nd};
        return dir ? find(right, mid + 1, rx, &nd, l, r, dir, F) : find(left, lx, mid, &nd, l, r, dir, F);
    }

public:
    template <class... M>
    segment_tree(int n, M... x) : size(n), seg(2 * n) {
        build(0, 0, size - 1, vector<M>(n, x)...);
    }

    template <class... M>
    segment_tree(const vector<M> &...a) : size((a.size(), ...)), seg(2 * size) {
        build(0, 0, size - 1, a...);
    }

    template <class... M>
    void update(int l, int r, const M &...value) {
        modify(0, 0, size - 1, l, r, value...);
    }

    node query(int l, int r) {
        return query(0, 0, size - 1, l, r);
    }

    int find_first(int l, int r, const auto &F) {
        return find(0, 0, size - 1, nullptr, l, r, 1, F).first;
    }

    int find_last(int l, int r, const auto &F) {
        return find(0, 0, size - 1, nullptr, l, r, 0, F).first;
    }
};

class dr_string {
private:
    static const int64_t mod = (1LL << 61) - 1;
    static int64_t base;
    static vector<int64_t> pw, powsum;

    struct node {
        int len, lazy = -1;
        int64_t hash, hash_rev;

        void apply(int lx, int rx, int64_t val = 0) {
            lazy = val;
            len = rx - lx + 1;
            hash = hash_rev = val * (__int128_t)powsum[len] % mod;
        }

        void merge(const node &a, const node &b) {
            len = a.len + b.len;
            hash = (a.hash + b.hash * (__int128_t)pw[a.len]) % mod;
            hash_rev = (a.hash_rev * (__int128_t)pw[b.len] + b.hash_rev) % mod;
        }

        void propagate(node &left, node &right, int lx, int rx, int mid) {
            if (lazy != -1) {
                left.apply(lx, mid, lazy);
                right.apply(mid + 1, rx, lazy);
                lazy = -1;
            }
        }
    };

    segment_tree<node> sg = segment_tree<node>(1);

public:
    dr_string(const auto &a) {
        while (pw.size() <= a.size()) {
            powsum.push_back((pw.back() + powsum.back()) % mod);
            pw.push_back((__int128_t)pw.back() * base % mod);
        }
        sg = segment_tree<node>(vector<int64_t>(a.begin(), a.end()));
    }

    void update(int l, int r, int64_t val) {
        sg.update(l, r, val);
    }

    int64_t substr(int l, int r) {
        return sg.query(l, r).hash;
    }

    int64_t substr_rev(int l, int r) {
        return sg.query(l, r).hash_rev;
    }

    bool is_palindrome(int l, int r) {
        return substr(l, r) == substr_rev(l, r);
    }
};
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int64_t dr_string::base = (mod >> 2) + rng() % (mod >> 1);
vector<int64_t> dr_string::pw = {1}, dr_string::powsum = {0};

void Main(...) {
    int n;
    string s;
    cin >> n >> s;

    dr_string h(s);
    h.update(0, 0, 'x');
    cout << h.is_palindrome(0, n - 1);
}
/*









*/
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) {
        Main(i), cout << '\n';
    }
}
