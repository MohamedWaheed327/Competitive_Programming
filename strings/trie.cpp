// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

class trie {
private:
    struct node {
        int word = 0, prefix = 0, child[26];
        node() {
            memset(child, -1, sizeof child);
        }
    };
    vector<node> tree = vector<node>(1);

public:
    void insert(const string &s, int cnt = 1) {
        int cur = 0;
        for (auto it : s) {
            int to = it - 'a';
            if (tree[cur].child[to] == -1) {
                tree[cur].child[to] = tree.size();
                tree.emplace_back();
            }
            cur = tree[cur].child[to];
            tree[cur].prefix += cnt;
        }
        tree[cur].word += cnt;
    }

    void erase(const string &s) {
        int cur = 0;
        for (auto it : s) {
            int to = it - 'a';
            if (tree[cur].child[to] == -1 || tree[tree[cur].child[to]].prefix == 1) {
                tree[cur].child[to] = -1;
                return;
            }
            cur = tree[cur].child[to];
            tree[cur].prefix--;
        }
        tree[cur].word--;
    }

    int count_word(const string &s) {
        int cur = 0;
        for (auto it : s) {
            int to = it - 'a';
            if (tree[cur].child[to] == -1) {
                return 0;
            }
            cur = tree[cur].child[to];
        }
        return tree[cur].word;
    }

    int count_prefix(const string &s) {
        int cur = 0;
        for (auto it : s) {
            int to = it - 'a';
            if (tree[cur].child[to] == -1) {
                return 0;
            }
            cur = tree[cur].child[to];
        }
        return tree[cur].prefix;
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
