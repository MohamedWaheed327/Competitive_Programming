// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

struct hashLL {
    int64_t operator()(int64_t x) const {
        x = (x ^ (x >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
        x = (x ^ (x >> 27)) * UINT64_C(0x94d049bb133111eb);
        x = x ^ (x >> 31);
        return x;
    }
};

struct Hashmap {
    typedef int64_t key_t;
    typedef int val_t;
    typedef unordered_map<key_t, val_t, hashLL> map_t;

    key_t toXor;
    map_t m;

    Hashmap() {
        srand(time(0));
        toXor = rand();

        m.reserve(4096);
        m.max_load_factor(0.25);
    }

    val_t &operator[](const key_t &key) { return m[key ^ toXor]; }

    map_t::iterator find(const key_t &key) { return m.find(key ^ toXor); }

    map_t::iterator end() { return m.end(); }
};

void Main(...) {
    Hashmap hm;
    hm[1] += 2;
    cout << hm[1];    
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
