// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

template <int LOG = 62>
class binary_trie {
private:
    struct node {
        int cnt = 0, child[2] = {-1, -1};
    };
    vector<node> tree = vector<node>(1);

public:
    void insert(int64_t x, int cnt = 1) {
        int cur = 0;
        tree[cur].cnt += cnt;
        for (int bit = LOG; ~bit; --bit) {
            int to = !!(x & (1LL << bit));
            if (tree[cur].child[to] == -1) {
                tree[cur].child[to] = tree.size();
                tree.emplace_back(node());
            }
            cur = tree[cur].child[to];
            tree[cur].cnt += cnt;
        }
    }

    void erase(int64_t x) {
        int cur = 0;
        for (int bit = LOG; ~bit; --bit) {
            int to = !!(x & (1LL << bit));
            if (tree[cur].child[to] == -1 || tree[tree[cur].child[to]].cnt == 1) {
                tree[cur].child[to] = -1;
                return;
            }
            cur = tree[cur].child[to];
            tree[cur].cnt--;
        }
    }

    int64_t max_xor(int64_t x) {
        int64_t cur = 0, ret = 0;
        for (int bit = LOG; ~bit; bit--) {
            int to = !!(x & (1LL << bit));
            if (~tree[cur].child[!to]) {
                cur = tree[cur].child[!to];
                ret += !to * (1LL << bit);
            }
            else {
                cur = tree[cur].child[to];
                ret += to * (1LL << bit);
            }
        }
        return x ^ ret;
    }

    int64_t min_xor(int64_t x) {
        return -1 ^ max_xor(x ^ -1);
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
