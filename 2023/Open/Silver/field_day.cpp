#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <string>
#include <queue>
#include <algorithm> // added this header for std::min
using namespace std;

int C, Q;


int main(){
    cin >> C >> Q;
    vector<int> arr(Q);
    vector<int> ans(Q);
    int totalss = int(pow(2, C));
    int masks[totalss];
    fill(masks, masks + totalss, 19);

    queue<int> q;
    for (int i = 0; i < Q; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < s.length(); j++) {
            if(s[j]=='H'){
                arr[i] += 1 << (C - 1 - j);
            }
        }
        q.push(arr[i]);
        masks[arr[i]] = 0;
        arr[i] = ((1 << C)-1) ^ (arr[i]);

    }


    while(!q.empty()){
        int i = q.front();
        q.pop();

        if(masks[i]!=19){
            for(int j = 0; j < C; j++){
                int nnum = i^(1<<j);
                if(masks[nnum] != 19)
                    continue;
                masks[nnum] = std::min(masks[nnum], 1 + masks[i]); // used std::min instead of min
                if(masks[nnum] > masks[i])
                    q.push(nnum);

            }
        }
    }
//    for (int i = 0; i < Q; i++) {
//        int curmin = 19;
//        for (int j = 0; j < C; j++) {
//            curmin = min(curmin, )
//        }
//    }
    for_each(arr.begin(), arr.end(), [&masks](int x){cout << C-masks[x] << "\n";});
}