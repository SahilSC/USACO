#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#define all(a) a.begin(), a.end()
#define sz(a) a.size()
#define pb push_back

using namespace std;
using ll = long long;

const char nl = '\n';

struct cmp{
    bool operator()(const vector<ll> &a, const vector<ll> &b){
        return is_permutation(all(a), b.begin());
    }
};
int T;
set<vector<ll>> answers;

vector<ll> xs;
vector<vector<ll>> possiblesorts;


int add(ll a, ll b, ll c) {
    vector<ll> temp{a, b, c, a + b, a + c, b + c, a + b + c};
    sort(all(temp));
    for (auto ele: xs) {
        if (find(all(temp), ele) == temp.end())
            return 0;
    }
    vector<ll> triplet{a, b, c};
    for(const vector<ll> &other : answers){
        if(is_permutation(all(triplet), other.begin()))
            return 0;
    }
    if(a < 1 || b < 1 || c < 1)
        return 0;
    answers.insert(triplet);
    return 1;
}
void gen_sorts(vector<ll> &a){
    for (int i = 0; i < a.size(); i++) {
        for (int j = i + 1; j < a.size(); j++) {
            vector<ll> b = a;
            int temp = b[i];
            b[i] = b[j];
            b[j] = temp;
            possiblesorts.pb(b);
        }
    }
    possiblesorts.pb(xs);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
//    freopen("../input.txt","r",stdin);
    cin >> T;
    vector<ll> all_ans;
    for (int i = 0; i < T; i++) {
        int len; cin >> len;
        xs.clear(); xs.resize(len); answers.clear(); possiblesorts.clear();
        for (int j = 0; j < len; j++)
            cin >> xs[j];
        sort(all(xs));
        gen_sorts(xs);
        ll all = xs[len - 1];
        ll ans = 0;
        if (len == 7) {
            ans += add(xs[0], xs[1], xs[len - 1] - xs[0] - xs[1]);
        }
        if (len <= 6) {
            //a,b,c all there
            // last is gone
            ans += add(xs[0], xs[1], xs[len - 1] - xs[1]);
            //last is tehre
            ans += add(xs[0], xs[1], xs[len - 1] - xs[0] - xs[1]);
            //one of a,b,c gone
            ans += add(xs[len - 1] - xs[len - 3], xs[len - 1] - xs[len - 2], xs[len - 3] + xs[len - 2] - xs[len - 1]);

        }
        if (len <= 5){
            for(vector<ll> &v : possiblesorts){
                //(a) (b) (c)
                if(v[0] == 5 && v[1] == 4 && v[2] == 7 && v[3] == 9)
                    int xx;
                ans += add(v[0], v[1], v[2]);
                //(a) (b) with 1 (a,b)
                ans += add(v[0], v[1], v[len - 1]-v[0]-v[1]);
                //(a) (b) w 2 (a, b)
                for(ll e : v) {
                    //all abc
                    ans += add(v[0], v[1], v[2] - v[0]) + add(v[0], v[1], v[3] - v[0])
                           + add(v[0], v[1], v[2] - v[1]) + add(v[0], v[1], v[3] - v[1]);
                    //(a, b)
                }
                //(a) (b) w 3(a, b) covered in len == 6
                //(a) w 3(a, b) covered in len == 6
                //actually coverd below
                ll last3 = (v[len - 1] + v[len - 2] + v[len - 3])/2;
                ans += add(last3 - v[len - 1], last3 - v[len - 2], last3 - v[len - 3]);
                ans += add(v[len - 1] - v[len - 3], v[len - 1] - v[len - 2], v[len - 3] + v[len - 2] - v[len - 1]);
                //a w 2(a,b) + a + b + c covered
                //a w 1 (a, b) impossiible

                //no singles = covered in len == 6
            }
        }
        all_ans.pb(ans);
    }
    for_each(all(all_ans),[](int x){cout << x << nl;});
}