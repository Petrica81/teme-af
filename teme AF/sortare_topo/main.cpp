#include <iostream>
#include <deque>
#include <fstream>
#include <vector>
using namespace std;
ifstream f("sortaret.in");
ofstream g("sortaret.out");
deque<int> C;
vector<pair<vector<int>,int>> graf;
int n,m,x,y;

int main(){
    f>>n>>m;
    graf.reserve(n+1);
    for(int i = 1; i <= m; i++) {
        f >> x >> y;
        graf[x].first.push_back(y);
        graf[y].second++;
    }
    for(int i = 1; i <= n; i++){
        if(graf[i].second == 0) C.push_back(i);
    }
    while(C.size() != 0){
        x = C[0];
        for(int i = 0; i < graf[x].first.size(); i++){
            y = graf[x].first[i];
            graf[y].second--;
            if(graf[y].second == 0) C.push_back(y);
        }
        g<<x<<" ";
        C.pop_front();
    }
    return 0;
}
