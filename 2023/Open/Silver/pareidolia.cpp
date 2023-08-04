#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
string s;
int n;
const string b{" bessie"};
void gred(int gred[]){

}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> s;
    n = s.length();
    int gred[n];
    vector<vector<long long>> arr;
    int len = 7;
    for (int i = 0; i < len; i++) {
         arr.emplace_back(n);
    }

//    int run = s[0] != 'b';
    if(s[0]=='b')
        arr[1][0] = 1;
    else{
        arr[0][0] = 1;
    }
    long long sum = 0;
    long long ans = 0;
    for (int i = 1; i < n; i++) {
//        arr[len-1][i] = arr[len-1][i - 1];
        arr[0][i] = arr[len - 1][i - 1] + arr[0][i-1];
//        run++;
        if(s[i]=='b'){
            arr[1][i] += 1 + arr[0][i];
            arr[0][i] = 0;
        }
        else{
            arr[0][i] += 1;
        }
        for (int j = 1; j <= 5; j++) {
            if (s[i] == b[j+1]){
                arr[j + 1][i] += arr[j][i - 1];
            }
            else{
                arr[j][i] += arr[j][i - 1];
            }
        }
        ans += arr[len-1][i] + sum;
        sum += arr[len - 1][i];
    }
    cout << ans;

}