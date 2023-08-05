#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>
using namespace std;

struct flight{
    int c, r, d, s;
    flight(int cc, int rr, int dd, int ss) : c(cc), r(rr), d(dd), s(ss){}
    bool operator<(const flight& other) const{
        return this->r <= other.r;
    }
};

const int MAXN = 2e5;//nodes
const int MAXM = 2e5;//edges;
//const int MAXN = 3;
//const int MAXM = 3;
const int MAXVAL = 2e9+1;
int layover[MAXN];
int ans[MAXN];
int anslow[MAXN];
bool visited[MAXN];
vector<vector<flight>> v(MAXM);
queue <pair<int, int>> q;//node, new lowest time
//
//void process(int node, int lowertime) {
//    int oldertime = ans[node];
//    ans[node] = lowertime;
//    anslow[node] = min(anslow[node], ans[node]);
//    if(v[node].empty())
//        return;
//    auto it = upper_bound(v[node].begin(), v[node].end(),
//                          flight(-1, lowertime + (node == 0 ? 0 : layover[node])-1, -1, -1));
//    while(it!=v[node].end() && it->r < oldertime){//
//        flight& f = *it;
//
//        if(ans[f.d] == MAXVAL || ans[f.d]-f.s > layover[f.d]) {
//            q.emplace(f.d, f.s);
//        }
//        it++;
//    }
//
//}

void dfs(int node, int lowersum){
    anslow[node] = min(anslow[node], lowersum);
    int oldsum = ans[node];
    ans[node] = lowersum;
    auto it = upper_bound(v[node].begin(), v[node].end(), flight(-1, lowersum+layover[node], -1, -1));
    auto end = upper_bound(v[node].begin(), v[node].end(), flight(-1, oldsum+layover[node], -1, -1));
    while(it!=end){
        flight &f = *it;
        if(!visited[f.d]) {
            if (ans[f.d] == MAXVAL || ans[f.d] - f.s > layover[f.d]) {
                dfs(f.d, f.s);
            }
        }
        else{
            if (f.s < ans[f.d]) {
                dfs(f.d, f.s);
            }
        }
        anslow[f.d] = min(anslow[f.d], f.s);
        it++;
    }
    visited[node] = true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
//    freopen("/Users/sahils/Downloads/prob3_silver_feb23/3.in", "r", stdin);
    fill(ans, ans + MAXN, MAXVAL);
    fill(anslow, anslow + MAXN, MAXVAL);
    fill(layover, layover + MAXN, MAXVAL);
    fill(visited, visited + MAXN, false);
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int c, r, d, s;
        cin >> c >> r >> d >> s, c--, d--;
        v[c].emplace_back(c, r, d, s);
    }
    for (int i = 0; i < N; i++) {
        if(!v[i].empty())
            sort(v[i].begin(), v[i].end());
    }
    for (int i = 0; i < N; i++) {
        cin >> layover[i];
    }
    layover[0] = 0;
    q.emplace(0, 0);
//    while (!q.empty()) {
//        pair<int, int> p = q.front();
//        q.pop();
//        if(ans[p.first] <= p.second)
//            continue;
//        process(p.first, p.second);
//    }
    dfs(0, 0);
    for (int i = 0; i < N; i++) {
        if (anslow[i] == MAXVAL){
            cout << -1 << "\n";
        }
        else
            cout << anslow[i] << "\n";
    }

}