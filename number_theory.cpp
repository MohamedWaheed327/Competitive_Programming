// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

namespace sieve {
    vector<bool> is_prime(int N) {
        vector<int> _primes;
        vector<bool> _is_prime(N + 1, 1);
        _is_prime[0] = _is_prime[1] = 0;
        for (int64_t i = 1; i <= N; i++) {
            if (_is_prime[i]) {
                _primes.push_back(i);
            }
            for (auto it : _primes) {
                if (i * it > N) {
                    break;
                }
                _is_prime[i * it] = 0;
                if (i % it == 0) {
                    break;
                }
            }
        }
        return _is_prime;
    }

    vector<int> primes(int N) {
        vector<int> _primes;
        vector<bool> _is_prime(N + 1, 1);
        _is_prime[0] = _is_prime[1] = 0;
        for (int64_t i = 1; i <= N; i++) {
            if (_is_prime[i]) {
                _primes.push_back(i);
            }
            for (auto it : _primes) {
                if (i * it > N) {
                    break;
                }
                _is_prime[i * it] = 0;
                if (i % it == 0) {
                    break;
                }
            }
        }
        return _primes;
    }

    vector<int> mobius(int N) {
        vector<int> _primes, mob(N + 1, 1);
        vector<bool> _is_prime(N + 1, 1);
        _is_prime[0] = _is_prime[1] = 0;
        for (int64_t i = 1; i <= N; i++) {
            if (_is_prime[i]) {
                mob[i] = -1;
                _primes.push_back(i);
            }
            for (auto it : _primes) {
                if (i * it > N) {
                    break;
                }
                mob[i * it] = !!(i % it) * -mob[i];
                _is_prime[i * it] = 0;
                if (i % it == 0) {
                    break;
                }
            }
        }
        return mob;
    }

    vector<bool> segmented_sieve(int64_t l, int64_t r) {
        vector<bool> primes_seg(r - l + 1, 1);
        if (l <= 1 && 1 <= r) {
            primes_seg[1 - l] = 0;
        }
        vector<int> prime = primes((int)sqrt(r));
        for (auto it : prime) {
            int64_t start = l / it * it + (l % it ? it : 0);
            for (int64_t i = start; i <= r; i += it) {
                if (i != it) {
                    primes_seg[i - l] = 0;
                }
            }
        }
        return primes_seg;
    }

    vector<int> spf(int N) {
        vector<int> _primes;
        vector<int> _spf(N + 1, 0);
        iota(_spf.begin(), _spf.end(), 0);
        for (int64_t i = 2; i <= N; i++) {
            if (_spf[i] == i) {
                _primes.push_back(i);
            }
            for (auto it : _primes) {
                if (i * it > N) {
                    break;
                }
                _spf[i * it] = min(it, _spf[i]);
                if (i % it == 0) {
                    break;
                }
            }
        }
        return _spf;
    }

    vector<vector<int>> factors(int N) {
        auto _spf = spf(N);
        vector<vector<int>> fact(N + 1);
        for (int i = 1; i <= N; i++) {
            int cur = i;
            while (1 < cur) {
                fact[i].push_back(_spf[cur]);
                cur /= _spf[cur];
            }
        }
        return fact;
    }

    vector<vector<int>> divs(int N) {
        vector<vector<int>> divisors(N + 1);
        for (int i = 1; i <= N; i++) {
            for (int j = i; j <= N; j += i) {
                divisors[j].push_back(i);
            }
        }
        return divisors;
    }

    vector<int> phi(int N) {
        vector<int> _phi(N + 1);
        iota(_phi.begin(), _phi.end(), 0);
        for (int i = 1; i <= N; i++) {
            for (int j = 2 * i; j <= N; j += i) {
                _phi[j] -= _phi[i];
            }
        }
        return _phi;
    }

    vector<int> next_prime(int N) {
        N += 1000;
        auto _is_prime = is_prime(N);
        vector<int> _next_prime(N + 1, 0);
        int last = 1e9 + 7;
        for (int i = N; ~i; i--) {
            _next_prime[i] = last;
            if (_is_prime[i]) {
                last = i;
            }
        }
        return _next_prime;
    }
}

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
