#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

//folosesc Dijkstra cu heap si am un graf complet( m > n)
//complexitatea este O(m+n*log(n))
class Solution {
public:
    int distanta(vector<int> &p1, vector<int> &p2){
        //functie pentru a calcula distanta
        return abs(p1[0]-p2[0])+abs(p1[1]-p2[1]);
    }
    int minCostConnectPoints(vector<vector<int>>& points) {
        //declar variabilele necesare
        int suma = 0;
        int n = points.size();
        vector<bool> vizitat(n,0);
        vector<int> dist(n,10000000);
        //declar un min_heap
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> heap;
        //inserez punctul de la care pornesc cu distanta 0;
        heap.push({0,0});
        dist[0] = 0;
        //cat timp am elemente in heap
        while(!heap.empty()){
            int nod = heap.top().second;
            heap.pop();
            //daca elementul cel mai mic din heap reprezinta un nod nevizitat(am dubluri in heap)
            if(!vizitat[nod]){
                vizitat[nod] = 1;
                //verific distanta de la el la toate celelalte noduri nevizitate
                for(int i = 0; i < n; i++)
                    if(!vizitat[i] && distanta(points[nod],points[i]) < dist[i]){
                        //daca distanta catre un punct este mai mica decat cea actuala, actualizez
                        dist[i] = distanta(points[nod],points[i]);
                        //inserez in heap
                        heap.push({dist[i],i});
                    }
                //adaug distanta minima in suma mea
                suma += dist[nod];

            }
        }
        return suma;

    }
};
int main() {
    return 0;
}
