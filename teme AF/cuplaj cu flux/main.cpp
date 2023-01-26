#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin ("cuplaj.in");
ofstream fout ("cuplaj.out");

//Complexitatea algotirmului este O(N * (E+N)^2) n = numar total de noduri, e = numar total de muchii din cuplaj
int n,m;
bool BFS(vector<vector<int>>& graf, vector<vector<int>>& capacitati, vector<int>& parinte){
    vector<bool> vizitat;
    vizitat.resize(n+m+2, 0);
    queue<int> q;
    q.push(0);
    vizitat[0] = 1;
    parinte[0] = -1;

    while(!q.empty()){
        int nod = q.front();
        q.pop();
        for(int i = 0; i < graf[nod].size(); i++){
            int nod_aux = graf[nod][i];
            if (capacitati[nod][nod_aux] > 0 && vizitat[nod_aux] == 0){
                //salvez parintele nodului, pusez nodul si il marchez
                parinte[nod_aux] = nod;
                q.push(nod_aux);
                vizitat[nod_aux] = 1;
                if(nod_aux == m+n+1) return true;
            }
        }
    }
    //daca nu ajung la destinatie returnez false
    return false;
};

int main() {
    int e;
    fin>>n>>m>>e;
    vector<vector<int>> graf, capacitati; //lista de adiacenta, respectiv matrice cu capacitati

    graf.resize(n+m+2);
    capacitati.resize(n+m+2, vector<int> (n+m+2, 0));

    //leg nodurile la o sursa
    for(int i = 1; i <= n; i++) {
        capacitati[0][i] = 1;
        graf[0].push_back(i);
    }
    //leg nodurile la un nod final
    for(int i = n+1; i <= n+m; i++) {
        capacitati[i][n + m + 1] = 1;
        graf[i].push_back(n+m+1);
    }

    //citesc datele
    for(int i = 0; i < e; i++){
        int sursa,destinatie;
        fin>>sursa>>destinatie;
        capacitati[sursa][n+destinatie] = 1;
        graf[sursa].push_back(n+destinatie);
    }
    //rezolvare (folosesc algoritmul Edmonds–Karp pentru flow)
    int flow_max = 0;
    vector<int> parinte(n+m+2);

    while(BFS(graf, capacitati, parinte)){
        int flow_curent = 100000, i = n+m+1;
        //parcurg de la final la sursa ca sa calculez flowul
        while(i != 0){
            int nod = parinte[i];
            flow_curent = min(flow_curent, capacitati[nod][i]);
            i = parinte[i];
        }
        //parcurg din nou , dar de data aceasta modific graful si capacitatile folosind flowul gasit
        i = n+m+1;
        while(i != 0){
            int nod = parinte[i];
            capacitati[nod][i] -= flow_curent;
            capacitati[i][nod] += flow_curent;
            graf[i].push_back(nod);
            i = parinte[i];
        }

        flow_max += flow_curent;
    }
    fout<<flow_max<<'\n';

    //parcurg muchiile dintre noduri si le afisez pe cele prin care a trecut flow
    for(int i = 1; i <= n; i++){
        int j;
        for( j = 0; j < graf[i].size(); j++){
            if(capacitati[i][graf[i][j]] == 0 && graf[i][j] > n) {
                fout << i << " " << graf[i][j] - n;
                break;
            }
        }
        if(j != graf[i].size()) fout<<'\n';
    }
}
