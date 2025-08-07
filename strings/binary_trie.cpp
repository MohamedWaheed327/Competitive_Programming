// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;


template <int LOG = 62>
class binary_trie {
private:
    struct node {
        int64_t cnt = 0;
        int child[2] = {-1, -1};
    };
    vector<node> tree = vector<node>(1);

    bool valid(int node) { return node != -1 && 0 < tree[node].cnt; }

public:
    void insert(int64_t x, int cnt = 1) {
        int cur = 0;
        tree[cur].cnt += cnt;
        for (int bit = LOG; ~bit; --bit) {
            int to = (x >> bit) & 1;
            if (tree[cur].child[to] == -1) {
                tree[cur].child[to] = tree.size();
                tree.emplace_back();
            }
            cur = tree[cur].child[to];
            tree[cur].cnt += cnt;
        }
    }

    int64_t max_xor(int64_t x) {
        int64_t cur = 0, ret = 0;
        for (int bit = LOG; ~bit; bit--) {
            int to = (x >> bit) & 1;
            if (valid(tree[cur].child[!to])) {
                cur = tree[cur].child[!to];
                ret += !to * (1LL << bit);
            }
            else if (valid(tree[cur].child[to])) {
                cur = tree[cur].child[to];
                ret += to * (1LL << bit);
            }
        }
        return x ^ ret;
    }

    int64_t min_xor(int64_t x) {
        return ~max_xor(~x);
    }

    int64_t xor_less_than_k(int64_t x, int64_t k) {
        int64_t cur = 0, ret = 0;
        for (int bit = LOG; ~bit; --bit) {
            if (!valid(cur)) return ret;
            int to = (x >> bit) & 1;
            if ((k >> bit) & 1) {
                if (valid(tree[cur].child[to])) {
                    ret += tree[tree[cur].child[to]].cnt;
                }
                cur = tree[cur].child[!to];
            }
            else {
                cur = tree[cur].child[to];
            }
        }
        return ret;
    }

    int64_t xor_greater_equal_to_k(int64_t x, int64_t k) {
        return tree[0].cnt - xor_less_than_k(x, k);
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
