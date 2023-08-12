#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <cmath>

#define all(a) a.begin(), a.end()
#define sz(a) a.size()
#define pb push_back

using namespace std;
using P = pair<int, int>;
using ll = long long;

const char nl = '\n';

int T, M, N, K;
P range;
map<int, int> cm, tm, sm, tsm;
map<int, queue<int>> window;
vector<int> files, skips;
vector<string> ans;

void clear_0(map<int, int> &tmap, map<int,int>::iterator i){
    if(i->second == 0) {
        tmap.erase(i);
    }
}

bool doskip(){
    int sizequery = std::min(K, static_cast<int>(skips.size()));
    if(sizequery == 0)
        return true;
    for (int i = 0; i < sizequery; i++) {
        sm[skips[skips.size() - i - 1]]++;//current map
    }
    if(range.first > sm.begin()->first) {
//        cout << "SUS"; // should never happen
        return false;
    }
    auto it = skips.end() - sizequery;//still in window; process then add it-1
    range = {tsm.begin()->first, tsm.begin()->first + K - 1};
    while(it!=skips.begin()) {
        int current_min = sm.begin()->first;
        int total_min = tsm.begin()->first;
        auto tsmclear = tsm.begin();
        auto smclear = sm.begin();
        if(range.second >= current_min){
            sm[current_min]--;
            tsm[current_min]--;
            tsmclear = tsm.find(current_min);
            clear_0(tsm, tsmclear);
            clear_0(sm, smclear);
            range = {total_min, total_min + K-1};
            it--;
            int toadd = *it;
            sm[toadd]++;
        }
        else{
            return false;
        }
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> M >> N >> K;
        bool visited[N];
        fill(visited, visited + N, false);
        cm.clear(); tm.clear(); sm.clear(); tsm.clear(); skips.clear(); files.clear(); window.clear();
        files.resize(N);
        for (int i = 0; i < N; i++) {
            cin >> files[i];
            if (i < K){
                cm[files[i]]++;
            }
            window[files[i]].push(i);
            tm[files[i]]++;
        }
        auto it = files.begin()+K;// process, need to change K-1 stuff
        int lastinwindow = 0;
        int goback = K;
        range = {tm.begin()->first, tm.begin()->first + K-1};
        while(it!=files.end()){
            int cur_lowest = cm.begin()->first;
            int total_lowest = tm.begin()->first;
            auto cmclear = cm.begin();
            auto tmclear = tm.begin();
//            if(cur_lowest == total_lowest){
            if(range.second >= cur_lowest){
                cm[cur_lowest]--;
                tm[cur_lowest]--;
                tmclear = tm.find(cur_lowest);
                int ind = window[cur_lowest].front();
                visited[ind] = true;
                window[cur_lowest].pop();
            }
            else{//total loweest is lower
                int kbefore = files[lastinwindow];
                visited[window[kbefore].front()] = true;
                window[kbefore].pop();
                skips.pb(kbefore);
                tsm[kbefore]++;
                cm[kbefore]--;
                tm[kbefore]--;
                cmclear = cm.find(kbefore);
                tmclear = tm.find(kbefore);

            }
            while(visited[lastinwindow])
                lastinwindow++;
            clear_0(cm, cmclear);
            clear_0(tm, tmclear);
            int toadd = *it;
            cm[toadd]++;
            range = {tm.begin()->first, tm.begin()->first + K-1};
            it++;
        }
        for(P p : cm){
            for (int j = 0; j < p.second; j++) {
                if(range.second < p.first) {
                    skips.pb(p.first);
                    tsm[p.first]++;
                }
            }
        }
        bool possible = doskip();
        ans.pb(possible ? "YES" : "NO");
    }//correct for creating skips; now add all remaining items into skips

    for_each(all(ans), [](string x){ cout << x << nl; });
}
//1
//9 13 3
//1 2 8 7 5 4 3 2 1 3 2 7 9