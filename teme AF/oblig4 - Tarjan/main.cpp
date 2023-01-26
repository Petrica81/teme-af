#include <iostream>
#include <vector>
#include <fstream>
#include <stack>

using namespace std;

//programul meu are o complexitatea O(n+m) deoarece folosesc algoritmul lui Tarjan pentru a gasi componentele tare conexe
//Parcurg printr-un DFS graful si ii atribui fiecarui nod un index , un index minim, si il inserez pe o stiva
// daca un adiacent acestuia are index minim mai mic decat indexul minim al nodului curent , schimb indexul minim al nodului curent
// dupa ce am ajuns la finalul DFS-ului , se parcurge in sense invers si unde indexul este egal cu indexul minim
//inseamna ca este inceputul unei componente tare conexe. In acel moment pe stiva , deasupra locatiei acelui nod
// sunt nodurile care fac parte din aceeasi componenta tare conexa cu el;
ifstream in("ctc.in");
ofstream out("ctc.out");
vector<vector<int>> graf,componente;
vector<int> index, low_index;
vector<bool> on_stack;
stack<int> s;
int n, m, dex = 1;

void tarjan(int nod) {
    index[nod] = dex;
    low_index[nod] = dex;
    dex++;
    s.push(nod);
    on_stack[nod] = true;
    for (int i = 0; i < graf[nod].size(); i++){
        if(index[graf[nod][i]] == 0) {
            tarjan(graf[nod][i]);
            low_index[nod] = min(low_index[nod],low_index[graf[nod][i]]);
        }
        if(on_stack[graf[nod][i]])
            low_index[nod] = min(low_index[nod],low_index[graf[nod][i]]);
    }
    if(low_index[nod] == index[nod]){
        componente.push_back({});
        int x,y = componente.size()-1;
        do{
            x = s.top();
            componente[y].push_back(x);
            on_stack[x] = false;
            s.pop();
        }while (nod != x);
    }
}


int main() {
    in>>n>>m;
    graf.resize(n+1);
    index.resize(n+1);
    on_stack.resize(n+1);
    low_index.resize(n+1);
    for(int i = 1; i <= m; i++){
        int v1,v2;
        in>>v1>>v2;
        graf[v1].push_back(v2);
    }
    for(int i = 1; i<= n ; i++)
        if(index[i] == 0)
            tarjan(i);


    out<<componente.size()<<'\n';
    for(int i = 0; i < componente.size(); i++){
        for(int j = 0; j < componente[i].size(); j++)
            out<<componente[i][j]<<" ";
        out<<'\n';
    }
    return 0;
}
