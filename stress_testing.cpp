#include <bits/stdc++.h>
using namespace std;

template <class M>
M rand(M l, M r) {
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    return rng() % (r - l + 1) + l;
}
int turn;
stringstream in, out1, out2;
struct in_unit {
    in_unit operator>>(auto &x) {
        in >> x;
        return *this;
    }
} cinn;
struct out_unit {
    out_unit operator<<(const auto &x) {
        if (turn == 0) {
            in << x;
        }
        else if (turn == 1) {
            out1 << x;
        }
        else if (turn == 2) {
            out2 << x;
        }
        else {
            cout << x;
        }
        return *this;
    }
} coutt;
#define cin cinn
#define cout coutt

void generate() {
}

void brute() {
}

void Main(...) {
}

int T = 100;
signed main() {
    while (T--) {
        in = stringstream(), out1 = stringstream(), out2 = stringstream();
        turn = 0, generate();
        stringstream copy(in.str());
        turn = 1, brute();
        in = stringstream(copy.str());
        turn = 2, Main();
        in = stringstream(copy.str());

        turn = 3;
        if (out1.str() != out2.str()) {
            cout << in.str() << "\n\n";
            cout << out1.str() << "\n\n";
            cout << out2.str() << "\n\n";
            exit(0);
        }
    }
    cout << "Accepted";
}

/*
    void shuffle(auto &x) {
        random_device rd;
        mt19937 g(rd());
        shuffle(x.begin(), x.end(), g);
    }
    // generate tree

    vector<int> v{0};
    vector<int> rem(n);
    vector<vector<int>> g(n + 1);
    iota(rem.begin(), rem.end(), 1);
    shuffle(rem);

    while (rem.size()) {
        int r = rand(0, v.size() - 1);
        g[r].push_back(rem.back());
        g[rem.back()].push_back(r);
        v.push_back(rem.back());
        rem.pop_back();
    }


*/
