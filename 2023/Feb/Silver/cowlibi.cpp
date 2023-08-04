#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include <numeric>
using namespace std;
using ll = long long;
int G, N;
struct unit{
    ll x, y, t;

    unit() = default;
    unit(ll xx, ll yy, ll tt) : x(xx), y(yy), t(tt){}

    bool operator<(const unit &c) const {
        return this->t < c.t;
    }
};

bool ifpossible(unit a, unit b) {//a is smaller timepoint
//    return (b.t - a.t) >= abs(a.x - b.x) + abs(a.y - b.y);
    return (b.t-a.t)*(b.t - a.t) < (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
//    freopen("/Users/sahils/Downloads/prob2_silver_feb23/7.in", "r", stdin);
    cin >> G >> N;
    vector<unit> g;
    for (int i = 0; i < G; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        g.emplace_back(a, b, c);
    }
    sort(g.begin(), g.end());
    int innocent = 0;
    for (int i = 0; i < N; i++) {
        ll x, y, t;
        cin >> x >> y >> t;
        unit a(x, y, t);
        auto it = upper_bound(g.begin(), g.end(), a);
        if (it == g.end()) {
            innocent += ifpossible(*(it - 1), a);
        }
        else if (it == g.begin()){
            innocent += ifpossible(a, *(it));
        }
        else{
            if(ifpossible(*(it - 1), a) || ifpossible(a, *(it)))
                innocent++;
        }
    }
    cout << innocent << "\n";
}