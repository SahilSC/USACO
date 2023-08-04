#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;
using ll = long long;
int N;
ll T, C, M;
const ll MAX = 2e9;
vector<pair<ll, ll>> arr;
struct cow{
    ll a, b, c;
    cow() = default;
    cow(ll aa, ll bb, ll cc) : a(aa), b(bb), c(cc){}
};
bool works(ll z, vector<cow> &cows){
    vector<pair<ll,ll>> t;
    for(auto & temp : cows) {
        ll upper = temp.c - temp.b * z;
        ll lower = temp.a - temp.b;
        pair<ll, ll> p;
        if(lower == 0){
            if (temp.c < z * (temp.a))
                return false;
            p.first = std::max(static_cast<ll>(1), z - M);
            p.second = std::min(C, min(temp.c / temp.a, z - 1));
        }
        else if (lower > 0){
            ll ans = (upper) / (lower);
            if (ans <= 0){
                return false;
            }
            ans = std::min(ans, std::min(C, z - 1));
            ll other = z - ans;
            if (other > M)
                return false;
            p.second = ans;
            p.first = std::max(static_cast<ll>(1), z-M);
        }
        else{
            ll ans = ceil(static_cast<double>(upper) / lower);
            if(ans>0){
                if (ans > C){
                    return false;
                }
                p.first = std::max(static_cast<ll>(1), max(ans,z - M));
                ans = min(z-1,  C);
                ll other = z - ans;
                if (other > M) {
                    return false;
                }

                p.second = ans;
            }
            else{
                p.first = std::max(static_cast<ll>(1), z - M);
                p.second = std::min(C, z - 1);
            }

        }
        t.push_back(p);
    }
    ll min = t[0].first;
    ll max = t[0].second;
    for (const auto &pi: t) {
        min = std::max(min, pi.first);
        max = std::min(max, pi.second);
    }
    return min <= max;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
//    freopen("/Users/sahils/Downloads/prob1_silver_feb23/2.in", "r", stdin);
    cin >> T;
    while (T--) {
        arr.clear();
        cin >> N >> C >> M;
        vector<cow> cows(N);
        for (int i = 0; i < N; i++) {
            ll a, b, c;
            cin >> a >> b >> c;
            cows[i] = cow(a, b, c);
        }
        ll lo = 2;
        ll hi = C+M;//C+M
        while(lo != hi){
            ll mid = (lo + hi + 1) / 2;
            if (mid == 823)
                int x;
            if(works(mid, cows)){
                lo = mid;
            }
            else{
                hi = mid - 1;
            }
        }
        cout << C+M-lo << "\n";
    }
}