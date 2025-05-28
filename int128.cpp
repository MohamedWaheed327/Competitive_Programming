// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

#define i128 __int128_t
istream &operator>>(istream &in, i128 &x) {
    x = 0;
    string s;
    cin >> s;
    int start = 0, sign = 1;
    if (s[0] == '-') {
        start = 1;
        sign = -1;
    }
    for (int i = start; i < s.size(); ++i) {
        x *= 10;
        x += s[i] - '0';
    }
    x *= sign;
    return in;
}

ostream &operator<<(ostream &out, i128 x) {
    if (x < 0) {
        cout << '-';
        x = -x;
    }
    string ret = x ? "":"0";
    while (x) {
        ret.push_back(x % 10 + '0');
        x /= 10;
    }
    reverse(ret.begin(), ret.end());
    cout << ret;
    return out;
}

void Main(...) {
    i128 x = 0, y = 0;
    cin >> x >> y;
    cout << x + y << " " << x - y;
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
