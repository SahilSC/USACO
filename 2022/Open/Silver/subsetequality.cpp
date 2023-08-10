#include <iostream>

using namespace std;
string s, t;
const int maxN = 18;
bool pairs[maxN][maxN];
int freqs[maxN];
int freqt[maxN];
int Q;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
//    freopen("/Users/sahils/Downloads/prob2_silver_open22/10.in", "r", stdin);
    cin >> s >> t >> Q;
    for (int i = 0; i < s.length(); i++) {
        freqs[s[i] - 'a']++;
    }
    for (int i = 0; i < t.length(); i++) {
        freqt[t[i] - 'a']++;
    }
    for (int i = 0; i <= 'r' -'a'; i++) {
        int x;
        for (int j = 0; j <= 'r' - 'a'; j++) {
            int p1 = 0, p2 = 0;
            bool pos = true;
            while(p1 != s.length() ||  p2 != t.length()){
                while (p1 != s.length() && s[p1] != 'a' + i && s[p1] != 'a' + j) {
                    p1++;
                }
                while (p2 != t.length() && t[p2] != 'a' + i && t[p2] != 'a' + j) {
                    p2++;
                }
                if(p1 == s.length() && p2 == t.length()) { continue; }
                if(p1 == s.length() && p2 != t.length() || p1 != s.length() && p2 == t.length() || (s[p1] != t[p2])){
                    pos = false;
                    break;
                }
                p1++, p2++;
            }
            pairs[i][j] = pos;
//            pairs[j][i] = pos;
        }
    }
    for (int i = 0; i < Q; i++) {
        string q;
        cin >> q;
        int pos = true;
        for (int j = 0; j < q.length(); j++) {
            for (int k = 0; k < q.length(); k++) {
                if(!pairs[q[j]-'a'][q[k]-'a'] && !pairs[q[k]-'a'][q[j]-'a']) {
                    pos = false;
                    break;
                }
            }
//            if (freqs[q[j]-'a'] != freqt[q[j]-'a'])
//                pos = false;
        }
        cout << (pos ? 'Y' : 'N');
    }
}