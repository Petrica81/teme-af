#include <iostream>
#include <vector>
#include <queue>

using namespace std;
//folosesc bitmask si bfs
//Complexitatea mea este O(n*m*(2^n))
int shortestPathLength(vector<vector<int>>& graph) {
    int n = graph.size();
    queue<pair<int, int>> q; //queue pentru bfs
    vector<vector<bool>> vizitat(n, vector<bool> (1<<n, false));

    //inserez in q si marchez vizitate toate posibilitatile de a incepe
    for(int i = 0; i < n; i++){
        q.push({i, 1<<i}); // retin nodul si 1 la pozitia 2^i pe biti
        vizitat[i][1<<i] = 1; // marchez vizitat nodul  prin pozitia la care am ajuns la el
    }

    int dist = 0; // raspunsul meu
    //aplic bfs
    while(q.size()){
        //aplic algoritmul pe tot ce am deja in q, deoarece au aceeasi distanta
        int i = q.size();
        while(i){
            //iau primul element si il elimin din q
            int k = q.front().first;
            int mask = q.front().second;
            q.pop();
            // daca valoare mea din mask contine 1 pe toti bitii, atunci am gasit solutia
            if(mask == (1<<n)-1) return dist;
            //pentru toti vecinii nodului(inafar de cel din care am venit sau care a fost deja vizitat inainte prin aceleasi noduri)
            for(auto x: graph[k]){
                if(!vizitat[x][mask | (1 << x)]){ // mask | (1<<x) imi schimba valoare bitului de pe pozitia x din mask in 1;
                    //inserez in q si marchez vizitat
                    q.push({x, mask | (1 << x)});
                    vizitat[x][mask | (1 << x)] = true;
                }
            }
            i--;
        }
        //cresc distanta din moment ce nu am gasit o solutie cu cea actuala
        dist++;
    }
    return dist;
}
int main() {
    return 0;
}
