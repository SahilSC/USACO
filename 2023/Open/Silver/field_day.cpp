#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdlib>

using ll = long long;
using namespace std;

int N, Q;
vector<ll> arr;
vector<int> inds;
map<int, int> m;
vector<ll> bsum;

ll computeCost(){
    ll ans = 0;
    for (int i = 0; i < N; i++) {
        ans += (i + 1) * arr[i];
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N;
    arr.resize(N);
    bsum.resize(N + 1);
    inds.resize(N);
    vector<ll> answers;
    for (int i = 0; i < N; i++) {
        inds[i] = i;
    }
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    sort(inds.begin(), inds.end(), [](int a, int b){ return arr[a] < arr[b]; });
    for (int i = 0; i < N; i++) {
        m.insert({inds[i], i});
    }
    sort(arr.begin(), arr.end());
    ll ans = computeCost();

    //prefix
    for (int i = N - 1; i >= 0; i--) {
        bsum[i] = arr[i]+bsum[i +1];
    }
    cin >> Q;
    while (Q--) {
        if (Q == 0) {
            int x;
        }
        int i,newind;
        ll newval, prefixc, switching;
        cin >> i >> newval,i--;
        int curind = m[i];
        ll curval = arr[curind];
        newind = upper_bound(arr.begin(), arr.end(), newval)-arr.begin();
        if(newval > curval) {
            prefixc = -(bsum[curind + 1] - bsum[newind]);
            switching = (newind)*(newval)-curval * (curind + 1);
        }
        else{
            prefixc = bsum[newind] - bsum[curind];
            switching = (newind+1)*newval-curval * (curind + 1);
        }

        answers.push_back(ans + prefixc + switching);
    }
    for_each(answers.begin(), answers.end(), [](ll x) { cout << x << "\n"; });


}


