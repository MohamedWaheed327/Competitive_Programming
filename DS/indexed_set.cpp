// Mohamed_Waheed
#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template <class M = int, class T = less<M>>
class indexed_set : public tree<M, null_type, T, rb_tree_tag, tree_order_statistics_node_update> {
private:
    /*
     * less<>           ---> set, increasing
     * less_equal<>     ---> multiset, increasing
     * greater<>        ---> set, decreasing
     * greater_equal<>  ---> multiset, decreasing
     */
public:
    void erase_element(M v) {
        int rank = this->order_of_key(v);    // Number of elements that are less than v in t
        auto it = this->find_by_order(rank); // Iterator that points to the (rank+1)th element in t
        if (*it == v) this->erase(it);
    }

    void erase_all(M v) {
        int cnt = count_range(v, v);
        while (cnt--) {
            erase_element(v);
        }
    }

    int count_range(M l, M r) { 
        if (is_same<T, less<>>() || is_same<T, less<M>>()) {
            auto it = this->upper_bound(r);
            return (it == this->end() ? this->size() : this->order_of_key(*it)) - this->order_of_key(l);
        }
        if (is_same<T, less_equal<>>() || is_same<T, less_equal<M>>()) {
            auto it = this->lower_bound(r);
            return (it == this->end() ? this->size() : this->order_of_key(*it)) - this->order_of_key(l);
        }
        if (is_same<T, greater<>>() || is_same<T, greater<M>>()) {
            auto it = this->upper_bound(l);
            return (it == this->end() ? this->size() : this->order_of_key(*it)) - this->order_of_key(r);
        }
        if (is_same<T, greater_equal<>>() || is_same<T, greater_equal<M>>()) {
            auto it = this->lower_bound(l);
            return (it == this->end() ? this->size() : this->order_of_key(*it)) - this->order_of_key(r);
        }
        //for less<>, less_equal<>: return this->order_of_key(r + 1) - this->order_of_key(l);
    }

    M operator[](int index) {
        return *this->find_by_order(index);
    }

    // size, insert, begin, end, rbegin, rend
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
