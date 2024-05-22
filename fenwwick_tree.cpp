// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

// 0 index
class fenwick_tree {
private:
    vector<long long> fenw;

    void add(int ind, long long val) {
        ++ind;
        while (ind < fenw.size()) {
            fenw[ind] += val;
            ind += (ind & -ind);
        }
    }

    long long get(int ind) {
        ++ind;
        long long ret = 0;
        while (ind) {
            ret += fenw[ind];
            ind -= (ind & -ind);
        }
        return ret;
    }

public:
    fenwick_tree(int n) {
        fenw.assign(n + 1, 0);
    }

    void update(int ind, long long val) {
        add(ind, val - query(ind, ind));
    }

    long long query(int l, int r) {
        return get(r) - get(l - 1);
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
