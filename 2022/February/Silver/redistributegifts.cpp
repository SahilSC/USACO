#include <iostream>
#include <vector>
using namespace std;
const int maxN = 501;
bool is_reachable[maxN][maxN];
int rankings[maxN][maxN];
bool connect[maxN][maxN];
int N;
void dfs(int src, int cur){
    is_reachable[src][cur] = true;
    for (int i = 1; i <= N; i++) {
        if(connect[cur][i] & !is_reachable[src][i])
            dfs(src, i);
    }
//    for()
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for (int i = 1; i <= N; i++) {
        bool seen = false;
        for (int j = 1; j <= N; j++) {
            int num;
            cin >> num;
            rankings[i][num] = j;
            connect[i][num] = !seen;
            seen |= num == i;
        }
    }
    for (int c1 = 1; c1 <= N; c1++) {
        dfs(c1, c1);
    }
    for (int i = 1; i <= N; i++) {
        int bestGift = i;
        for (int j = 1; j <= N; j++) {
            if(connect[i][j] && is_reachable[j][i] && rankings[i][bestGift] > rankings[i][j]){
                bestGift = j;
            }
        }
        cout << bestGift << "\n";
    }
}

//
//5
//3 5 4 2 1
//3 2 1 4 5
//1 5 2 3 4
//5 4 3 2 1
//2 1 4 3 5
