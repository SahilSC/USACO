#include <iostream>
#include <vector>
#include <algorithm>

#define all(a) a.begin(), a.end()
#define sz(a) a.size()
#define pb push_back

using namespace std;
using ll = long long;

const char nl = '\n';

ll N, K, L;
vector<ll> arr;
vector<ll> prefix;

bool works(int h) {//max is K*L, each has max of K
    auto it = arr.begin();
    ll remaining = K * L;
    for (int i = 0; i < h; i++, it++) {
        ll citations = *it;
        if(citations >= h)
            continue;
        if(h-citations > K || h - citations > remaining)
            return false;
        else{
            remaining-=h-citations;
        }
    }
    return true;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> K >> L;
//    freopen("../input.txt", "r", stdin);
    for (int i = 0; i < N; i++) {
        int t; cin >> t;
        arr.pb(t);
        if(i == 0)
            prefix.pb(arr[0]);
        else {
            prefix.pb(arr[i] + prefix[i - 1]);
        }
    }
    sort(all(arr), greater<>());

    int lo = 1;
    int hi = N;
    while(lo < hi){
        int mid = (lo + hi + 1) / 2;
        if (works(mid)){
            lo = mid;
        }
        else
            hi = mid -1;
    }
    cout << lo << nl;

}