#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <cmath>

#define all(a) a.begin(), a.end()
#define sz(a) a.size()
#define pb push_back

using namespace std;
using ll = long long;

const char nl = '\n';
const int maxN = 2001;
int dp[maxN][2 * maxN];
int N, moonies, cones;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> moonies >> cones;
    vector<array<int, 3>> v(N);
    for (auto &[a, b, c] : v) {
        cin >> c >> b >> a;
    }
    sort(all(v), greater<>());
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < v[0].size(); j++) {
//            cout << v[i][j] << " ";
//        }
//        cout << nl;
//    }
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= moonies + cones; j++) {
            dp[i][j] = dp[i - 1][j];
            int newJ = j - v[i - 1][1] * v[i - 1][0];
            if (newJ >= moonies) {
                dp[i][j] = max(dp[i][j], dp[i - 1][newJ] + v[i - 1][2]);
            }
            else {
                int val = (j - moonies) / v[i - 1][0];
                newJ = j;
                if (val <= 0 && j >= moonies) newJ = moonies;
                if (val > 0) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][moonies - v[i-1][1] + val] + v[i - 1][2]);
                }
                else if (newJ >= v[i-1][1]){
                    dp[i][j] = max(dp[i][j], dp[i - 1][newJ-v[i-1][1]] + v[i-1][2]);
                }
            }
        }
    }
//    for (int i = 0; i < 20; i++) {
//        for (int j = 0; j < 20; j++) {
//            cout << dp[i][j] << " ";
//        }
//        cout << nl;
//    }
    cout << dp[N][cones + moonies];
}
