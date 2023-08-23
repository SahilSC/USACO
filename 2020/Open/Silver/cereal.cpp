#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <climits>

#define all(a) a.begin(), a.end()
#define sz(a) a.size()
#define pb push_back

using namespace std;
using ll = long long;

const char nl = '\n';
struct cow{
    int ind;
    int f;
    int s;
    cow() : ind(0), f(0), s(0){}
    cow(int ii, int ff, int ss) : ind(ii), f(ff), s(ss) {}
};
int N, M, ans;
int INF = INT_MAX;
const int MAX = 1e5+1;
int curcereal[MAX];
cow cows[MAX];

void placecow(int i){
    if(i == INT_MAX)
        return;
    int cprev = -1;
    if(curcereal[cows[i].f] > i){
        cprev = curcereal[cows[i].f];
        curcereal[cows[i].f] = i;
    }
    else if (curcereal[cows[i].s] > i){
        cprev = curcereal[cows[i].s];
        curcereal[cows[i].s] = i;
    }
    else{
        ans--;
        return;
    }
    placecow(cprev);
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("cereal.in", "r", stdin);
    freopen("cereal.out", "w", stdout);
    fill(curcereal, curcereal + MAX, INF);
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        int c1, c2; cin >> c1 >> c2;
        cows[i] = cow(i, c1, c2);
    }
    int answers[N+1];
    for (int i = N; i >= 1; i--) {
        ans++;
        placecow(i);
        answers[i] = ans;
    }
    for_each(answers+1, answers + N + 1, [](int x) { cout << x << nl; });
}