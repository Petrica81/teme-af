#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

ifstream fin("catun.in");
ofstream fout("catun.out");
//Complexitatea este O(m+n*log(n))
int main() {
    //declarare si citire date
    int n,m,k;
    fin>>n>>m>>k;
    vector<int> fortarete(k);
    for(int i = 0; i < k; i++)
        fin>>fortarete[i];

    //creez graful
    vector<vector<pair<int,long>>> graf(n+1);
    for(int i = 0; i < m; i++){
        int nod,nod2,val;
        fin>>nod>>nod2>>val;
        graf[nod].push_back({nod2,val});
        graf[nod2].push_back({nod,val});
    }
    //rezolvare

    vector<bool> vizitat(n+1,0);
    vector<pair<long,int>> dist(n+1,{1000000,0}); // distanta, fortareata
    priority_queue<pair<long,int>, vector<pair<long,int>>, greater<pair<long,int>>> heap;// min heap pentru Dijkstra
    for(int i = 0; i < k; i++){//inserez in heap si in vectorul de distante toate fortaretele, cu distanta 0 si fortareata respectiva
        heap.push({0,fortarete[i]});
        dist[fortarete[i]] = {0,fortarete[i]};
    }

    while(heap.size()){//aplic Dijkstra pornind de la fortarete
        int nod = heap.top().second; // selectez nodul cu cea mai mica distanta fata de o fortareata
        heap.pop();
        for(int i = 0; i < graf[nod].size(); i++){//pentru toti vecinii lui nevizitati
            int nod2 = graf[nod][i].first;
            long distanta = graf[nod][i].second;
            if(!vizitat[nod2]){
                // daca distantele fata de doua fortarete sunt egale , atunci actualizez cu fortareata cea mai mica(indice)
                if(dist[nod2].first == dist[nod].first + distanta && dist[nod2].second > dist[nod].second)
                    dist[nod2].second = dist[nod].second;
                //daca distanta salvata este mai mare decat cea actuala , actualizez atat distanta cat si fortareata
                if(dist[nod2].first > dist[nod].first + distanta){
                    dist[nod2].first = dist[nod].first + distanta;
                    dist[nod2].second = dist[nod].second;
                    heap.push({dist[nod2].first,nod2}); //inserez in heap
                }
            }
        }
        vizitat[nod] = 1; //marchez catunul ca vizitat
    }
    for(int i = 0; i < k; i++){
        //updatez pentru fortarete, fortareata la care sunt legate cu 0
        dist[fortarete[i]].second = 0;
    }
    for(int i = 1; i <= n; i++){
        fout<<dist[i].second<<" ";//pentru toate nodurile ,afisez fortaretele salvate in vectorul de distante
    }
    return 0;
}
