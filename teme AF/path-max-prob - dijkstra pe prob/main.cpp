#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    //Algoritmul are o complexitate de O(m+n*log(n)) n = numar de noduri, m este numarul de muchii
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        //declar datele necesare  si creez graful
        vector<pair<int,double>> graf[n];
        for(int i = 0; i < edges.size(); i++){
            graf[edges[i][0]].push_back({edges[i][1],succProb[i]});
            graf[edges[i][1]].push_back({edges[i][0],succProb[i]});
        }

        vector<bool> vizitat(n,0);
        vector<double>dist(n,0); //salvez probabilitatile
        dist[start] = 1;
        vizitat[start] = 1;
        //folosec un max heap pentru Dijkstra
        priority_queue<pair<double,int>> heap; // prob, nod
        heap.push({1,start});

        while(heap.size()){
            int nod = heap.top().second;// selectez nodul cu probabilitatea cea mai mare
            heap.pop();//il elimin din heap
            for(int i = 0; i < graf[nod].size(); i++){//pentru toti vecinii lui care inca nu au fost vizitati
                int nod2 = graf[nod][i].first;
                double prob = graf[nod][i].second;
                if(!vizitat[nod2]){//daca probabilitatea de a ajunge la el este mai mare decat cea salvata, il actualizez
                    if(dist[nod2] < dist[nod] * prob){
                        dist[nod2] = dist[nod] * prob;
                        heap.push({dist[nod2],nod2});//il adaug in max heap
                    }
                }
            }
            vizitat[nod] = 1; // marchez nodul prin care am trecut ca fiind vizitat
        }
        return dist[end];//returnez probabilitatea salvata pentru nodul cautat
    }
};
int main() {

    return 0;
}
