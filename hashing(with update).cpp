// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

class dr_string {
private:
    static const long long mod = (1LL << 61) - 1;
    static long long base;
    static vector<long long> pw, powsum;

    class segment_tree {
    private:
        struct node {
            int len, lazy = -1;
            long long hash;

            void apply(int lx, int rx, long long val = 0) {
                lazy = val;
                len = rx - lx + 1;
                hash = val * (__int128_t)powsum[len] % mod;
            }

            void merge(const node &a, const node &b) {
                len = a.len + b.len;
                hash = (a.hash + b.hash * (__int128_t)pw[a.len]) % mod;
            }

            bool operator==(const node &x) {
                return hash == x.hash;
            }
        };

        inline void propagate(int x, int lx, int rx) {
            int mid = lx + rx >> 1;
            int left = x + 1;
            int right = x + (mid - lx + 1 << 1);
            if (~seg[x].lazy) {
                seg[left].apply(lx, mid, seg[x].lazy);
                seg[right].apply(mid + 1, rx, seg[x].lazy);
                seg[x].lazy = -1;
            }
        }

        int size;
        vector<node> seg;

        template <class... M>
        void build(int x, int lx, int rx, const vector<M> &...build_seg) {
            if (lx == rx) {
                seg[x].apply(lx, rx, build_seg[lx]...);
                return;
            }
            int mid = lx + rx >> 1;
            int left = x + 1;
            int right = x + (mid - lx + 1 << 1);
            build(left, lx, mid, build_seg...);
            build(right, mid + 1, rx, build_seg...);
            seg[x].merge(seg[left], seg[right]);
        }

        template <class... M>
        void update(int x, int lx, int rx, int l, int r, const M &...value) {
            if (l <= lx && rx <= r) {
                seg[x].apply(lx, rx, value...);
                return;
            }
            propagate(x, lx, rx);
            int mid = lx + rx >> 1;
            int left = x + 1;
            int right = x + (mid - lx + 1 << 1);
            if (l <= mid) {
                update(left, lx, mid, l, r, value...);
            }
            if (r >= mid + 1) {
                update(right, mid + 1, rx, l, r, value...);
            }
            seg[x].merge(seg[left], seg[right]);
        }

        node query(int x, int lx, int rx, int l, int r) {
            if (l <= lx && rx <= r) {
                return seg[x];
            }
            propagate(x, lx, rx);
            int mid = lx + rx >> 1;
            int left = x + 1;
            int right = x + (mid - lx + 1 << 1);
            node ret;
            if (r < mid + 1) {
                return query(left, lx, mid, l, r);
            }
            else if (mid < l) {
                return query(right, mid + 1, rx, l, r);
            }
            else {
                ret.merge(query(left, lx, mid, l, r), query(right, mid + 1, rx, l, r));
            }
            return ret;
        }

    public:
        segment_tree() {}

        template <class... M>
        segment_tree(const vector<M> &...build_seg) {
            size = (build_seg.size(), ...);
            seg.resize(2 * size - 1);
            build(0, 0, size - 1, build_seg...);
        }

        template <class... M>
        void update(int l, int r, const M &...value) {
            update(0, 0, size - 1, l, r, value...);
        }

        node query(int l, int r) {
            return query(0, 0, size - 1, l, r);
        }
    };

    int size;
    segment_tree A, B;

public:
    dr_string(string s) {
        size = s.size();
        while (pw.size() <= size) {
            powsum.push_back((pw.back() + powsum.back()) % mod);
            pw.push_back((__int128_t)pw.back() * base % mod);
        }
        A = segment_tree(vector<char>(s.begin(), s.end()));
        reverse(s.begin(), s.end());
        B = segment_tree(vector<char>(s.begin(), s.end()));
    }

    void update(int l, int r, char val) {
        A.update(l, r, val);
        B.update(size - r - 1, size - l - 1, val);
    }

    auto substr(int l, int r) {
        return A.query(l, r);
    }

    auto substr_rev(int l, int r) {
        return B.query(size - r - 1, size - l - 1);
    }

    bool is_palindrome(int l, int r) {
        return substr(l, r) == substr_rev(l, r);
    }
};
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long dr_string::base = (mod >> 2) + rng() % (mod >> 1);
vector<long long> dr_string::pw = {1}, dr_string::powsum = {0};

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
