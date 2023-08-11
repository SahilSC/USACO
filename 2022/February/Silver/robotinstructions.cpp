#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>

#define all(a) a.begin(), a.end()
#define sz(a) a.size()
#define pb push_back

using namespace std;
using ll = long long;
using P = pair<ll, ll>;
using PP = pair<P, ll>;

const char nl = '\n';

int n;
ll xg, yg;

vector<P> a;
vector<P> b;
vector<pair<P, ll>> as;
vector<pair<P, ll>> bs;

P operator-(const P &a, const P &b){
    return make_pair(a.first - b.first, a.second - b.second);
}
PP operator-(const PP &a, const PP &b){
    return make_pair(a.first - b.first, 0);
}
bool operator==(const PP &a, const PP &b){
    return a.first == b.first;
}
bool operator<(const PP &a, const PP &b){
    return a.first < b.first;
}
ostream& operator<<(ostream& os, const P&b){
    os << "P: " << b.first << " " << b.second;
    return os;
}
void gen_subsets(vector<P> &a, vector<pair<P,ll>> &as) {
    for (int i = 0; i < (1 << sz(a)); i++) {
        ll s1{0}, s2{0};
        ll bitson = __builtin_popcount(i);
        if(bitson == 4)
            int x;
        for (int j = 0; j < sz(a); j++) {
            if(i & 1<<j){
                s1 += a[j].first;
                s2 += a[j].second;
            }
        }
        P t1(s1, s2);
        PP t2(t1, bitson);
        as.pb(t2);

    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
//    freopen("/Users/sahils/Downloads/prob2_silver_feb22/5.in", "r", stdin);
    cin >> n >> xg >> yg;
    P fakegoal{xg, yg};
    pair<P, ll> goal{fakegoal, 0} ;

    for (int i = 0; i < n; i++) {
        ll p, q;
        cin >> p >> q;
        if(i % 2 == 0)
            a.emplace_back(p, q);
        else
            b.emplace_back(p, q);
    }
    gen_subsets(a, as);
    gen_subsets(b, bs);
    sort(all(bs));
    sort(all(as));
    vector<ll> ans(n+1);
    PP subtract(make_pair(0, 1), 0);
    PP prev = {{1e18, 1e18}, 0};
    vector<ll> prevbitcounts(n + 1);
    for (int i = 0; i < sz(as); i++) {
        auto f = as[i];
        auto need = goal - f - subtract;
        if(prev!=need) {
            prevbitcounts = vector<ll>(n + 1);
            prev = need;
            auto it = upper_bound(all(bs), need, [](const PP &a, const PP &b) { return a.first < b.first; });
            while (it != bs.end() && f.first.first + it->first.first == xg && f.first.second + it->first.second == yg) {
                prevbitcounts[it->second]++;
                it++;
            }
        }
        for (int k = f.second; k <= n; k++) {
            ans[k] += prevbitcounts[k - f.second];
        }
    }
    for_each(ans.begin()+1, ans.end(), [](ll x){ cout << x << nl; });
}