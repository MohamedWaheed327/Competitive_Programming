// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

const long long mod1 = 1e9 + 7, mod2 = 2e9 + 11, base1 = 31, base2 = 37;
vector<long long> pow1, pow2;
signed init(int N = 1e6) {
    pow1.resize(N + 1);
    pow2.resize(N + 1);
    pow1[0] = pow2[0] = 1;
    for (int i = 1; i <= N; i++) {
        pow1[i] = (base1 * pow1[i - 1]) % mod1;
        pow2[i] = (base2 * pow2[i - 1]) % mod2;
    }
    return 0;
}
int DO_It = init();

class dr_string {
private:
    class segment_tree {
    private:
        struct node {
            int len, h1, h2;

            void apply(int lx, int rx, long long val) {
                len = rx - lx + 1;
                h1 = (val * pow1[1]) % mod1;
                h2 = (val * pow2[1]) % mod2;
            }

            void merge(const node &a, const node &b) {
                len = a.len + b.len;
                h1 = (a.h1 + b.h1 * pow1[a.len]) % mod1;
                h2 = (a.h2 + b.h2 * pow2[a.len]) % mod2;
            }

            bool operator==(const node &x) {
                return (h1 == x.h1 && h2 == x.h2);
            }
        };

        int size;
        vector<node> seg;

        template <class M>
        void update(int x, int lx, int rx, int l, int r, M value) {
            if (l <= lx && rx <= r) {
                seg[x].apply(lx, rx, value);
                return;
            }
            int mid = lx + rx >> 1;
            int left = x + 1;
            int right = x + (mid - lx + 1 << 1);
            if (l <= mid) {
                update(left, lx, mid, l, r, value);
            }
            if (r >= mid + 1) {
                update(right, mid + 1, rx, l, r, value);
            }
            seg[x].merge(seg[left], seg[right]);
        }

        node query(int x, int lx, int rx, int l, int r) {
            if (l <= lx && rx <= r) {
                return seg[x];
            }
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
        segment_tree(int n = 1) {
            size = n;
            seg.resize(2 * size - 1);
        }

        template <class M>
        void update(int ind, M value) {
            update(0, 0, size - 1, ind, ind, value);
        }

        node query(int l, int r) {
            return query(0, 0, size - 1, l, r);
        }
    };

    int size;
    segment_tree A, B;

public:
    dr_string(int n = 1) {
        size = n;
        A = segment_tree(n);
        B = segment_tree(n);
    }

    dr_string(string s) {
        int n = s.size();
        size = n;
        A = segment_tree(n);
        B = segment_tree(n);
        for (int i = 0; i < n; ++i) {
            update(i, s[i]);
        }
    }

    void update(int ind, char val) {
        A.update(ind, val - 'a');
        B.update(size - ind - 1, val - 'a');
    }

    auto substr(int l, int r) {
        return A.query(l, r);
    }

    bool is_palindrome(int l, int r) {
        return A.query(l, r) == B.query(size - r - 1, size - l - 1);
    }

    bool operator==(dr_string s) {
        return A.query(0, size - 1) == s.A.query(0, size - 1);
    }
};

void Main(...) {
    
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
