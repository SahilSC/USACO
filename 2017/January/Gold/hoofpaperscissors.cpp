#include <iostream>
#include <vector>
#include <algorithm>


#include <map>
#include <unordered_map>
#include <array>
#include <cstdio>

#define all(a) a.begin(), a.end()
#define sz(a) a.size()
#define pb push_back

using namespace std;
using ll = long long;

const char nl = '\n';
const int maxN = 1e5 + 2;
int dp[3][21];
int main(){
    ios::sync_with_stdio(false);
    freopen("hps.in", "r", stdin);
    freopen("hps.out", "w", stdout);
    cin.tie(nullptr);
    unordered_map<char, int> mp;
    unordered_map<int, char> mp2;
    mp.insert({'P', 0});
    mp.insert({'S', 1});
    mp.insert({'H', 2});
    mp2.insert({0, 'P'});
    mp2.insert({1, 'S'});
    mp2.insert({2, 'H'});
    int N, K;
    cin >> N >> K;
    int ans = 0;
    for (int i = 0; i < N; i++) {
        char c;
        cin >> c;
        int num = ((mp.find(c) -> second) + 1)%3;
        dp[num][0]++;
        ans = max(dp[num][0], ans);
        for (int j = 1; j <= K; j++) {
            dp[num][j]++;
            dp[num][j] = max(dp[num][j], dp[(num + 1) % 3][j - 1] + 1);
            dp[num][j] = max(dp[num][j], dp[(num + 2) % 3][j - 1] + 1);
            ans = max(dp[num][j], ans);
        }
    }
//    cout << max(dp[0][K], max(dp[1][K], dp[2][K]));
    cout << ans;
}