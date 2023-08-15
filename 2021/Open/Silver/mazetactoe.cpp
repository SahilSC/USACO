#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <set>
#define all(a) a.begin(), a.end()
#define sz(a) a.size()
#define pb push_back

using namespace std;
using ll = long long;

const char nl = '\n';
bool visited[25][25][19683];
bool seenstate[19683];
set<int> answers;
char board[25][25][3];
int N;
int pow3[9];
int x[4]{0, 0, 1, -1};
int y[4]{1, -1, 0, 0};
bool hasMoo(int b){
    int state[3][3];
    for (int i = 8; i >= 0; i--) {
        int a = b/pow3[i];
        int ci = i/3; int cj = i%3;
        state[ci][cj]=a;
        b -= a * pow3[i];
    }
    bool moo = false;
    for(int i = 0; i < 3; i++){//m = 1
        if(state[i][0] == 1 && state[i][1]==2 && state[i][2]==2 || state[i][0] == 2 && state[i][1]==2 && state[i][2]==1) moo = true;
    }
    for(int i = 0; i < 3; i++){//m = 1
        if(state[0][i] == 1 && state[1][i]==2 && state[2][i]==2 || state[0][i] == 2 && state[1][i]==2 && state[2][i]==1) moo = true;
    }
    if(state[0][0]==1 && state[1][1] == 2 && state[2][2] == 2 || state[0][0]==2 && state[1][1]==2 && state[2][2] == 1) moo = true;
    if(state[2][0]==1 && state[1][1] == 2 && state[0][2] == 2 || state[2][0]==2 && state[1][1]==2 && state[0][2] == 1) moo = true;
    return moo;
}

void dfs(int i, int j, int b){
    if(visited[i][j][b])
        return;
    visited[i][j][b] = true;
    if(board[i][j][0] == 'M' || board[i][j][0] == 'O'){
        int ci = board[i][j][1]-'1'; int cj = board[i][j][2]-'1';
        int toadd;
        if(board[i][j][0] == 'M')
            toadd = 1;
        else
            toadd = 2;
        int ind = ci*3 + cj;
        int curch = b/pow3[ind] % 3;
        if(curch==0){
            b += toadd * pow3[ind];
            visited[i][j][b]=true;
        }
    }
    if (hasMoo(b)) {
        answers.insert(b);
        return;
    }
    for (int k = 0; k < 4; k++) {//r, l, d, u
        int ni = i + x[k]; int nj = j + y[k];
        if (board[ni][nj][0] != '#') dfs(ni, nj, b);
    }

}
int main(){
    ios::sync_with_stdio(false);
    int bessie_i, bessie_j;
//    freopen("../input.txt", "r", stdin);
    cin.tie(nullptr);
    pow3[0]=1;
    for (int i = 1; i < 9; i++) {
        pow3[i] = 3*pow3[i-1];
    }
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            scanf(" %c%c%c", &board[i][j][0], &board[i][j][1], &board[i][j][2]);
            if(board[i][j][0]=='B'){
                bessie_i = i; bessie_j = j;
            }
        }
    }
    dfs(bessie_i, bessie_j, 0);
    cout << answers.size() << nl;
}