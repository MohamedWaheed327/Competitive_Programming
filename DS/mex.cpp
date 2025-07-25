// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

template <int N = (int)1e6>
class MEX {
private:
    bitset<N + 1> mex;
    vector<int> cnt;

public:
    MEX() {
        mex.set();
        cnt.assign(N + 1, 0);
    }

    void add(int x) {
        if (++cnt[x] == 1) {
            mex[x] = false;
        }
    }

    void remove(int x) {
        if (--cnt[x] == 0) {
            mex[x] = true;
        }
    }

    int get_mex() {
        return mex._Find_first();
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
