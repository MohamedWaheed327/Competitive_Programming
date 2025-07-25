// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

template <int N>
class bitset_matching {
private:
    char text[N];
    bitset<N> mask[26], st_mask;

public:
    bitset_matching() {
        fill(text, text + N, 'a');
        mask[0].set();
    }

    void set_text(const string &s) {
        for (int i = 0; i < s.size(); i++) {
            update(i, s[i]);
        }
    }

    void update(int idx, char ch) {
        mask[text[idx] - 'a'][idx] = 0;
        text[idx] = ch;
        mask[text[idx] - 'a'][idx] = 1;
    }

    int pattern_count(const string &pat, int l, int r) {
        if (r - l + 1 < pat.size()) return 0;
        st_mask.set();
        for (int i = 0; i < pat.size(); ++i) {
            st_mask &= (mask[pat[i] - 'a'] >> i);
        }
        return (st_mask >> l).count() - (st_mask >> (r - pat.size() + 2)).count();
    }

    vector<int> pattern_pos(const string &pat, int l, int r) {
        pattern_count(pat, l, r);
        vector<int> pos;
        for (int i = st_mask._Find_next(l - 1);; i = st_mask._Find_next(i)) {
            if (r - pat.size() + 1 < i) return pos;
            pos.push_back(i);
        }
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
