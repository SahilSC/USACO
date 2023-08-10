#include <iostream>
#include <vector>
#include <map>
using namespace std;
string s;
int Q;
map<char, int> m = {{'C',0}, {'O',1}, {'W', 2}};
int main(){
    cin >> s >> Q;
    int prefix[3][s.length() + 1];
    prefix[0][0] = prefix[1][0] = prefix[2][0] = 0;
    for (int i = 1; i < s.length()+1; i++) {
        prefix[0][i] = prefix[0][i - 1];
        prefix[1][i] = prefix[1][i - 1];
        prefix[2][i] = prefix[2][i - 1];
        prefix[m[s[i-1]]][i]+=1;
    }
    for (int i = 0; i < Q; i++) {
        int r, l;
        cin >> l >> r;
        int arr[3];
        for (int j = 0; j <= 2; j++) {
            arr[j] = prefix[j][r] - prefix[j][l - 1];
        }
        if (arr[0] % 2 != arr[1] % 2 && arr[1] % 2 == arr[2] % 2)
            cout << 'Y';
        else
            cout << 'N';
    }
}