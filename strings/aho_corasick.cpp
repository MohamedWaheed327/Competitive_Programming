class aho_corasick_static {
private:
    int sz = 0;
    struct node {
        int child[26], cnt, link;
        vector<int> occ;
        node() {
            cnt = 0, link = -1;
            memset(child, -1, sizeof child);
        }
    };
    vector<node> tree;

public:
    aho_corasick_static(const vector<string> &words) {
        tree = vector<node>(1);

        for (auto &s : words) {
            int cur = 0;
            for (auto it : s) {
                int to = it - 'a';
                if (tree[cur].child[to] == -1) {
                    tree[cur].child[to] = tree.size();
                    tree.emplace_back(node());
                }
                cur = tree[cur].child[to];
            }
            tree[cur].cnt++;
            tree[cur].occ.push_back(sz++);
        }

        queue<int> Q;
        Q.push(0);
        while (!Q.empty()) {
            int node = Q.front();
            Q.pop();
            for (int i = 0; i < 26; ++i) {
                int v = tree[node].child[i];
                if (~v) {
                    int j = tree[node].link;
                    while (~j && tree[j].child[i] == -1) {
                        j = tree[j].link;
                    }
                    tree[v].link = (~j ? tree[j].child[i] : 0);
                    tree[v].cnt += tree[tree[v].link].cnt;
                    for (auto &it : tree[tree[v].link].occ) {
                        tree[v].occ.push_back(it);
                    }
                    Q.push(v);
                }
            }
        }
    }

    int count(const string &s) {
        long long cur = 0, ans = 0;
        for (auto it : s) {
            int to = it - 'a';
            while (~cur && tree[cur].child[to] == -1) {
                cur = tree[cur].link;
            }
            cur = (~cur ? tree[cur].child[to] : 0);
            ans += tree[cur].cnt;
        }
        return ans;
    }

    vector<vector<int>> get_occ(const string &s) {
        int cur = 0, i = 0;
        vector<vector<int>> ret(sz);
        for (auto it : s) {
            int to = it - 'a';
            while (~cur && tree[cur].child[to] == -1) {
                cur = tree[cur].link;
            }
            cur = (~cur ? tree[cur].child[to] : 0);
            for (auto &it : tree[cur].occ) {
                ret[it].push_back(i);
            }
            i++;
        }
        return ret;
    }
};
