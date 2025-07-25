class manacher {
private:
    vector<int> d;

public:
    manacher(string t) {
        string s = "#";
        for (auto c : t) {
            s += c + string("#");
        }
        int n = s.size(), l = 1, r = 1;
        s = "$" + s + "^";
        vector<int> p(n + 2);
        for (int i = 1; i <= n; i++) {
            p[i] = max(0, min(r - i, p[l + (r - i)]));
            while (s[i - p[i]] == s[i + p[i]]) {
                p[i]++;
            }
            if (i + p[i] > r) {
                l = i - p[i], r = i + p[i];
            }
        }
        d = vector<int>(p.begin() + 1, p.end() - 1);
    }

    int even(int i) {
        return d[2 * i] - 1;
    }

    int odd(int i) {
        return d[2 * i + 1] - 1;
    }

    bool is_palindrome(int l, int r) {
        int len = r - l + 1;
        if (len & 1) {
            return odd((l + r) / 2) >= len;
        }
        else {
            return even((l + r) / 2 + 1) >= len;
        }
    }
};
