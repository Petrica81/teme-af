#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

ifstream fin ("transport2.in");
ofstream fout ("transport2.out");
//Complexitate O(n+m)
int main() {
    int n,m;
    fin>>n>>m;//salvez datele
    vector<vector<pair<int,int>>> graf(n+1);
    vector<bool>vizitat(n+1, false);
    for(int i = 1; i <= m; i++){
        int nod1, nod2, cost;
        fin>>nod1>>nod2>>cost;
        graf[nod1].push_back({cost,nod2});
        graf[nod2].push_back({cost,nod1});
    }

    //aplic un BFS folosind max-heap din moment ce vreau valoarea cea mai mare
    priority_queue<pair<int,int>> q; // pun in q pair sub forma {cost,nod} ca s aimi ordoneze in functie de cost
    q.push({10000000,1});
    while(!q.empty()){
        pair<int,int> nod = q.top();
        q.pop();
        if(nod.second == n){//verific daca am ajuns la destinatie ,
            // daca da afisez din moment ce am selectat valoarea cea mai mare din heap
            fout<<nod.first;
            return 0;
        }
        vizitat[nod.second] = true;
        for(int i = 0; i < graf[nod.second].size(); i++){
            pair<int,int> nod2 = {graf[nod.second][i].first,graf[nod.second][i].second};
            if(vizitat[nod2.second] == false){
                q.push({min(nod.first,nod2.first),nod2.second});
            }
        }
    }
    return 0;
}
